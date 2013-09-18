#include "DHT.h"
DHT dht(13, DHT22);

#include <Wire.h>
#include <RTClib.h>
RTC_Millis RTC;

#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire0(5);
DallasTemperature sensor0(&oneWire0);

OneWire oneWire1(9);
DallasTemperature sensor1(&oneWire1);

OneWire oneWire2(10);
DallasTemperature sensor2(&oneWire2);

#include <SD.h>
File myFile;

void setup() {
  Serial.begin(9600);
  
  while (!Serial);

  if (!SD.begin(11)) {
    Serial.println("SD initialization failed!");
    return;
  }
  Serial.println("SD initialization done.");
  
  sensor0.begin();
  sensor1.begin();
  sensor2.begin();
  RTC.begin(DateTime(__DATE__, __TIME__));
}

void loop () {

  float h = dht.readHumidity();
  float t = dht.readTemperature();  

  DateTime now = RTC.now();
  String filename = "";
//  filename += now.year();
  String month = String(now.month());
  if (now.month() < 10) {
    month = "0" + month;
  }
  String day = String(now.day());
  if (now.day() < 10) {
    day = "0" + day;
  }
  String hour = String(now.hour());
  if (now.hour() < 10) {
    hour = "0" + hour;
  }
//  String minute = String(now.minute());
//  if (now.minute() < 10) {
//    minute = "0" + minute;
//  }
  filename += month;
  filename += day;
  filename += hour;
//  filename += minute;
  filename += ".csv";

  char __dataFileName[filename.length() + 1];
  filename.toCharArray(__dataFileName, sizeof(__dataFileName));
  Serial.println("");
  Serial.println(__dataFileName);
  
  myFile = SD.open(__dataFileName, FILE_WRITE);
  if (myFile) {
    sensor0.requestTemperatures();
    sensor1.requestTemperatures();
    sensor2.requestTemperatures();
    Serial.println(sensor0.getTempCByIndex(0));
    Serial.println(sensor1.getTempCByIndex(0));
    Serial.println(sensor2.getTempCByIndex(0));
    Serial.println(t);
    Serial.println(h);
    myFile.print(sensor0.getTempCByIndex(0));    
    myFile.print(",");
    myFile.print(sensor1.getTempCByIndex(0)); 
    myFile.print(",");
    myFile.print(sensor2.getTempCByIndex(0)); 
    myFile.print(",");
    myFile.print(t);
    myFile.print(",");
    myFile.print(h);
    myFile.print(",");
    myFile.println(now.get());
  } else {
    Serial.println("FAIL");
  }
  myFile.close();

  delay(12000);
};
