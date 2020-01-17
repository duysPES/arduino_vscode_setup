
/***
 * This is example header, use this space for general overview of what the contents
 * within this file does. For example:
 * 
 * Reads from Analog pin and changes blinking rate of connected LED depending on 
 * analog value. Lower value equates to slow blinking while faster blinking result in higher value.
 ***/

#include <stdint.h>
#include <Arduino.h>

#define M328P_LOWV (0)
#define M328P_HIGHV (1023)

typedef uint8_t Pin;
typedef long Baudrate;
typedef unsigned long AnalogValue;
typedef unsigned long ms;

class MicroController
{

private:
  int read()
  {
    return analogRead(this->AnalogPin);
  }

  // this toggles a pin based on current state. If it comes back high, it will
  // turn off, and vice-versa
  void toggle(Pin pin)
  {
    if (digitalRead(pin))
    {
      Serial.println("OFF");
      digitalWrite(pin, LOW);
    }
    else
    {
      Serial.println("ON");
      digitalWrite(pin, HIGH);
    }
  }

public:
  Pin AnalogPin,
      LED;
  Baudrate baud;
  AnalogValue raw, delay_time;

  // Constructor of this object, takes AnalogPin where values where be read
  // and led pin where the LED will be connected too.
  MicroController(Pin analogPin, Pin led, Baudrate baud)
  {
    this->AnalogPin = analogPin;
    this->LED = led;
    this->baud = baud;
  }

  // Initializes the Serial communication
  void init()
  {
    Serial.begin(this->baud);     // begin serial with baud rate
    pinMode(this->LED, OUTPUT);   // setup pin for output mode
    digitalWrite(this->LED, LOW); // turn LED off
  }

  // control blinking rate based on slowest seconds to fastest ms
  void control_blink(ms slow_s, ms fast_s)
  {
    this->raw = this->read();
    this->delay_time = map(this->raw, M328P_LOWV, M328P_HIGHV, slow_s, fast_s);
    this->toggle(this->LED);
  }
};

// declare global visible object of type MicroController, with parameters
MicroController uc(A0, LED_BUILTIN, 9600);

void setup()
{
  uc.init();
}

void loop()
{
  // begin blink control and vary blinking between 3 seconds and 0.1 seconds depending
  // on analog read value
  uc.control_blink(1000, 10);
  delay(uc.delay_time);
}
