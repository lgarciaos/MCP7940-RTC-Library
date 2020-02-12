/*
  This software is licensed under a Creative Commons Attribution-ShareAlike 3.0 Unported License
  Attribution-ShareAlike
  CC BY-SA 
  
  MCP7940.cpp - library for MCP7940 rtc
  version 1.0 / 2014/01/27
  http://smi.aii.pub.ro/arduino.html
*/

#include "Wire.h"
#include "MCP7940.h"

uint8_t MCP7940_VBAT_MASK=0;

MCP7940::MCP7940()
{
  Wire.begin();
}

// PRIVATE FUNCTIONS

// Aquire data from the RTC chip in BCD format
// refresh the buffer
void MCP7940::read(void)
{
  // use the Wire lib to connect to tho rtc
  // reset the resgiter pointer to zero
  Wire.beginTransmission(MCP7940_CTRL_ID);
  Wire.write((uint8_t)0x00);
  Wire.endTransmission();

  // request the 7 bytes of data    (secs, min, hr, dow, date. mth, yr)
  Wire.requestFrom(MCP7940_CTRL_ID, 7);
  for(int i=0; i<7; i++)
  {
    // store data in raw bcd format
    rtc_bcd[i]=Wire.read();
  }
}

// update the data on the IC from the bcd formatted data in the buffer
void MCP7940::save(void)
{
  Wire.beginTransmission(MCP7940_CTRL_ID);
  Wire.write((uint8_t)0x00); // reset register pointer
  for(int i=0; i<7; i++)
  {
	Wire.write(rtc_bcd[i]);
  }
  Wire.endTransmission();
}


// PUBLIC FUNCTIONS
void MCP7940::get(int *rtc, boolean refresh)   // Aquire data from buffer and convert to int, refresh buffer if required
{
  if(refresh) read();
  for(int i=0;i<7;i++)  // cycle through each component, create array of data
  {
	rtc[i]=get(i, 0);
  }
}

int MCP7940::get(int c, boolean refresh)  // aquire individual RTC item from buffer, return as int, refresh buffer if required
{
  if(refresh) read();
  int v=-1;
  switch(c)
  {
  case MCP7940_SEC:
    v=(10*((rtc_bcd[MCP7940_SEC] & MCP7940_HI_SEC)>>4))+(rtc_bcd[MCP7940_SEC] & MCP7940_LO_BCD);
	break;
  case MCP7940_MIN:
    v=(10*((rtc_bcd[MCP7940_MIN] & MCP7940_HI_MIN)>>4))+(rtc_bcd[MCP7940_MIN] & MCP7940_LO_BCD);
	break;
  case MCP7940_HR:
    v=(10*((rtc_bcd[MCP7940_HR] & MCP7940_HI_HR)>>4))+(rtc_bcd[MCP7940_HR] & MCP7940_LO_BCD);
	break;
  case MCP7940_DOW:
    v=rtc_bcd[MCP7940_DOW] & MCP7940_LO_DOW;
	break;
  case MCP7940_DATE:
    v=(10*((rtc_bcd[MCP7940_DATE] & MCP7940_HI_DATE)>>4))+(rtc_bcd[MCP7940_DATE] & MCP7940_LO_BCD);
	break;
  case MCP7940_MTH:
    v=(10*((rtc_bcd[MCP7940_MTH] & MCP7940_HI_MTH)>>4))+(rtc_bcd[MCP7940_MTH] & MCP7940_LO_BCD);
	break;
  case MCP7940_YR:
    v=(10*((rtc_bcd[MCP7940_YR] & MCP7940_HI_YR)>>4))+(rtc_bcd[MCP7940_YR] & MCP7940_LO_BCD)+MCP7940_BASE_YR;
	break;
  } // end switch
  return v;
}

void MCP7940::set(int c, int v)  // Update buffer, then update the chip
{
  switch(c)
  {
  case MCP7940_SEC:
    if(v<60 && v>-1)
    {
	//preserve existing clock state (running/stopped)
	int state=rtc_bcd[MCP7940_SEC] & MCP7940_CLOCKHALT;
	rtc_bcd[MCP7940_SEC]=state | ((v / 10)<<4) + (v % 10);
    }
    break;
  case MCP7940_MIN:
    if(v<60 && v>-1)
    {
	rtc_bcd[MCP7940_MIN]=((v / 10)<<4) + (v % 10);
    }
    break;
  case MCP7940_HR:
  // TODO : AM/PM  12HR/24HR
    if(v<24 && v>-1)
    {
	rtc_bcd[MCP7940_HR]=((v / 10)<<4) + (v % 10);
    }
    break;
  case MCP7940_DOW:
    if(v<8 && v>-1)
    {
	rtc_bcd[MCP7940_DOW]=v;
    }
	rtc_bcd[MCP7940_DOW]=rtc_bcd[MCP7940_DOW] | MCP7940_VBAT_MASK;
    break;
  case MCP7940_DATE:
    if(v<31 && v>-1)
    {
	rtc_bcd[MCP7940_DATE]=((v / 10)<<4) + (v % 10);
    }
    break;
  case MCP7940_MTH:
    if(v<13 && v>-1)
    {
	rtc_bcd[MCP7940_MTH]=((v / 10)<<4) + (v % 10);
    }
    break;
  case MCP7940_YR:
    if(v<80 && v>-1)
    {
	rtc_bcd[MCP7940_YR]=((v / 10)<<4) + (v % 10);
    }
    break;
  } // end switch
  save();
}

void MCP7940::stop(void)
{
	read();
	// set the ClockHalt bit high to stop the rtc
	// this bit is part of the seconds byte
    rtc_bcd[MCP7940_SEC]=rtc_bcd[MCP7940_SEC] & MCP7940_CLOCKHALT;
    save();
}

void MCP7940::start(boolean VBAT)
{
	if (VBAT) MCP7940_VBAT_MASK=B00001000;
	read();
	rtc_bcd[MCP7940_DOW]=rtc_bcd[MCP7940_DOW] | MCP7940_VBAT_MASK;
    rtc_bcd[MCP7940_SEC]=rtc_bcd[MCP7940_SEC] | (~MCP7940_CLOCKHALT);
	save();
}


void MCP7940::SetOutput(uint8_t c)  
{
  uint8_t out;
  switch(c)
  {
  // only 0.6V ???
  case HIGH :
	out=MCP7940_HIGH_BIT;
  break;
  case LOW :
	out=MCP7940_LOW_BIT;
  break;
  case MCP7940_SQW1HZ :
	out=MCP7940_SQW1HZ_BIT;
  break;
  case MCP7940_SQW4KHZ :
	out=MCP7940_SQW4KHZ_BIT;
  break;
  case MCP7940_SQW8KHZ :
	out=MCP7940_SQW8KHZ_BIT;
  break;
  case MCP7940_SQW32KHZ :
	out=MCP7940_SQW32KHZ_BIT;
  case MCP7940_SQW64KHZ :
	out=MCP7940_SQW64KHZ_BIT;
  break;
  // default: 
  //	out=MCP7940_LOW_BIT;
  }
  
  Wire.beginTransmission(MCP7940_CTRL_ID);
  Wire.write((uint8_t)0x07); 
  Wire.write(out);
  Wire.endTransmission();
}

uint8_t MCP7940::GetOutput(void)  
{
  Wire.beginTransmission(MCP7940_CTRL_ID);
  Wire.write((uint8_t)0x07);
  Wire.endTransmission();

  Wire.requestFrom(MCP7940_CTRL_ID, 1);
  uint8_t out=Wire.read();
  
/*  int c=-1;
  switch(out)
  {
  case MCP7940_HIGH_BIT :
	c=HIGH;
  break;
  case MCP7940_LOW_BIT :
	c=LOW;
  break;
  case MCP7940_SQW1HZ_BIT :
	c=MCP7940_SQW1HZ;
  break;
  case MCP7940_SQW4KHZ_BIT :
	c=MCP7940_SQW4KHZ;
  break;
  case MCP7940_SQW8KHZ_BIT :
	c=MCP7940_SQW8KHZ;
  break;
  case MCP7940_SQW32KHZ_BIT :
	c=MCP7940_SQW32KHZ;
  break;
  } */
  return out;
}
