

#include "FixSession.h"
#include "Socket.h"
#include "Acceptor.h"
#include "Initiator.h"

namespace fprime {

    FixSession::FixSession(FixSessionSetup ssetup) : sessionSetup(ssetup), connected(false), ibpRunning(false) {
        if (ssetup.getType() == "Acceptor") {
            connectorPtr.reset(new fprime::Acceptor); 
        } else {
            connectorPtr.reset(new fprime::Initiator); 
        }
    }

    FixSession::FixSession(const FixSession& orig) {
    }

    FixSession::~FixSession() {
        cout << "FixSession released" << endl;
    }

    void FixSession::inboundProcessor() {
        
        Socket::MessageQueuePtr inboundQueue = connectorPtr->getInboundQueuePtr();
        
        setIbRunning(true);
        fprime::FixParser parser;
        parser.setProtocol(protocolPtr);
        parser.setSeparator('\001');

        while (ibpRunning) {
            unique_lock<mutex> lock(connectorPtr->inboundLock);

            while (inboundQueue->empty()) {
                connectorPtr->inboundCondition.wait(lock);
            }
            string rawMsg = inboundQueue->front();
            inboundQueue->pop();
            lock.unlock();
            try {
                fprime::FixParser::FlatMessage flatMessage = parser.explode(rawMsg);
                fprime::Message fixMsg = parser.parseMessage(flatMessage);
                string callbackKey = fixMsg.getHeader()->getChild(8)->getValue() + "-" + fixMsg.getHeader()->getChild(35)->getValue();

                // delegates the method to it handler
                //cout << "Executing delegate" << endl;
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

    void FixSession::start(Socket::IOSPtr iosPtr, unsigned short port) {
        if (!startInboundProcessor())
            throw runtime_error("at FixSession.start : InboundProcessor could not be started.");
        
        cout << "acceptor started" << endl;
        setSessionRunning(true);
        if (sessionSetup.getType() == "Acceptor") 
            connectorPtr->start(iosPtr, sessionSetup.getPort());
        else
            connectorPtr->start(iosPtr, sessionSetup.getHost(), sessionSetup.getPort());
    }

    void FixSession::stop() {
        //disconnect();
        connectorPtr->stop();
        bool emtyqueue = false;
        while (!emtyqueue) {
            emtyqueue = stopInboundProcessor();
            usleep(500000);
        }
        
        cout << "Session Stopped" << endl;
    }

    void FixSession::send(string msg) {
        connectorPtr->send(msg);
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