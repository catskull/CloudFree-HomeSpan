#include <Arduino.h>
#include "HomeSpan.h"
#include "dev_led.h"
#include "dev_motion.h"

#define LOG_LEVEL 0
#define PAIRING_CODE "88888888"

#define LED_STATUS 18
#define MOTION_SENSOR 13
#define BUTTON 26
#define RELAY 19

void setup() {
  // Serial.begin(115200);
  homeSpan.begin(Category::Lighting,"Motion Light Switch");
  homeSpan.enableAutoStartAP();
  homeSpan.setStatusPin(LED_STATUS);
  homeSpan.enableOTA(false);
  // homeSpan.setLogLevel(LOG_LEVEL);
  // homeSpan.setPairingCode(PAIRING_CODE);

  new SpanAccessory(); 
    new Service::AccessoryInformation(); 
      new Characteristic::Identify();
    new DEV_LED(RELAY, BUTTON);

  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Identify(); 
      new Characteristic::Name("Motion Sensor");
    new DEV_MotionSensor(MOTION_SENSOR);

  homeSpan.autoPoll();
}