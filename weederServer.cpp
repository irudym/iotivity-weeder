//
// Created by Igor Rudym on 23/04/16.
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


#include <signal.h>
#include <thread>
#include <functional>

#include "weederServer.h"
#include "namedefs.h"


void WeederIoTServer::initPlatform() {
    cout << "Init weeder server" << endl;

    m_platformConfig = make_shared<PlatformConfig>(ServiceType::InProc, ModeType::Server, "0.0.0.0",
            0, OC::QualityOfService::HighQos);

    OCPlatform::Configure(*m_platformConfig);
}

WeederIoTServer::WeederIoTServer() {
    initPlatform();
    setupResources();

    m_moistSensor1Rep.setValue(MOIST_RESOURCE_KEY, 0);
    m_moistSensor2Rep.setValue(MOIST_RESOURCE_KEY, 0);
    m_temperatureSensor1Rep.setValue(TEMPERATURE_RESOURCE_KEY, (float) 0.0f);
    m_temperatureSensor2Rep.setValue(TEMPERATURE_RESOURCE_KEY, (float) 0.0f);
}

WeederIoTServer::~WeederIoTServer() {
    cout << "Stop weeder server" << endl;
    //ClosePins();
}

void WeederIoTServer::setupResources() {
    EntityHandler cb1 = bind(&WeederIoTServer::temperatureSensor1EntityHandler, this, placeholders::_1);
    createResource(TEMPERATURE_RESOURCE_ENDPOINT, TEMPERATURE_RESOURCE_TYPE, cb1,
                   m_temperatureSensor1Res);
    //IoTObserverCb tempObsCb = bind(&IoTServer::temperatureObserverLoop, this);
    //m_temperatureObserverLoop = make_shared<IoTObserver>(tempObsCb);

    EntityHandler cb2 = bind(&WeederIoTServer::temperatureSensor2EntityHandler, this, placeholders::_1);
    createResource(TEMPERATURE_RESOURCE_ENDPOINT, TEMPERATURE_RESOURCE_TYPE, cb2,
                   m_temperatureSensor2Res);

    EntityHandler cb3 = bind(&WeederIoTServer::moistSensor1EntityHandler, this, placeholders::_1);
    createResource(MOIST_RESOURCE_ENDPOINT, MOIST_RESOURCE_TYPE, cb3,
                   m_moistSensor1Res);
    EntityHandler cb4 = bind(&WeederIoTServer::moistSensor2EntityHandler, this, placeholders::_1);
    createResource(MOIST_RESOURCE_ENDPOINT, MOIST_RESOURCE_TYPE, cb4,
                   m_moistSensor2Res);

}

void WeederIoTServer::createResource(string Uri, string Type, EntityHandler Cb, OCResourceHandle& Handle) {
    string resourceUri = Uri;
    string resourceType = Type;
    string resourceInterface = EDISON_RESOURCE_INTERFACE;
    uint8_t resourceFlag = OC_DISCOVERABLE | OC_OBSERVABLE;

    cout << "Creating resource: " << Type << endl;

    OCStackResult result = OCPlatform::registerResource(Handle, resourceUri, resourceType, resourceInterface, Cb, resourceFlag);

    if(result != OC_STACK_OK)
        cerr << "\tCould not create " << Type << " resource" << endl;
    else
        cout << "\tSuccesfully created " << Type << " resource" << endl;
}

OCRepresentation WeederIoTServer::getTemperatureSensor1Rep() {
    float temp = 0;
    //TODO: need to read data from a sensor, use MRAA library for that
    m_temperatureSensor1Rep.setValue(TEMPERATURE_RESOURCE_KEY, temp);
    return m_temperatureSensor1Rep;
}

OCRepresentation WeederIoTServer::getTemperatureSensor2Rep() {
    float temp = 0;
    //TODO: need to read data from a sensor, use MRAA library for that

    m_temperatureSensor2Rep.setValue(TEMPERATURE_RESOURCE_KEY, temp);
    return m_temperatureSensor2Rep;
}

OCRepresentation WeederIoTServer::getMoistSensor1Rep() {
    float temp = 0;
    //TODO: need to read data from a sensor, use MRAA library for that

    m_temperatureSensor1Rep.setValue(MOIST_RESOURCE_KEY, temp);
    return m_moistSensor1Rep;
}

OCRepresentation WeederIoTServer::getMoistSensor2Rep() {
    float temp = 0;
    //TODO: need to read data from a sensor, use MRAA library for that

    m_temperatureSensor1Rep.setValue(MOIST_RESOURCE_KEY, temp);
    return m_moistSensor2Rep;
}


OCEntityHandlerResult WeederIoTServer::sensorEntityHandler(shared_ptr<OCResourceRequest> Request, string sensor) {
    OCEntityHandlerResult result = OC_EH_ERROR;
    if(Request) {
        string requestType = Request->getRequestType();
        int requestFlag = Request->getRequestHandlerFlag();

        if(requestFlag & RequestHandlerFlag::RequestFlag) {
            auto Response = make_shared<OC::OCResourceResponse>();
            Response->setRequestHandle(Request->getRequestHandle());
            Response->setResourceHandle(Request->getRequestHandle());

            if(requestType == "GET") {
                cout << "GET request for " << sensor << " reading" << endl;
                if(Response) {
                    Response->setErrorCode(200);
                    Response->setResponseResult(OC_EH_OK);
                    if(sensor == "temperature1")
                        Response->setResourceRepresentation(getTemperatureSensor1Rep());
                    else if(sensor == "temperature2")
                        Response->setResourceRepresentation(getTemperatureSensor2Rep());
                    else if(sensor == "moist1")
                        Response->setResourceRepresentation(getMoistSensor1Rep());
                    else if(sensor == "moist2")
                        Response->setResourceRepresentation(getMoistSensor2Rep());
                    else {
                        cerr << "Unsupported type of sensor:" << sensor << endl;
                        return result;
                    }
                    if(OCPlatform::sendResponse(Response) == OC_STACK_OK) {
                        result = OC_EH_OK;
                    }
                }
            }
            else {
                Response->setResponseResult(OC_EH_ERROR);
                OCPlatform::sendResponse(Response);
                cerr << "Unsupported request type" << endl;
                return result;
            }
        }
        if(requestFlag & RequestHandlerFlag::ObserverFlag) {
            ObservationInfo observationInfo = Request->getObservationInfo();
            if (ObserveAction::ObserveRegister == observationInfo.action) {
                cout << "Staring observer for " << sensor << " sensor" << endl;
                //m_temperatureObservers.push_back(observationInfo.obsId);
                //m_temperatureObserverLoop->start();

                //TODO: here should be the problem with result value
            }
            else if (ObserveAction::ObserveUnregister == observationInfo.action)
            {
                cout << "Stopping observer for " << sensor << " sensor" << endl;
                //m_temperatureObservers.erase(
                //        remove(m_temperatureObservers.begin(), m_temperatureObservers.end(),
                //               observationInfo.obsId),
                //        m_temperatureObservers.end());
                //m_temperatureObserverLoop->stop();
            }
        }
    }
    return result;
}

OCEntityHandlerResult WeederIoTServer::temperatureSensor1EntityHandler(shared_ptr<OCResourceRequest> Request) {
    return sensorEntityHandler(Request, "temperature1");
}

OCEntityHandlerResult WeederIoTServer::temperatureSensor2EntityHandler(shared_ptr<OCResourceRequest> Request) {
    return sensorEntityHandler(Request, "temperature2");
}

OCEntityHandlerResult WeederIoTServer::moistSensor1EntityHandler(shared_ptr<OCResourceRequest> Request) {
    return sensorEntityHandler(Request, "moist1");
}

OCEntityHandlerResult WeederIoTServer::moistSensor2EntityHandler(shared_ptr<OCResourceRequest> Request) {
    return sensorEntityHandler(Request, "moist2");
}






