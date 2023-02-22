#define MOTION_TIMEOUT 5

struct DEV_MotionSensor : Service::MotionSensor {

  int sensorPin;
  SpanCharacteristic *motion;
  
  DEV_MotionSensor(int sensorPin) : Service::MotionSensor(){

    new SpanToggle(sensorPin);

    this->sensorPin = sensorPin;
    motion = new Characteristic::MotionDetected(false);
  }

  uint32_t motionTimeout = 0;

  void loop(){
    if (motionTimeout > 0 && millis() > motionTimeout) {
      motion->setVal(0);
      LOG1("Motion timeout\n");  
      motionTimeout = 0;          
    }
  }

  void button(int pin, int pressType) override {
    if (pressType == SpanToggle::CLOSED) {
      motionTimeout = millis() + MOTION_TIMEOUT * 1000;
      if (!motion->getVal()) {
        motion->setVal(1);
        LOG1("Motion updated!\n");
      } else {
        LOG1("Motion detected but not updated\n");
      }
    }
  }
  
};