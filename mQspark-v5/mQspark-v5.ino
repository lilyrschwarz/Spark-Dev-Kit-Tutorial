#include "CayenneLPP.h"
#include "Ultrasonic.h"
#include <ByteConvert.hpp>
#include "SparkFunLSM6DS3.h"
#include "Wire.h"




CayenneLPP lpp(uint8_t size);

//*** ----> LoRa parameters here:
String  set_deveui = "BADDECAFC0FFE567"; // Put your 16 hex char here
String  set_appeui = "BADDECAFC0FFEE01"; // Put your 16 hex char here
String  set_appkey = "BADDECAFC0FFEE01BADDECAFC0FFEE01"; // Put your 32 hex char here
//*** <---- END LoRa parameters

//Include libraries
#include "mQspark-v5.h"



//*** Define in which port the temp sensor is plugged in ---->
int tempSensorPin = A2;     // Grove - Temperature Sensor connects to port closest to USB port
int soundSensorPin = A5;    // Grove - Sound Sensor connect to the second closed port.
int ultrasonicSensorPin = A0; // Grove - UltraSonic Sensor connect to the second closed port.
int accelandgyroSensorPin = SDA; //Grove - Accelerometer and Gyroscope Sensor

//Set device baud rate
long defaultBaudRate = 19200;


CayenneLPP cayenneLPP(128);

//Create a instance of class LSM6DS3 for Accelerometer and Gyroscope
LSM6DS3 myIMU( I2C_MODE, 0x6A );  //I2C device address 0x6A

void setup() {

  Serial.begin(115200);
  sparkStart(defaultBaudRate);
  mQjoin();
  myIMU.begin();

}

//Global variables
String payload = "";


void loop() {

    //These must be added individually.
    cayenneLPP.reset();
    cayenneLPP.addTemperature(0, sparkTemp(A2));
    cayenneLPP.addAnalogInput(1, sparkSound(A5));
    cayenneLPP.addAccelerometer(2, myIMU.readFloatAccelX(), myIMU.readFloatAccelY(), myIMU.readFloatAccelZ());
    cayenneLPP.addGyrometer(3, myIMU.readFloatGyroX(), myIMU.readFloatGyroY(), myIMU.readFloatGyroZ());
    cayenneLPP.addPresence(4, A0);

    Serial.println(sparkUltrasonic(A0));
    //Convert Byte Array to String
    String arrayAsString = ByteConvert::arrayToString(cayenneLPP.getSize(),cayenneLPP.getBuffer());

    String payload = arrayAsString;
    int payloadSize = payload.length()/2;

    //send LoRa packet
    mQsend(payloadSize, payload);
    delay(1000);
    read_data_from_LoRa_Mod();

    delay(10000);
}
