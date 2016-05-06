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

using namespace std;
using namespace OC;

class WeederIoTServer {
    shared_ptr<PlatformConfig> m_platformConfig;

    //sensors representations and handlers
    OCRepresentation m_moistSensor1Rep;
    OCResourceHandle m_moistSensor1Res;

    OCRepresentation m_moistSensor2Rep;
    OCResourceHandle m_moistSensor2Res;

    OCRepresentation m_temperatureSensor1Rep;
    OCResourceHandle m_temperatureSensor1Res;

    OCRepresentation m_temperatureSensor2Rep;
    OCResourceHandle m_temperatureSensor2Res;

    void initPlatform();
    void setupResources();
    void createResource(string, string, EntityHandler, OCResourceHandle&);



    //get data from sensors
    OCRepresentation getTemperatureSensor1Rep();
    OCRepresentation getTemperatureSensor2Rep();
    OCRepresentation getMoistSensor1Rep();
    OCRepresentation getMoistSensor2Rep();

    //polling threads to periodically query sensors values and notify subscribers
    //void temperatureObserverLoop();
    //void moistObserverLoop();

    OCEntityHandlerResult sensorEntityHandler(shared_ptr<OCResourceRequest>, string sensor);

    OCEntityHandlerResult temperatureSensor1EntityHandler(shared_ptr<OCResourceRequest>);
    OCEntityHandlerResult temperatureSensor2EntityHandler(shared_ptr<OCResourceRequest>);
    OCEntityHandlerResult moistSensor1EntityHandler(shared_ptr<OCResourceRequest>);
    OCEntityHandlerResult moistSensor2EntityHandler(shared_ptr<OCResourceRequest>);

public:
    WeederIoTServer();
    virtual ~WeederIoTServer();
    void showSensors();
    float getData(int pin_num);

    void setLog(const char* log_file);
};

#endif