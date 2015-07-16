/* 
 * File:   Delegator.h
 * Author: DeveloperPrime
 *
 * Created on July 15, 2015, 10:28 AM
 */

#ifndef CALLBACKMANAGER_H
#define	CALLBACKMANAGER_H

#include "Message.h"
#include <map>
#include <functional>
#include <future>


using namespace std;
namespace fprime {
    class FixSession;
    class CallbacksManager {
    public:
        typedef shared_ptr<fprime::CallbacksManager> CallbacksManagerPtr;
        typedef std::function<void(fprime::Message, fprime::FixSession*) > CallBackType;
        CallbacksManager();
        CallbacksManager(const CallbacksManager& orig);
        virtual ~CallbacksManager();

        void registerCallback(string, fprime::CallbacksManager::CallBackType, bool);
        void unregisterCallback(string);
        void executeCallback(string, fprime::Message, fprime::FixSession*);
    private:

        struct Callback {

            void setCallBack(CallBackType callback, bool async) {
                _callback = callback;
                launchAsync = async;
            }

            CallBackType getCallback() {
                return _callback;
            }

            bool getlaunchAsync() {
                return launchAsync;
            }
        private:
            CallBackType _callback;
            bool launchAsync;
        };
        std::map<string, Callback> callbacksMap;
    };

}

#endif	/* CALLBACKMANAGER_H */

