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

#ifndef WEEDERSERVER_H
#define WEEDERSERVER_H

#include <string>
#include <iostream>
#include <memory>

#include "ocstack.h"
//#include "observer.h"
#include "OCPlatform.h"
#include "OCApi.h"

#include "WeederObserver.h"
#include "CSensor.h"

using namespace std;
using namespace OC;


class WeederIoTServer {
    shared_ptr<MRAASystem> m_MRAA;
    shared_ptr<PlatformConfig> m_platformConfig;

    OCPlatformInfo m_platformInfo; //OCPlatformInfo Contains all the platform info to be stored
    OCDeviceInfo m_deviceInfo; //OCDeviceInfo Contains all the device info to be stored


    ObservationIds m_temperatureObservers;
    shared_ptr<WeederObserver> m_temperatureObserverLoop;

    ObservationIds m_moistObserver;
    shared_ptr<WeederObserver> m_moistObserverLoop;

    TSensorMap m_sensors;

    void initPlatform();
    void setupResources();
    void createResource(string, string, EntityHandler, OCResourceHandle&);

public:
    WeederIoTServer();
    virtual ~WeederIoTServer();
    void showSensors();
    float getData(int pin_num);

    shared_ptr<CSensor> addSensor(string name, string end_point, string type, string resource_key, int pin);

    void setLog(const char* log_file);
};

#endif