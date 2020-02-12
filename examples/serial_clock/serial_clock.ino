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

MCP7940 mcp_rtc;
int rtc[7];

void setup()
{
  Wire.begin();
  SerialUSB.begin(9600);
  
  mcp_rtc.get(rtc,true); 
  // the following 7 lines are used to set the time,
  // only upload this code once uncommented to set the time,
  // afterwards comment these lines out and upload again.
  mcp_rtc.set(MCP7940_SEC,0);
  mcp_rtc.set(MCP7940_MIN,13);
  mcp_rtc.set(MCP7940_HR,18);
  mcp_rtc.set(MCP7940_DOW,1);
  mcp_rtc.set(MCP7940_DATE,27);
  mcp_rtc.set(MCP7940_MTH,1);
  mcp_rtc.set(MCP7940_YR,14);
  
  // true for MCP7940N vith back-up battery
  // false for MCP7940M or MCP7940N vith VBAT connected to ground 
  mcp_rtc.start(true);
}

void loop()
{
  mcp_rtc.get(rtc,true);

  switch (rtc[3]) {
   case 1: 
     SerialUSB.print("MON ");
     break;
   case 2: 
     SerialUSB.print("TUE ");
     break;
   case 3: 
     SerialUSB.print("WED ");
     break;
   case 4: 
     SerialUSB.print("THU ");
     break;
   case 5: 
     SerialUSB.print("FRI ");
     break;
   case 6: 
     SerialUSB.print("SAT ");
     break;
   case 7: 
     SerialUSB.print("SUN ");
     break;
  }

  SerialUSB.print(rtc[4], DEC);
  SerialUSB.print(" ");
  switch (rtc[5]) {
   case 1: 
     SerialUSB.print("jan");
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
     SerialUSB.print("may");
     break;
   case 6: 
     SerialUSB.print("jun");
     break;
   case 7: 
     SerialUSB.print("jul");
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
     SerialUSB.print("nov");
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
  delay(1000);
}
