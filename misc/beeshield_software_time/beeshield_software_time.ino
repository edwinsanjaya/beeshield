
#define S4 A0 //MICRO
#define S3 A3 //SENS_2710
#define S2 A2 //SENS_5525

#define S5 A1 //LDR

#include "DHT.h"
DHT dht(A1, DHT22);

#include <Wire.h>
#include <RTClib.h>
RTC_Millis RTC;

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#include <SD.h>
File myFile;

void setup() {
  Serial.begin(9600);
  
  while (!Serial);
  sensors.begin();
  RTC.begin(DateTime(__DATE__, __TIME__));
}

void loop () {
  

  float h = dht.readHumidity();
  float t = dht.readTemperature();  

  DateTime now = RTC.now();
  String filename = "";
  filename += now.year();
  filename += '-';
  filename += now.month();
  filename += '-';
  filename += now.day();
  filename += '-';
  filename += now.hour();
  filename += '-';
  filename += now.minute();
  filename += ".csv";
  
  Serial.println(filename);
  
  char __dataFileName[sizeof(filename)];
  filename.toCharArray(__dataFileName, sizeof(__dataFileName));
  
  myFile = SD.open(__dataFileName, FILE_WRITE);
  if (myFile) {
//    myFile.print( sensors.requestTemperatures(); );
//    myFile.print(",");
    myFile.print(t);
    myFile.print(",");
    myFile.print(h);
    myFile.print(",");
    myFile.println(now.get());
  } else {
    Serial.println("FAIL");
  }
  myFile.close();

  delay(4000);
};
