
#define dht_apin A0 // Analog Pin sensor is connected to
#include "dht.h"
#include <SPI.h>
#include <SD.h>

File myFile;
int quarterTime = 0;
dht DHT;

int LED7 = 7;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  pinMode(LED7, OUTPUT);
  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("readings.csv", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to datas.txt...");
    // close the file:
    myFile.println("Minutes;Temperature;Humidity");
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening datas.txt");
  }
}

void loop() {
    digitalWrite(LED7, HIGH);
    
    Serial.println("Time");
    quarterTime = quarterTime + 1;
    Serial.println(quarterTime);
    
    myFile = SD.open("readings.csv", FILE_WRITE);
    DHT.read11(dht_apin);

      // if the file opened okay, write to it:
  if (myFile) {

    if(quarterTime%4 == 0){
      Serial.println("Clock hour");
    }
    
    myFile.print(quarterTime * 15);
    myFile.print(";");
    myFile.print(DHT.temperature);
    myFile.print(";");
    myFile.println(DHT.humidity);
    // close the file:
    myFile.close();

    Serial.println("Datas");
    Serial.println(DHT.temperature);
    Serial.println(DHT.humidity);
    Serial.println("Writing done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening readings.csv");
  }

  
  delay(1000);                       // wait for a second
  digitalWrite(LED7, LOW);    // turn the LED off by making the voltage LOW
  Serial.println("Delay 900000");
  delay(900000);
}
