//Code-Transmitter Side:
#include "Wire.h"       //For communicate
#include "I2Cdev.h"     //For communicate with MPU6050
#include "MPU6050.h"    //The main library of the MPU6050
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
RH_ASK driver;
MPU6050 mpu;
int16_t ax, ay, az,gx, gy, gz;
//Define packet for the direction (X axis and Y axis)
int data[2];
void setup()
{
    Wire.begin();
    mpu.initialize();      //Initialize the MPU object    
    driver.init();
}
void loop(){       
    data[0] = map(ax, -17000, 17000, 300, 400 ); //Send X axis data
    data[1] = map(ay, -17000, 17000, 100, 200);  //Send Y axis data  
    mpu.getMotion6(&ax, &ay, &az ,&gx, &gy, &gz);    
    if(data[0] > 380){ //on1
    const char *msg = "a";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    Serial.print("Command Sent ");
    Serial.print("Light_on ");    
    }

    if(data[0] < 310){ //off 1
    const char *msg = "b";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    Serial.print("Command Sent ");
    Serial.print("Light_off ");    
    }
    if(data[1] > 180){ //on2
    const char *msg = "c";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    Serial.print("Command Sent ");
    Serial.print("Fan_on ");    
    }
    if(data[1] < 110){
    const char *msg = "d";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    Serial.println("Command Sent ");
    Serial.print("Fan_off ");    
    }
}
