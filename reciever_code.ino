//Code-Receiver Side:
#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile
#define light A0
#define fan A1
#define interval 1000
RH_ASK driver;
void setup()
{
  pinMode(light, OUTPUT);
    pinMode(fan, OUTPUT);
    Serial.begin(9600);	// Debugging only
    if (!driver.init())
         Serial.println("init failed");
}
void loop()
{
    uint8_t buf[1];
    uint8_t buflen =sizeof(buf) ;
    if (driver.recv(buf, &buflen))
    {
      
      // Message received with valid checksum
      Serial.print("Command Received =====");
      Serial.println((char*)buf); 
    }
    if (strcmp((char*)buf,"a")==0)
    {
      Serial.print("Light ON");
      digitalWrite(light,HIGH);  
      }
    if (strcmp((char*)buf,"b")==0)
    {
      digitalWrite(light,LOW);  
      Serial.print("Light OFF");
      }
    if (strcmp((char*)buf,"c")==0)
    {
      digitalWrite(fan,HIGH);
      Serial.print("Fan ON");  
      }
    if (strcmp((char*)buf,"d")==0)
    {
      digitalWrite(fan,LOW);  
      Serial.print("Fan OFF");
      }

  delay(interval);    
}
