#include <stdint.h>
#include <Arduino.h>

class MyClass
{
public:
  int32_t buf;
};

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  MyClass myObj;
  myObj.buf = 23;
  Serial.println(myObj.buf);
  delay(100);
}
