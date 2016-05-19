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
#include <octypes.h>

#include "ocpayload.h"

#include "weederServer.h"

#include "TemperatureSensor.h"
#include "MoistSensor.h"

void DuplicateString(char ** targetString, std::string sourceString)
{
    *targetString = new char[sourceString.length() + 1];
    strncpy(*targetString, sourceString.c_str(), (sourceString.length() + 1));
}


void WeederIoTServer::initPlatform() {
    cout << "Init weeder server" << endl;

    m_platformConfig = make_shared<PlatformConfig>(ServiceType::InProc, ModeType::Server, "0.0.0.0",
            0, OC::QualityOfService::HighQos);

    OCPlatform::Configure(*m_platformConfig);

    cout <<"Register the platform... ";
    OCStackResult result;
    DuplicateString(&m_platformInfo.manufacturerName, MANUFACTURER_NAME);
    DuplicateString(&m_platformInfo.manufacturerUrl, MANUFACTURER_URL);
    DuplicateString(&m_platformInfo.platformID, PLATFORM_ID);
    DuplicateString(&m_platformInfo.operatingSystemVersion, OS_VERSION);
    DuplicateString(&m_platformInfo.dateOfManufacture, DATE_OF_MANUFACTURE);

    DuplicateString(&m_platformInfo.modelNumber, "1");
    DuplicateString(&m_platformInfo.platformVersion, "1");
    DuplicateString(&m_platformInfo.hardwareVersion, "edison");
    DuplicateString(&m_platformInfo.firmwareVersion, "ostro");
    DuplicateString(&m_platformInfo.supportUrl, "fennec.tech");
    DuplicateString(&m_platformInfo.systemTime, "moscow");


    result = OCPlatform::registerPlatformInfo(m_platformInfo);
    if(result != OC_STACK_OK)
    {
        std::cout << "Platform Registration failed\n";
    }
    cout << "OK!" << endl;

    cout <<"Register the device... ";
    //DuplicateString(&m_deviceInfo.deviceName, DEVICE_NAME);
    //OCResourcePayloadAddStringLL(&m_deviceInfo.types, "oic.wk.d");
    //OCResourcePayloadAddStringLL(&m_deviceInfo.types, "oic.d.weeder");

    //result = OCPlatform::registerDeviceInfo(m_deviceInfo);

    if(result != OC_STACK_OK)
    {
        std::cout << "Device Registration failed\n";
    }
    cout << "OK!" <<endl;
}

WeederIoTServer::WeederIoTServer() {
    initPlatform();
    setupResources();
}

WeederIoTServer::~WeederIoTServer() {
    cout << "Stop weeder server" << endl;

    delete[] m_platformInfo.platformID;
    delete[] m_platformInfo.manufacturerName;
    delete[] m_platformInfo.manufacturerUrl;
    delete[] m_platformInfo.dateOfManufacture;
    delete[] m_platformInfo.operatingSystemVersion;
    delete[] m_platformInfo.systemTime;
    delete[] m_platformInfo.modelNumber;
    delete[] m_platformInfo.supportUrl;
    delete[] m_platformInfo.firmwareVersion;
    delete[] m_platformInfo.hardwareVersion;
    delete[] m_platformInfo.platformVersion;

    //delete[] m_deviceInfo.deviceName;
}

void WeederIoTServer::showSensors() {
    cout << "\tTemperature_1: " <<   m_MRAA->getTemperatureInC (TEMP1_A_PIN) << endl;
    cout << "\tTemperature_2: " <<   m_MRAA->getTemperatureInC (TEMP2_A_PIN) << endl;
    cout << "\tMoist_1: " <<   m_MRAA->getMoistPercent(MOIST1_A_PIN) << endl;
    cout << "\tMoist_2: " <<   m_MRAA->getMoistPercent(MOIST2_A_PIN) << endl;
}

float WeederIoTServer::getData(int pin_num) {
    mraa_aio_context a_pin = mraa_aio_init(pin_num);
    return mraa_aio_read(a_pin);
}

void WeederIoTServer::setLog(const char *log_file) {
    //TODO: set log file name
}

void WeederIoTServer::setupResources() {

    m_MRAA = make_shared<MRAASystem>();

    WeederSensor sensor = addSensor("temperature1", TEMPERATURE1_RESOURCE_ENDPOINT, TEMPERATURE_RESOURCE_TYPE, TEMPERATURE_RESOURCE_KEY, TEMP1_A_PIN);
    if(sensor == NULL) cout<<"Error adding temperature sensor #1" << endl;
    sensor = addSensor("temperature2", TEMPERATURE2_RESOURCE_ENDPOINT, TEMPERATURE_RESOURCE_TYPE, TEMPERATURE_RESOURCE_KEY, TEMP2_A_PIN);
    if(sensor == NULL) cout<<"Error adding temperature sensor #2" << endl;

    sensor = addSensor("moist1", MOIST1_RESOURCE_ENDPOINT, MOIST_RESOURCE_TYPE, MOIST_RESOURCE_KEY, MOIST1_A_PIN);
    if(sensor == NULL) cout<<"Error adding moist sensor #1" << endl;

    sensor = addSensor("moist2", MOIST2_RESOURCE_ENDPOINT, MOIST_RESOURCE_TYPE, MOIST_RESOURCE_KEY, MOIST2_A_PIN);
    if(sensor == NULL) cout<<"Error adding moist sensor #2" << endl;
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



shared_ptr<CSensor> WeederIoTServer::addSensor(string name, string end_point, string sensor_type, string resource_key, int pin) {
    shared_ptr<CSensor> sensor;
    IoTObserverCb tempObsCb;
    EntityHandler cb;
    //cout << "Add a sensor::\tName: " << name << "\n\tResource key: " << resource_key << "\n\tType: " << sensor_type <<endl;
    if(sensor_type == TEMPERATURE_RESOURCE_TYPE) {
        sensor = make_shared<TemperatureSensor>(name, pin);
        tempObsCb = bind(&TemperatureSensor::observerLoop, (TemperatureSensor*)sensor.get());
        cb = bind(&TemperatureSensor::entityHandler, (TemperatureSensor*)sensor.get(), placeholders::_1);

    } else if(sensor_type == MOIST_RESOURCE_TYPE) {
        sensor = make_shared<MoistSensor>(name, pin);
        tempObsCb = bind(&MoistSensor::observerLoop, (MoistSensor*)sensor.get());
        cb = bind(&MoistSensor::entityHandler, (MoistSensor*)sensor.get(), placeholders::_1);

    } else {
        cout << "Undefined type of sensor!"<<endl;
        cout << "\tName: " << name << "\n\tResource key: " << resource_key << "\n\tType: " << sensor_type <<endl;
        //throw error
        return NULL;
    }

    sensor->setMRAA(m_MRAA);
    sensor->m_ObserverLoop = make_shared<WeederObserver>(tempObsCb);

    createResource(end_point, sensor_type, cb,sensor->m_Handle);

    m_sensors[name] = sensor;
    return sensor;
}















