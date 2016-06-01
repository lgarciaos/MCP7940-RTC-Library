/*
  This software is licensed under a Creative Commons Attribution-ShareAlike 3.0 Unported License
  Attribution-ShareAlike
  CC BY-SA 
  
  serial clock, example for MCP7940 rtc library
  version 1.0 / 2014/01/27
  http://smi.aii.pub.ro/arduino.html
*/

#include <Wire.h>
#include <MCP7940.h>

int rtc[7];

void setup()
{
  Serial.begin(9600);
  
  RTC.get(rtc,true);
  
  RTC.set(MCP7940_SEC,0);
  RTC.set(MCP7940_MIN,13);
  RTC.set(MCP7940_HR,18);
  RTC.set(MCP7940_DOW,1);
  RTC.set(MCP7940_DATE,27);
  RTC.set(MCP7940_MTH,1);
  RTC.set(MCP7940_YR,14);
  
  // true for MCP7940N vith back-up battery
  // false for MCP7940M or MCP7940N vith VBAT connected to ground 
  RTC.start(true);
}

void loop()
{
  RTC.get(rtc,true);

  switch (rtc[3]) {
   case 1: 
     Serial.print("LUN ");
     break;
   case 2: 
     Serial.print("MAR ");
     break;
   case 3: 
     Serial.print("MIE ");
     break;
   case 4: 
     Serial.print("JOI ");
     break;
   case 5: 
     Serial.print("VIN ");
     break;
   case 6: 
     Serial.print("SAM ");
     break;
   case 7: 
     Serial.print("DUM ");
     break;
  }

  Serial.print(rtc[4], DEC);
  Serial.print(" ");
  switch (rtc[5]) {
   case 1: 
     Serial.print("ian");
     break;
   case 2: 
     Serial.print("feb");
     break;
   case 3: 
     Serial.print("mar");
     break;
   case 4: 
     Serial.print("apr");
     break;
   case 5: 
     Serial.print("mai");
     break;
   case 6: 
     Serial.print("iun");
     break;
   case 7: 
     Serial.print("iul");
     break;
   case 8: 
     Serial.print("aug");
     break;
   case 9: 
     Serial.print("sep");
     break;
   case 10: 
     Serial.print("oct");
     break;
   case 11: 
     Serial.print("noi");
     break;
   case 12: 
     Serial.print("dec");
     break;
  }
  Serial.print(" ");
  Serial.println(rtc[6], DEC);
  if (rtc[2]<10) Serial.print("0");
  Serial.print(rtc[2], DEC);
  Serial.print(":");
  if (rtc[1]<10) Serial.print("0");
  Serial.print(rtc[1], DEC);
  Serial.print(":");
  if (rtc[0]<10) Serial.print("0");
  Serial.println(rtc[0], DEC);
  Serial.println();
  delay(5000);
}

