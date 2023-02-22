struct DEV_LED : Service::LightBulb {

  int relayPin;
  int buttonPin;
  SpanCharacteristic *power;
  
  DEV_LED(int relayPin, int buttonPin) : Service::LightBulb(){

    new SpanToggle(buttonPin);

    power = new Characteristic::On();
    this->relayPin = relayPin;
    this->buttonPin = buttonPin;
    pinMode(relayPin, OUTPUT);
  }

  boolean update() {            
    digitalWrite(relayPin, power->getNewVal());
    return(true);
  }

  void button(int pin, int pressType) {
    if (pressType == SpanToggle::CLOSED) {
      LOG0("button pressed");
      digitalWrite(relayPin, !power->getVal());
      power->setVal(!power->getVal());
    }
  }
};