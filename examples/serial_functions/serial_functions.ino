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
}

void loop()
{
  RTC.SetOutput(HIGH);
  Serial.print("07h HIGH: ");
  Serial.println (RTC.GetOutput(),BIN);
  delay(5000);
  RTC.SetOutput(LOW);
  Serial.print("07h LOW: ");
  Serial.println (RTC.GetOutput(),BIN);
  delay(5000);
  RTC.SetOutput(MCP7940_SQW1HZ);
  Serial.print("07h MCP7940_SQW1HZ: ");
  Serial.println (RTC.GetOutput(),BIN);
  delay(5000);
  RTC.SetOutput(MCP7940_SQW4KHZ);
  Serial.print("07h MCP7940_SQW4KHZ: ");
  Serial.println (RTC.GetOutput(),BIN);
  delay(5000);
  RTC.SetOutput(MCP7940_SQW8KHZ);
  Serial.print("07h MCP7940_SQW8KHZ: ");
  Serial.println (RTC.GetOutput(),BIN);
  delay(5000);
  RTC.SetOutput(MCP7940_SQW32KHZ);
  Serial.print("07h MCP7940_SQW32KHZ: ");
  Serial.println (RTC.GetOutput(),BIN);
  delay(5000);
  RTC.SetOutput(MCP7940_SQW64KHZ);
  Serial.print("07h MCP7940_SQW64KHZ: ");
  Serial.println (RTC.GetOutput(),BIN);
  delay(5000);
}

