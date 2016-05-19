//
// Created by ubuntu on 19.05.16.
//

#ifndef IOTIVITY_WEEDER_MOISTSENSOR_H
#define IOTIVITY_WEEDER_MOISTSENSOR_H

#include "CSensor.h"
#include "sensors.h"
#include "namedefs.h"

class MoistSensor : public CSensor {

public:
    MoistSensor(const string &name, int pin) : CSensor(name, pin) {
        this->m_Representation.setValue(MOIST_RESOURCE_KEY, 0);
    }
    virtual ~MoistSensor() { }

    virtual OCRepresentation getRepresentation();
    virtual void observerLoop();
    virtual OCEntityHandlerResult entityHandler(shared_ptr<OCResourceRequest>);
};


#endif //IOTIVITY_WEEDER_MOISTSENSOR_H
