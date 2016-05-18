//
// Created by ubuntu on 12.05.16.
//

#include "WeederObserver.h"


WeederObserver::WeederObserver(IoTObserverCb Cb):m_callback(Cb), m_destroy(false), m_started(false) {
    m_observerThread[0] = thread(&WeederObserver::observerThread, this);
}

WeederObserver::~WeederObserver() {
    terminate();
}

void WeederObserver::start() {
    if (!m_started)
    {
        {
            lock_guard<mutex> lock(m_mutex);
            m_started = true;
        }
        m_cond.notify_one();
    }
}

void WeederObserver::stop() {
    m_started = false;
}

void WeederObserver::terminate() {
    m_destroy = true;
    stop();
    m_cond.notify_one();
    m_observerThread[0].join();
}

void WeederObserver::observerThread()
{
    while (!m_destroy)
    {
        unique_lock<mutex> lock(m_mutex);
        if (!m_started)
            m_cond.wait(lock);
        while (m_started)
        {
            m_callback();
        }
    }
}