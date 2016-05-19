//
// Created by ubuntu on 19.05.16.
//

#ifndef IOTIVITY_WEEDER_CSENSOR_H
#define IOTIVITY_WEEDER_CSENSOR_H

#include <string>
#include <iostream>
#include <memory>

#include "ocstack.h"
#include "WeederObserver.h"
#include "OCPlatform.h"
#include "OCApi.h"

#include "namedefs.h"
#include "sensors.h"


using namespace OC;
using namespace std;

class CSensor {
public:
    OCRepresentation m_Representation;
    OCResourceHandle m_Handle;
    ObservationIds m_Observers;
    shared_ptr<WeederObserver> m_ObserverLoop;
    string m_Name;
    int m_Pin;

    CSensor(string name, int pin);
    virtual ~CSensor();

    void setMRAA(shared_ptr<MRAASystem> mraa);

    virtual OCRepresentation getRepresentation() = 0;
    virtual void observerLoop() = 0;
    virtual OCEntityHandlerResult entityHandler(shared_ptr<OCResourceRequest>) = 0;
protected:
    shared_ptr<MRAASystem> m_MRAA;
};

typedef map<string, shared_ptr<CSensor>> TSensorMap;
typedef shared_ptr<CSensor> WeederSensor;

#endif //IOTIVITY_WEEDER_CSENSOR_H
