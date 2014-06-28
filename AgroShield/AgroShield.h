/*
  AgroShield.h - Library for AgroShield.
  Created by Jorge Mendes, June 07, 2014.
*/

#ifndef AgroShield_h
#define AgroShield_h

#include "Arduino.h"
#include <Wire.h>
#include <FreqPeriod.h>
#include <SDI12.h>
#include "RTClib.h"

#define	SENS_FREQUENCY 		1
#define SENS_VOLTAGE_1		2
#define SENS_VOLTAGE_2		3
#define	SENS_CURRENT_1		4
#define	SENS_CURRENT_2		5
#define	SENS_I2C			6
//#define SENS_SDI12			#
#define	CHECK_ALL			8
#define	WILD_CARD			9
#define SIMPLE_LOGGER		10
#define INTERFACE			11

#define	DATAPIN	9



class AgroShield
{
  public:
	
//Funções AgroShield
    AgroShield();
	float readSensor(uint8_t sensor);
	float readSensor(uint8_t sensor, int address, int num_bytes);
	//float readFreq(int f_comp_value, int gatetime);
	//float readFreq();
	//float readCurrent1();
	//float readCurrent2();
	//float readI2C(int address);
	
//Funções para SDI-12
	void SDI12(uint8_t mode);
	char printInfo(char i);
	byte charToDec(char i);
	char decToChar(byte i);
	boolean checkActive(char i);
	boolean isTaken(byte i);
	boolean setTaken(byte i);
	boolean setVacant(byte i);
	
//Funções para Simple_Logger do SDI-12
	void takeMeasurement(char i);
	void printBufferToScreen();

//Funções para RTC
	void getDateTime();
	void setDateTime();
	
  private:
	//int _f_comp_value;
	//int _gatetime;
	//unsigned long frq;
	double lfrq;
	long int period;
	float valor1;
	float voltage1;
	float valor2;
	float voltage2;
	float valor11;
	float voltage11;
	float current1;
	float valor22;
	float voltage22;
	float current2;
	int _address;
	int _num_bytes;
	float value;
	float buffer;
};

#endif