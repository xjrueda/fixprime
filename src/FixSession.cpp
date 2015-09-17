

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
        setIbRunning(true);
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
                string callbackKey = fixMsg.getHeader()->getChild(8)->getValue() + "-" + fixMsg.getHeader()->getChild(35)->getValue();

                // delegates the method to it handler
                callbacksManager->executeCallback(callbackKey, fixMsg, this);

            } catch (exception& e) {
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

    void FixSession::pushInbound(const string msg) {
        unique_lock<mutex> lock(inboundLock);
        inboundQueue.push(RawMessage(msg));
        lock.unlock();
        inboundCondition.notify_one();
    }

    bool FixSession::connect() {
        setConnected(true);
    }

    bool FixSession::disconnect() {
        setConnected(false);
    }

    void FixSession::startAcceptor(boost::asio::io_service& io_service, unsigned short port) {
        tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
        tcp::socket sock(io_service);
        a.accept(sock);
        setConnected(true);
        try {
            while (connected) {
                char data[max_length];
                cout << "receiving" << endl;
                boost::system::error_code error;
                size_t length = sock.read_some(boost::asio::buffer(data), error);

                if (error == boost::asio::error::eof) {
                    usleep(5000000);
                    break; // Connection closed cleanly by peer.
                } else if (error)
                    throw boost::system::system_error(error); // Some other error.
                pushInbound(string(data));
            }
            a.close();
            setConnected(false);
        } catch (std::exception& e) {
            setConnected(false);
            std::cerr << "at FixSession.startAcceptor: " << e.what() << "\n";
        }
    }

    void FixSession::start(boost::asio::io_service& io_service, unsigned short port) {
        if (!startInboundProcessor())
            throw runtime_error("at FixSession.start : InboundProcessor could not be started.");
        setSessionRunning(true);
        startAcceptor(io_service, port);
    }

    void FixSession::stop() {
        disconnect();
        bool emtyqueue = false;
        while (!emtyqueue) {
            emtyqueue = stopInboundProcessor();
            usleep(500000);
        }
    }


    // Private methods

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