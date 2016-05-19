//
// Created by ubuntu on 19.05.16.
//

#include "CSensor.h"

CSensor::CSensor(string name, int pin):m_Name(name), m_Pin(pin), m_MRAA(NULL) {
}

CSensor::~CSensor() {
}

void CSensor::setMRAA(shared_ptr<MRAASystem> mraa) {
    m_MRAA = mraa;
}









