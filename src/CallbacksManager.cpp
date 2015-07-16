/* 
 * File:   Delegator.cpp
 * Author: DeveloperPrime
 * 
 * Created on July 15, 2015, 10:28 AM
 */

#include "CallbacksManager.h"
#include "FixSession.h"

namespace fprime {

    CallbacksManager::CallbacksManager() {
    }

    CallbacksManager::CallbacksManager(const CallbacksManager& orig) {
    }

    CallbacksManager::~CallbacksManager() {
        cout << "CallbacksManager released" << endl;
    }

    void CallbacksManager::registerCallback(string methodName, fprime::CallbacksManager::CallBackType task, bool async) {
        Callback callback;
        callback.setCallBack(task, async);
        callbacksMap[methodName] = callback;
    }

    void CallbacksManager::unregisterCallback(string methodName) {
        callbacksMap.erase(methodName);
    }

    void CallbacksManager::executeCallback(string methodName,  fprime::Message msg, fprime::FixSession* sessionPtr) {
        typename std::map<string, Callback>::iterator it;
        future<void> f1;
        it = callbacksMap.find(methodName);
        if (it != callbacksMap.end()) {
            try {
                CallBackType task = it->second.getCallback();
                if (it->second.getlaunchAsync()) {
                    f1 = std::async(std::launch::async, task, msg, sessionPtr);
                } else
                    task(msg, sessionPtr);
            } catch (...) {
                
            }
        }
    }
}

