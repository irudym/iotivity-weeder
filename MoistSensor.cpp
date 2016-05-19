//
// Created by ubuntu on 19.05.16.
//

#include "MoistSensor.h"

OCRepresentation MoistSensor::getRepresentation() {
    if(m_MRAA == NULL) {
        //throw exception
        return m_Representation;
    }
    float temp = m_MRAA->getMoistPercent(m_Pin);
    m_Representation.setValue(MOIST_RESOURCE_KEY, temp);
    return m_Representation;
}

void MoistSensor::observerLoop() {
    usleep(3000000); //sleep 3 sec

    shared_ptr<OCResourceResponse> resourceResponse(new OCResourceResponse());
    resourceResponse->setErrorCode(200);
    resourceResponse->setResourceRepresentation(getRepresentation(), EDISON_RESOURCE_INTERFACE);

    try {
        OCStackResult result = OCPlatform::notifyListOfObservers(m_Handle,
                                                                 m_Observers,
                                                                 resourceResponse);
        if (result == OC_STACK_NO_OBSERVERS) {
            cout << "[Sensor: " << m_Name << "]:: No more observers..Stopping observer loop..." << endl;
            m_ObserverLoop->stop();
        } else if(result!=OC_STACK_OK) {
            cout << "[Sensor: " << m_Name << "]:: error during notifying observers: " << result << endl;
        }

    } catch(OCException& e)  {
        cout << "[MoistSensor]::Exception during notifying observers" << e.what()<< endl;
        //m_ObserverLoop->stop();
    }
}

OCEntityHandlerResult MoistSensor::entityHandler(shared_ptr<OCResourceRequest> Request) {
    OCEntityHandlerResult result = OC_EH_ERROR;
    //cout << "[MoistSensor]:: call for sensor: " << m_Name << endl;
    if(Request) {
        string requestType = Request->getRequestType();
        int requestFlag = Request->getRequestHandlerFlag();

        if(requestFlag & RequestHandlerFlag::RequestFlag) {
            auto Response = make_shared<OC::OCResourceResponse>();
            Response->setRequestHandle(Request->getRequestHandle());
            Response->setResourceHandle(Request->getRequestHandle());

            if(requestType == "GET") {
                //cout << "GET request for " << m_Name << " reading" << endl;
                if(Response) {
                    Response->setErrorCode(200);
                    Response->setResponseResult(OC_EH_OK);

                    Response->setResourceRepresentation(getRepresentation());

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
                cout << "Staring observer for " << m_Name << " sensor" << endl;

                m_Observers.push_back(observationInfo.obsId);
                m_ObserverLoop->start();

                //TODO: here should be the problem with result value
            }
            else if (ObserveAction::ObserveUnregister == observationInfo.action)
            {
                cout << "Stopping observer for " << m_Name << " sensor" << endl;

                m_Observers.erase(remove(m_Observers.begin(), m_Observers.end(), observationInfo.obsId), m_Observers.end());
                m_ObserverLoop->stop();

            }
        }
    }
    return result;
}







