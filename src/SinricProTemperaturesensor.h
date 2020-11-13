/****************************************************************************************************************************
  SinricProTemperatureSensor.h - Sinric Pro Library for boards

  Based on and modified from SinricPro libarary (https://github.com/sinricpro/)
  to support other boards such as  SAMD21, SAMD51, Adafruit's nRF52 boards, etc.

  Built by Khoi Hoang https://github.com/khoih-prog/SinricPro_Generic
  Licensed under MIT license
  Version: 2.7.4

  Copyright (c) 2019 Sinric. All rights reserved.
  Licensed under Creative Commons Attribution-Share Alike (CC BY-SA)

  This file is part of the Sinric Pro (https://github.com/sinricpro/)

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  2.4.0   K Hoang      21/05/2020 Initial porting to support SAMD21, SAMD51 nRF52 boards, such as AdaFruit Itsy-Bitsy,
                                  Feather, Gemma, Trinket, Hallowing Metro M0/M4, NRF52840 Feather, Itsy-Bitsy, STM32, etc.
  2.5.1   K Hoang      02/08/2020 Add support to STM32F/L/H/G/WB/MP1. Add debug feature, examples. Restructure examples.
                                  Sync with SinricPro v2.5.1: add Speaker SelectInput, Camera. Enable Ethernetx lib support.
  2.6.1   K Hoang      15/08/2020 Sync with SinricPro v2.6.1: add AirQualitySensor, Camera Class.
  2.7.0   K Hoang      06/10/2020 Sync with SinricPro v2.7.0: Added AppKey, AppSecret and DeviceId classes and RTT function.
  2.7.4   K Hoang      12/11/2020 Sync with SinricPro v2.7.4. Add WIO Terminal support and examples
 *****************************************************************************************************************************/

#ifndef _SINRIC_PRO_TEMPERATURESENSOR_H_
#define _SINRIC_PRO_TEMPERATURESENSOR_H_

#include "SinricProDevice.h"

/**
   @class SinricProTemperaturesensor
   @brief Device to report actual temperature and humidity
*/
class SinricProTemperaturesensor :  public SinricProDevice 
{
  public:
    SinricProTemperaturesensor(const DeviceId &deviceId);
    
    // From v2.5.1
    String getProductType() 
    {
      return SinricProDevice::getProductType() + String("TEMPERATURESENSOR"); 
    }
    //////

    // event
    bool sendTemperatureEvent(float temperature, float humidity = -1, String cause = "PERIODIC_POLL");

  private:
};

SinricProTemperaturesensor::SinricProTemperaturesensor(const DeviceId &deviceId) : SinricProDevice(deviceId) {}

/**
   @brief Sending current temperature and humidity to SinricPro server

   @param   temperature   float representing current temperature
   @param   humidity      (optional) float representing current humidity (default = `-1` meaning not supported)
   @param   cause         (optional) `String` reason why event is sent (default = `"PERIODIC_POLL"`)
   @return  the success of sending the event
   @retval  true          event has been sent successfully
   @retval  false         event has not been sent, maybe you sent to much events in a short distance of time
 **/
bool SinricProTemperaturesensor::sendTemperatureEvent(float temperature, float humidity, String cause) 
{
  DynamicJsonDocument eventMessage = prepareEvent(deviceId, "currentTemperature", cause.c_str());
  JsonObject event_value = eventMessage["payload"]["value"];
  event_value["humidity"] = roundf(humidity * 10) / 10.0;
  event_value["temperature"] = roundf(temperature * 10) / 10.0;
  return sendEvent(eventMessage);
}

#endif    //_SINRIC_PRO_TEMPERATURESENSOR_H_

