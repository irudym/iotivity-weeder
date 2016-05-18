//******************************************************************
//
// Copyright 2016 Igor Rudym.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#ifndef WEEDEROBSERVER_H
#define WEEDEROBSERVER_H


#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <functional>

using namespace std;

//Polling callback function prototype.
typedef function<void(void)> IoTObserverCb;

//Hosts a polling thread which continually calls the specific function
//supplied to its constructor. Client code simply uses Start/Stop calls
//to kick off/suspend polling.
class WeederObserver {
    mutex m_mutex;
    condition_variable m_cond;
    IoTObserverCb m_callback;
    thread m_observerThread[1];
    bool m_destroy;
    bool m_started;
    void observerThread();
    void terminate();
public:
    WeederObserver(IoTObserverCb Cb);
    virtual ~WeederObserver();
    void start();
    void stop();
};



#endif