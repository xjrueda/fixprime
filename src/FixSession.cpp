

#include "FixSession.h"
#include "Socket.h"
#include "Acceptor.h"

namespace fprime {

    FixSession::FixSession() : connected(false), ibpRunning(false) {
    }

    FixSession::FixSession(const FixSession& orig) {
    }

    FixSession::~FixSession() {
        cout << "FixSession released" << endl;
    }

    void FixSession::inboundProcessor() {
        
        Socket::MessageQueuePtr inboundQueue = acceptor.getInboundQueuePtr();
        
        setIbRunning(true);
        fprime::FixParser parser;
        parser.setProtocol(protocolPtr);
        parser.setSeparator('\001');

        while (ibpRunning) {
            unique_lock<mutex> lock(acceptor.inboundLock);

            while (inboundQueue->empty()) {
                acceptor.inboundCondition.wait(lock);
            }
            string rawMsg = inboundQueue->front();
            inboundQueue->pop();
            lock.unlock();
            try {
                fprime::FixParser::FlatMessage flatMessage = parser.explode(rawMsg);
                fprime::Message fixMsg = parser.parseMessage(flatMessage);
                string callbackKey = fixMsg.getHeader()->getChild(8)->getValue() + "-" + fixMsg.getHeader()->getChild(35)->getValue();

                // delegates the method to it handler
                callbacksManager->executeCallback(callbackKey, fixMsg, this);

            } catch (exception& e) {
                cout << "error in inboundprocessor" + string(e.what()) << endl;
                setIbRunning(false);
                //TODO log error
            }
        }

    }

    void FixSession::setCallbackManager(fprime::CallbacksManager::CallbacksManagerPtr cbMan) {
        callbacksManager = cbMan;
    }

    void FixSession::setProtocol(fprime::Protocol::ProtocolPtr protPtr) {
        protocolPtr = protPtr;
    }

    bool FixSession::startInboundProcessor() {
        try {
            // launch the processor for inbound messages
            thread t1(bind(&FixSession::inboundProcessor, this));
            t1.detach();
            return true;
        } catch (...) {
            return false;
        }
    }

    bool FixSession::stopInboundProcessor() {
        if (inboundQueue.empty()) {
            setIbRunning(false);
            return true;
        } else
            return false;
    }

    void FixSession::stopAbortProcessor() {
        setIbRunning(false);
    }

    bool FixSession::connect() {
        setConnected(true);
    }

    bool FixSession::disconnect() {
        setConnected(false);
    }

    void FixSession::startAcceptor(boost::asio::io_service& io_service, unsigned short port) {
        acceptor.start(io_service, port);
        cout << "acceptor started" << endl;
    }

    void FixSession::start(boost::asio::io_service& io_service, unsigned short port) {
        if (!startInboundProcessor())
            throw runtime_error("at FixSession.start : InboundProcessor could not be started.");
        setSessionRunning(true);
        startAcceptor(io_service, port);
    }

    void FixSession::stop() {
        //disconnect();
        acceptor.stop();
        bool emtyqueue = false;
        while (!emtyqueue) {
            emtyqueue = stopInboundProcessor();
            usleep(500000);
        }
    }

    void FixSession::setConnected(bool val) {
        mutex lock;
        lock.lock();
        connected = val;
        lock.unlock();
    }

    void FixSession::setSessionRunning(bool val) {
        mutex lock;
        lock.lock();
        sessionRunning = val;
        lock.unlock();
    }

    void FixSession::setIbRunning(bool val) {
        mutex lock;
        lock.lock();
        ibpRunning = val;
        lock.unlock();
    }

    
}