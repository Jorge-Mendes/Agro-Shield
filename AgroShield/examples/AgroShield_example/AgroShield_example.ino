#include <AgroShield.h>
#include <FreqCounter.h>
#include <Wire.h>
#include <FreqPeriod.h>
#include <SDI12.h>
#include "RTClib.h"

AgroShield mysensors;

void setup()
{
  Serial.begin(9600);
  
  //////////////////////////////////////////////////////////////////////
  //    ACTUALIZAR DATA E HORA (DESCOMENTAR CASO QUEIRA ATUALIZAR)    //
  //////////////////////////////////////////////////////////////////////
  //mysensors.setDateTime();
}

void loop()
{
  ///////////////////////////////////////////////////////////////
  //             LEITURA DA INTERFACE DE FREQUÊNCIA            //
  ///////////////////////////////////////////////////////////////
  float valorfreq = mysensors.readSensor(SENS_FREQUENCY);
  mysensors.getDateTime();
  Serial.print("Freq: ");
  Serial.print(valorfreq);
  Serial.println(" Hz\n");
  delay(100);
  
  ///////////////////////////////////////////////////////////////
  //            LEITURA DA INTERFACE DE CORRENTE 1             //
  ///////////////////////////////////////////////////////////////
  float valorcurrente1 = mysensors.readSensor(SENS_CURRENT_1);
  mysensors.getDateTime();
  Serial.print("Current 1: ");
  Serial.print(valorcurrente1*1000);
  Serial.println(" mA\n");
  delay(100);
  
  ///////////////////////////////////////////////////////////////
  //            LEITURA DA INTERFACE DE CORRENTE 2             //
  ///////////////////////////////////////////////////////////////
  float valorcurrente2 = mysensors.readSensor(SENS_CURRENT_2);
  mysensors.getDateTime();
  Serial.print("Current 2: ");
  Serial.print(valorcurrente2*1000);
  Serial.println(" mA\n");
  delay(100);
  
  ///////////////////////////////////////////////////////////////
  //             LEITURA DA INTERFACE DE TENSÃO 1              //
  ///////////////////////////////////////////////////////////////
  float valortensao1 = mysensors.readSensor(SENS_VOLTAGE_1);
  mysensors.getDateTime();
  //Serial.print("Voltage 1: ");
  //Serial.print(valortensao1);
  //Serial.println(" V\n");
  float temperatura = valortensao1*100;
  Serial.print(temperatura);
  Serial.print(" ");
  Serial.print((char)176);
  Serial.println("C\n");
  delay(100);
  
  ///////////////////////////////////////////////////////////////
  //             LEITURA DA INTERFACE DE TENSÃO 2              //
  ///////////////////////////////////////////////////////////////
  float valortensao2 = mysensors.readSensor(SENS_VOLTAGE_2);
  mysensors.getDateTime();
  Serial.print("Voltage 2: ");
  Serial.print(valortensao2);
  Serial.println(" V\n");
  delay(100);
  
  ///////////////////////////////////////////////////////////////
  //                 LEITURA DA INTERFACE I2C                  //
  ///////////////////////////////////////////////////////////////
  float valori2c = mysensors.readSensor(SENS_I2C,0x68,1);
  mysensors.getDateTime();
  Serial.print("I2C: ");
  Serial.println(valori2c);
  Serial.println("");
  delay(100);
  
  ///////////////////////////////////////////////////////////////
  //               LEITURAS DA INTERFACE SDI-12                //
  ///////////////////////////////////////////////////////////////
  mysensors.SDI12(WILD_CARD);

  mysensors.SDI12(CHECK_ALL);

  mysensors.SDI12(SIMPLE_LOGGER);

  mysensors.SDI12(INTERFACE);
  
  ///////////////////////////////////////////////////////////////
  //       FAZ UMA PAUSA DE 10 SEGUNDOS ATÉ NOVA MEDIÇÃO       //
  ///////////////////////////////////////////////////////////////
  delay(1000);
  Serial.println("------------------- | ------------------------------------------------------------------------\n");
}

