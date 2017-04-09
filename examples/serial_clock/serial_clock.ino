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
  SerialUSB.begin(9600);
  
  RTC.get(rtc,true); 
  // the following 7 lines are used to set the time,
  // only upload this code once uncommented to set the time,
  // afterwards comment these lines out and upload again.
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
     SerialUSB.print("LUN ");
     break;
   case 2: 
     SerialUSB.print("MAR ");
     break;
   case 3: 
     SerialUSB.print("MIE ");
     break;
   case 4: 
     SerialUSB.print("JOI ");
     break;
   case 5: 
     SerialUSB.print("VIN ");
     break;
   case 6: 
     SerialUSB.print("SAM ");
     break;
   case 7: 
     SerialUSB.print("DUM ");
     break;
  }

  SerialUSB.print(rtc[4], DEC);
  SerialUSB.print(" ");
  switch (rtc[5]) {
   case 1: 
     SerialUSB.print("ian");
     break;
   case 2: 
     SerialUSB.print("feb");
     break;
   case 3: 
     SerialUSB.print("mar");
     break;
   case 4: 
     SerialUSB.print("apr");
     break;
   case 5: 
     SerialUSB.print("mai");
     break;
   case 6: 
     SerialUSB.print("iun");
     break;
   case 7: 
     SerialUSB.print("iul");
     break;
   case 8: 
     SerialUSB.print("aug");
     break;
   case 9: 
     SerialUSB.print("sep");
     break;
   case 10: 
     SerialUSB.print("oct");
     break;
   case 11: 
     SerialUSB.print("noi");
     break;
   case 12: 
     SerialUSB.print("dec");
     break;
  }
  SerialUSB.print(" ");
  SerialUSB.println(rtc[6], DEC);
  if (rtc[2]<10) SerialUSB.print("0");
  SerialUSB.print(rtc[2], DEC);
  SerialUSB.print(":");
  if (rtc[1]<10) SerialUSB.print("0");
  SerialUSB.print(rtc[1], DEC);
  SerialUSB.print(":");
  if (rtc[0]<10) SerialUSB.print("0");
  SerialUSB.println(rtc[0], DEC);
  SerialUSB.println();
  delay(5000);
}

