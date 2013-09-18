#include "DHT.h"
//#include <Wire.h>

#define DHTPIN A2
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

//#include "I2C_Anything.h"
typedef struct {
  float h;
  float t;
} Vals;
Vals v;

void setup()
{
//  Wire.begin(5);
//  Wire.onRequest(requestEvent);
  dht.begin();
}

void loop()    
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  getValues();
  delay(100);
}

void getValues()
{
  v.h = dht.readHumidity();
  v.t = dht.readTemperature();
}

void requestEvent()
{
  if (isnan(v.t) || isnan(v.h))
  {
//    Wire.write(0);
  } else
  {
//    I2C_writeAnything(v);
  }
}

