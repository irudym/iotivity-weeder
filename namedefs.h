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

#ifndef WEEDER_NAMEDEFS_H
#define WEEDER_NAMEDEFS_H


#define EDISON_RESOURCE_INTERFACE "oic.if.r"

#define TEMPERATURE_RESOURCE_TYPE "core.temperature"
#define TEMPERATURE1_RESOURCE_ENDPOINT "/temperature/1"
#define TEMPERATURE2_RESOURCE_ENDPOINT "/temperature/2"
#define TEMPERATURE_RESOURCE_KEY "temperature"

#define MOIST_RESOURCE_TYPE "core.humidity" // core.moist
#define MOIST1_RESOURCE_ENDPOINT "/humidity/1" // /moist
#define MOIST2_RESOURCE_ENDPOINT "/humidity/2" // /moist
#define MOIST_RESOURCE_KEY "humidity"       // /moist


//platfrom description
#define MANUFACTURER_NAME "fennec"
#define MANUFACTURER_URL "fennec.tech"
#define PLATFORM_ID "d5a36f31-9426-46e1-aa8f-3b48fc60334f"
#define OS_VERSION "ostro"
#define DEVICE_NAME "weeder"
#define DATE_OF_MANUFACTURE "08/05/2016"


#endif //WEEDER_NAMEDEFS_H
