/*
  This software is licensed under a Creative Commons Attribution-ShareAlike 3.0 Unported License
  Attribution-ShareAlike
  CC BY-SA 
  
  serial functions, example for MCP7940 rtc library
  version 1.0 / 2014/01/27
  http://smi.aii.pub.ro/arduino.html
*/

#include <Wire.h>
#include <MCP7940.h>

int rtc[7];

void setup()
{
  Wire.begin();
  SerialUSB.begin(9600);
}

void loop()
{
  RTCind.SetOutput(HIGH);
  SerialUSB.print("07h HIGH: ");
  SerialUSB.println (RTCind.GetOutput(),BIN);
  delay(5000);
  RTCind.SetOutput(LOW);
  SerialUSB.print("07h LOW: ");
  SerialUSB.println (RTCind.GetOutput(),BIN);
  delay(5000);
  RTCind.SetOutput(MCP7940_SQW1HZ);
  SerialUSB.print("07h MCP7940_SQW1HZ: ");
  SerialUSB.println (RTCind.GetOutput(),BIN);
  delay(5000);
  RTCind.SetOutput(MCP7940_SQW4KHZ);
  SerialUSB.print("07h MCP7940_SQW4KHZ: ");
  SerialUSB.println (RTCind.GetOutput(),BIN);
  delay(5000);
  RTCind.SetOutput(MCP7940_SQW8KHZ);
  SerialUSB.print("07h MCP7940_SQW8KHZ: ");
  SerialUSB.println (RTCind.GetOutput(),BIN);
  delay(5000);
  RTCind.SetOutput(MCP7940_SQW32KHZ);
  SerialUSB.print("07h MCP7940_SQW32KHZ: ");
  SerialUSB.println (RTCind.GetOutput(),BIN);
  delay(5000);
  RTCind.SetOutput(MCP7940_SQW64KHZ);
  SerialUSB.print("07h MCP7940_SQW64KHZ: ");
  SerialUSB.println (RTCind.GetOutput(),BIN);
  delay(5000);
}