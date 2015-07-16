

#include "FixSession.h"


namespace fprime {

    FixSession::FixSession() : connected(false), ibpRunning(false) {
    }

    FixSession::FixSession(const FixSession& orig) {
    }

    FixSession::~FixSession() {
        cout << "FixSession released" << endl;
    }

    void FixSession::inboundProcessor() {
        if (!connected)
            throw runtime_error("at FixSession.inboundProcessor : session not connected");
        fprime::FixParser parser;
        parser.setProtocol(protocolPtr);
        parser.setSeparator('\001');

        while (ibpRunning) {
            unique_lock<mutex> lock(inboundLock);

            while (inboundQueue.empty()) {
                inboundCondition.wait(lock);
            }
            RawMessage rawMsg(inboundQueue.front());
            inboundQueue.pop();
            lock.unlock();
            try {
                fprime::FixParser::FlatMessage flatMessage = parser.explode(rawMsg.getText());
                fprime::Message fixMsg = parser.parseMessage(flatMessage);
                string callbackKey = fixMsg.getHeader()(8).getValue() + "-" + fixMsg.getHeader()(35).getValue();

                // delegates the method to it handler
                callbacksManager->executeCallback(callbackKey, fixMsg, this);

            } catch (exception& e) {
                cout << "at FixSession.inboundProcessor :" << e.what() << endl;
                cout.flush();
            }
        }
    }

    void FixSession::setCallbackManager(fprime::CallbacksManager::CallbacksManagerPtr cbMan) {
        callbacksManager = cbMan;
    }

    void FixSession::setProtocol(fprime::Protocol::ProtocolPtr protPtr) {
        protocolPtr = protPtr;
    }

    void FixSession::startInboundProcessor() {
        mutex lock;
        lock.lock();
        ibpRunning = true;
        lock.unlock();

        // lauch the processor for inbound messages
        thread t1(bind(&FixSession::inboundProcessor, this));
        t1.detach();
    }

    void FixSession::stopInboundProcessor() {
        mutex lock;
        lock.lock();
        usleep(1000000);
        ibpRunning = false;
        lock.unlock();
    }

    void FixSession::pushInbound(const string msg) {
        unique_lock<mutex> lock(inboundLock);
        inboundQueue.push(RawMessage(msg));
        lock.unlock();
        inboundCondition.notify_one();
    }

    bool FixSession::connect() {
        mutex lock;
        lock.lock();
        connected = true;
        lock.unlock();
        return true;
    }

    bool FixSession::disconnect() {
        mutex lock;
        lock.lock();
        connected = false;
        lock.unlock();
        return true;
    }
}