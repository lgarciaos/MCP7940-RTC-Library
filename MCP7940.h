/*
  This software is licensed under a Creative Commons Attribution-ShareAlike 3.0 Unported License
  Attribution-ShareAlike
  CC BY-SA 
  
  MCP7940.h - library for MCP7940 rtc
  version 1.0 / 2014/01/27
  http://smi.aii.pub.ro/arduino.html
*/

// ensure this library description is only included once
#ifndef MCP7940_h
#define MCP7940_h

// include types & constants of Wiring core API
#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include <WProgram.h>
	#include <WConstants.h>
#endif

// include types & constants of Wire ic2 lib
#include "Wire.h"

#define MCP7940_SEC 0
#define MCP7940_MIN 1
#define MCP7940_HR 2
#define MCP7940_DOW 3
#define MCP7940_DATE 4
#define MCP7940_MTH 5
#define MCP7940_YR 6

#define MCP7940_BASE_YR 2000

#define MCP7940_SQW1HZ  7
#define MCP7940_SQW4KHZ 8
#define MCP7940_SQW8KHZ 9
#define MCP7940_SQW32KHZ 10
#define MCP7940_SQW64KHZ 11

#define MCP7940_CTRL_ID B1101111  //I2C address MCP7940

 // Define register bit masks
#define MCP7940_CLOCKHALT B01111111

#define MCP7940_LO_BCD  B00001111
#define MCP7940_HI_BCD  B11110000

#define MCP7940_HI_SEC  B01110000
#define MCP7940_HI_MIN  B01110000
#define MCP7940_HI_HR   B00110000
#define MCP7940_LO_DOW  B00000111
#define MCP7940_HI_DATE B00110000
#define MCP7940_HI_MTH  B00110000
#define MCP7940_HI_YR   B11110000


// Prescaler
#define MCP7940_LOW_BIT			B00000000
#define MCP7940_HIGH_BIT		B10000000
#define MCP7940_SQW1HZ_BIT		B00010000
#define MCP7940_SQW4KHZ_BIT		B00010001
#define MCP7940_SQW8KHZ_BIT		B00010010
#define MCP7940_SQW32KHZ_BIT	B00010011
#define MCP7940_SQW64KHZ_BIT	B00010100

// library interface description
class MCP7940
{
  // user-accessible "public" interface
  public:
    MCP7940();
    void get(int *, boolean);
    int get(int, boolean);
	void set(int, int);
    void start(boolean);
    void stop(void);
    void SetOutput(uint8_t);
	uint8_t GetOutput(void);
	
  // library-accessible "private" interface
  private:
    uint8_t rtc_bcd[7]; // used prior to read/set MCP7490 registers;
	uint8_t MCP7940_VBAT_MASK;
	void read(void);
	void save(void);
};

extern MCP7940 RTCind;

#endif
