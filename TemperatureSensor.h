//
// Created by ubuntu on 19.05.16.
//

#ifndef IOTIVITY_WEEDER_TEMPERATURESENSOR_H
#define IOTIVITY_WEEDER_TEMPERATURESENSOR_H


#include "CSensor.h"
#include "sensors.h"
#include "namedefs.h"

class TemperatureSensor : public CSensor {
public:
    TemperatureSensor(const string &name, int pin) : CSensor(name, pin) {
        this->m_Representation.setValue(TEMPERATURE_RESOURCE_KEY, 0);
    }
    virtual ~TemperatureSensor() { }

    virtual OCRepresentation getRepresentation();
    virtual void observerLoop();
    virtual OCEntityHandlerResult entityHandler(shared_ptr<OCResourceRequest>);
};


#endif //IOTIVITY_WEEDER_TEMPERATURESENSOR_H
