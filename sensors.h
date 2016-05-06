//
// Created by ubuntu on 05.05.16.
//

#ifndef IOTIVITY_WEEDER_SENSORS_H
#define IOTIVITY_WEEDER_SENSORS_H

#include <stdlib.h>
#include <math.h>
#include "mraa.h"

#define TEMP1_A_PIN 0
#define TEMP2_A_PIN 1
#define MOIST1_A_PIN 2
#define MOIST2_A_PIN 3

#define SAMPLE_NUM 5

namespace Sensors {
    mraa_aio_context tmp1_aio = NULL;
    mraa_aio_context tmp2_aio = NULL;
    mraa_aio_context moist1_aio = NULL;
    mraa_aio_context moist2_aio = NULL;

    inline void setupPins() {
        //Initialize AIO pins
        cout << "Setup pins:" << endl;
        cout << "TEMP1_PIN ...";
        tmp1_aio = mraa_aio_init(TEMP1_A_PIN);   // initialize pin 0
        if(tmp1_aio != NULL) cout << "OK" << endl; else cout << "FAIL!" << endl;
        cout << "TEMP2_PIN ...";
        tmp2_aio = mraa_aio_init(TEMP2_A_PIN);   // initialize pin 2
        if(tmp2_aio != NULL) cout << "OK" << endl; else cout << "FAIL!" << endl;

        cout << "MOIST1_PIN ...";
        moist1_aio = mraa_aio_init(MOIST1_A_PIN);
        if(moist1_aio != NULL) cout << "OK" << endl; else cout << "FAIL!" << endl;
        cout << "MOIST2_PIN ...";
        moist2_aio = mraa_aio_init(MOIST2_A_PIN);
        if(moist2_aio != NULL) cout << "OK" << endl; else cout << "FAIL!" << endl;
    }

    inline void closePins() {
        mraa_aio_close(tmp1_aio);
        mraa_aio_close(tmp2_aio);
        mraa_aio_close(moist1_aio);
        mraa_aio_close(moist2_aio);
    }

    inline float getAverageDataRaw(int sensor)
    {
        mraa_aio_context pin;

        pin = NULL;
        switch(sensor) {
            case TEMP1_A_PIN: pin = tmp1_aio; break;
            case TEMP2_A_PIN: pin = tmp2_aio; break;
            case MOIST1_A_PIN: pin = moist1_aio; break;
            case MOIST2_A_PIN: pin = moist2_aio; break;
        }

        if (pin == NULL)
        {
            return 0;
        }

        uint16_t adc_value = 0;
        for (int i=0; i< SAMPLE_NUM; i++)
            adc_value += mraa_aio_read(pin);           // read the raw value

        float average = (float)adc_value/SAMPLE_NUM;
        //cout << "Temperature reading raw ..."  << average << endl;

        return average;
    }

    inline float getTemperatureInC(int sensor)
    {
        // Temperature calculation using simpilfy Steinhart-Hart equation
        //
        //          1/T = 1/T0 + 1/beta*ln (R/R0)
        //
        // where T0 = 25C room temp, R0 = 10000 ohms
        //
        float beta = 4090.0;            //the beta of the thermistor, magic number
        float t_raw = getAverageDataRaw(sensor);
        float R = 1023.0/t_raw -1;      //
        R = 10000.0/R;                  // 10K resistor divider circuit

        float T1 = log(R/10000.0)/beta; // natural log
        float T2 = T1 + 1.0/298.15;     // room temp 25C= 298.15K
        float ret = 1.0/T2 - 273.0;

        return ret;
    }


    inline float getMoistPercent(int sensor) {
        float m_raw = getAverageDataRaw(sensor);
        return m_raw/400*100;
    }
}


#endif //IOTIVITY_WEEDER_SENSORS_H
