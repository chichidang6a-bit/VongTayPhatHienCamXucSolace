#include <Wire.h>
#include "BluetoothSerial.h"
#define CHAN_NHIP 36     
#define CHAN_DA 39     
#define CHAN_NHIET 34   
#define CHAN_RUNG 25  
#define LED_XANH 2    
#define LED_DO 4        
BluetoothSerial BT;
int nhip=0,da=0;
float nhiet=0.0,stress=0.0;
const int nguong=70; 
void setup() 
{
  Serial.begin(115200);
  BT.begin("VONG_TAY_STRESS");
  pinMode(CHAN_RUNG, OUTPUT);
  pinMode(LED_XANH, OUTPUT);
  pinMode(LED_DO, OUTPUT);
  digitalWrite(CHAN_RUNG, LOW);
  digitalWrite(LED_XANH, LOW);
  digitalWrite(LED_DO, LOW);
}
void loop()
 {
  nhip=analogRead(CHAN_NHIP);
  da=analogRead(CHAN_DA);
  nhiet=(float)analogRead(CHAN_NHIET)*0.1;
  stress=0.5*(nhip/40.0)+0.3*(da/80.0)-0.2*nhiet;
  BT.print(nhip);
  BT.print(",");
  BT.print(da);
  BT.print(",");
  BT.print(nhiet);
  BT.print(",");
  BT.println(stress);
  if (stress>nguong) 
  {
    digitalWrite(LED_DO, HIGH);
    digitalWrite(LED_XANH, LOW);
    digitalWrite(CHAN_RUNG, HIGH);
    delay(500);
    digitalWrite(CHAN_RUNG, LOW);
  } 
  else 
  {
    digitalWrite(LED_DO, LOW);
    digitalWrite(LED_XANH, HIGH);
  }
  delay(1000);
}
