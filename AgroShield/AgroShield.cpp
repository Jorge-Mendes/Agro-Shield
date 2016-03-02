/*
  AgroShield.h - Library for AgroShield.
  Created by Jorge Mendes, June 07, 2014.
*/

#include "Arduino.h"
#include "AgroShield.h"
#include <Wire.h>
#include <FreqPeriod.h>
#include <SDI12.h>
#include "RTClib.h"

byte addressRegister[8] = { 
	0B00000000, 
	0B00000000, 
	0B00000000, 
	0B00000000, 
	0B00000000, 
	0B00000000, 
	0B00000000, 
	0B00000000 
};

String wild_card_Command = "?!";
boolean found = false;
boolean found_check_all = false;
String myCommand;
boolean estado = true;
String comandorecebido;

SDI12 mySDI12(DATAPIN);
RTC_DS1307 RTC;	

AgroShield::AgroShield()
{
}

//Medição da Frequência com FreqCounter.h
	//float AgroShield::readFreq(int f_comp_value, int gatetime)
	//{
	//	_f_comp_value = f_comp_value;
	//	_gatetime = gatetime;
	//	FreqCounter::f_comp = _f_comp_value;	// Set compensation to 12
	//	FreqCounter::start(_gatetime);			// Start counting with gatetime of 100ms
	//	
	//	while (FreqCounter::f_ready == 0)		// wait until counter ready
	// 
	//	frq=FreqCounter::f_freq;				// read result
	//
	//	return frq;
	//}

float AgroShield::readSensor(uint8_t sensor)
{
	switch( sensor )
	{
		case	SENS_FREQUENCY	:	FreqPeriod::begin();
									period=FreqPeriod::getPeriod();
									if (period ){

		//							Serial.print("Período: ");
		//							Serial.print(period);
		//							Serial.print(" 1/16us  /  Frequência: ");

									lfrq= 16000400.0 / period;
									
		//							Serial.print("VALOR DA FREQUENCIA: ");
		//							Serial.print(lfrq);
		
									return lfrq;
									}
									break;
									
									
		case	SENS_VOLTAGE_1	:	analogRead(A0);
									delay(50);
									for (int i = 0; i < 100; i++){
										buffer += analogRead(A0);
									}
									//valor1=analogRead(A0);
									valor1 = buffer/100;
		//							Serial.println(valor1);
									voltage1 = valor1 * (5.0 / 1023.0);
									buffer = 0;
									return voltage1;
									break;


		case	SENS_VOLTAGE_2	:	analogRead(A1);
									delay(50);
									for (int i = 0; i < 100; i++){
										buffer += analogRead(A1);
									}
									//valor2=analogRead(A1);
									valor2 = buffer/100;
		//							Serial.println(valor1);
									voltage2 = valor2 * (5.0 / 1023.0);
									buffer = 0;
									return voltage2;
									break;										


		case	SENS_CURRENT_1	:	analogRead(A2);
									delay(50);
									for (int i = 0; i < 100; i++){
										buffer += analogRead(A2);
									}
									//valor11=analogRead(A2);
									valor11 = buffer/100;
		//							Serial.println(valor1);
									voltage11 = valor11 * (5.0 / 1023.0);
									current1 = voltage11 / 250;
									buffer = 0;
									return current1;
									break;

									
		case	SENS_CURRENT_2	:	analogRead(A3);
									delay(50);
									for (int i = 0; i < 100; i++){
										buffer += analogRead(A3);
									}
									//valor22=analogRead(A3);
									valor22 = buffer/100;
		//							Serial.println(valor2);
									voltage22 = valor22 * (5.0 / 1023.0);
									current2 = voltage22 / 250;
									buffer = 0;
									return current2;
									break;												

									
		default					:	;							
	}
}


float AgroShield::readSensor(uint8_t sensor, int address, int num_bytes)
{
	switch( sensor )
	{
	case	SENS_I2C		:	Wire.begin();
								_address = address;
								_num_bytes=num_bytes;
								Wire.beginTransmission(_address);
								// Envia um bit e um ack para o registo zero.
								Wire.write(0);
								// Termina a transmissão.
								Wire.endTransmission();
								// Solicita "_num_bytes" bytes do endereço "_address".
								Wire.requestFrom(_address, _num_bytes);
								// Espera por uma resposta.
								while(Wire.available() == 0);
								// Coloca a medição na variável "value".
								value = Wire.read();
//								value = 555;
								return value;
								break;

	
	default					:	;							
	}
}





////////////////////////////////////////////////////////////////////////////
////////////////////////////////// SDI-12 //////////////////////////////////
////////////////////////////////////////////////////////////////////////////


void AgroShield::SDI12(uint8_t mode)
{
	switch( mode )
	{
	case	CHECK_ALL			:	mySDI12.begin(); 
									delay(500); 						// Tempo para que mySDI12 seja iniciado.
									
									/*
										Efectua um Scan rápido de todos os endereços.
									*/
									Serial.println("                    | SEARCH FOR SENSORS");
									Serial.println("                    | Scanning all addresses, please wait...");
									for(byte i = '0'; i <= '9'; i++) if(checkActive(i)) setTaken(i);   // Scan dos endereços entre 0-9

									for(byte i = 'a'; i <= 'z'; i++) if(checkActive(i)) setTaken(i);   // Scan dos endereços entre a-z

									for(byte i = 'A'; i <= 'Z'; i++) if(checkActive(i)) setTaken(i);   // Scan dos endereços entre A-Z

									/*
										Imprime a informação actual de cada sensor activo.
									*/
								  
									// Scan dos endereços entre 0-9
									for(char i = '0'; i <= '9'; i++) if(isTaken(i)){
									
										Serial.println("");
										getDateTime();
										found_check_all = true;
									
										Serial.print("Sensor ");
										Serial.print(i);
										Serial.print(":");
										printInfo(i);   
										//Serial.println(); 
									}
								  
									// Scan dos endereços entre a-z
									for(char i = 'a'; i <= 'z'; i++) if(isTaken(i)){
									
										Serial.println("");
										getDateTime();
										found_check_all = true;
									
										Serial.print("Sensor ");
										Serial.print(i);
										Serial.print(": ");
										printInfo(i);   
										//Serial.println(); 
									} 
								  
									// Scan dos endereços entre A-Z
									for(char i = 'A'; i <= 'Z'; i++) if(isTaken(i)){
									
										Serial.println("");
										getDateTime();
										found_check_all = true;
									
										Serial.print("Sensor ");
										Serial.print(i);
										Serial.print(":");
										printInfo(i);   
										//Serial.println();  
									};
									
									
									
									if(!found_check_all) {
										Serial.println("                    | No sensors found, please check connections and restart the Arduino.\n"); 
										//while(true);
										//break;
									} // stop here
									
									
									
									mySDI12.end();
									delay(500);
									found_check_all = false;
									break;

									
	case	WILD_CARD			:	mySDI12.begin();
									delay(500);							// Tempo para que mySDI12 seja iniciado.
									mySDI12.sendCommand(wild_card_Command); 
									delay(300);							// Espera um tempo pela resposta.
									Serial.println("                    | SENSORS CONNECTED");
									getDateTime();
									
									while(mySDI12.available()){			// Escreve a resposta no Serial Monitor.
										Serial.write(mySDI12.read());
										
										//Serial.print("                    | ");
										
									}
									Serial.println("");
									mySDI12.end();
									delay(500);
									break;
									
									
	case	SIMPLE_LOGGER		:	mySDI12.begin();
									delay(500); 						// Tempo para que mySDI12 seja iniciado.
									//////////////////////////////////////////////
									Serial.println();
									Serial.println("                    | SENSORS INFORMATION AND MEASUREMENTS "); 
									Serial.println("                    | Scanning all addresses, please wait..."); 
									
									/*
									  Efectua um Scan rápido de todos os endereços.
									*/

									for(byte i = '0'; i <= '9'; i++) if(checkActive(i)) setTaken(i);   // Scan dos endereços entre 0-9

									for(byte i = 'a'; i <= 'z'; i++) if(checkActive(i)) setTaken(i);   // Scan dos endereços entre a-z

									for(byte i = 'A'; i <= 'Z'; i++) if(checkActive(i)) setTaken(i);   // Scan dos endereços entre A-Z

									/*
									  Verificar se existem sensores activos.
									*/
									
//									for(byte i = 0; i < 62; i++){
//										if(isTaken(i)){
//										  found = true;
//										  break;
//										}
//									}
									
									for(char i = '0'; i <= '9'; i++){
										if(isTaken(i)){
											found = true;
											
											//Serial.print("Checking address ");
											//Serial.print(i);
											//Serial.print("..."); 
											
											break;
										}
									}
									for(char i = 'a'; i <= 'z'; i++){
										if(isTaken(i)){
											found = true;
											
											//Serial.print("Checking address ");
											//Serial.print(i);
											//Serial.print("..."); 
											
											break;
										}
									}
									for(char i = 'A'; i <= 'Z'; i++){
										if(isTaken(i)){
											found = true;
											
											//Serial.print("Checking address ");
											//Serial.print(i);
											//Serial.print("..."); 
											
											break;
										}
									}

									if(!found) {
										Serial.println("                    | No sensors found, please check connections and restart the Arduino.\n"); 
										//while(true);
										break;
									} // stop here

									Serial.println();
									Serial.println("                    | Time Elapsed (s), Sensor Address and ID");
									Serial.println("                    | Sensor Address, Measurement 1, Measurement 2, ... etc."); 
									Serial.println("                    | -------------------------------------------------------------------------------");
									//////////////////////////////////////////////
									// Scan dos endereços entre 0-9
									for(char i = '0'; i <= '9'; i++) if(isTaken(i)){
									
										getDateTime();
									
										Serial.print(millis()/1000);
										Serial.print(",");
										printInfo(i); 

										//getDateTime();
										
										takeMeasurement(i);
										
										Serial.println("");
									}

									// Scan dos endereços entre a-z
									for(char i = 'a'; i <= 'z'; i++) if(isTaken(i)){
									
										getDateTime();
									
										Serial.print(millis()/1000);
										Serial.print(",");
										printInfo(i); 

										//getDateTime();
										
										takeMeasurement(i);
										
										Serial.println("");
									} 

									// Scan dos endereços entre A-Z
									for(char i = 'A'; i <= 'Z'; i++) if(isTaken(i)){
									
										getDateTime();
									
										Serial.print(millis()/1000);
										Serial.print(",");
										printInfo(i); 

										//getDateTime();
										
										takeMeasurement(i);
										
										Serial.println("");
									};   
									//////////////////////////////////////////////
									mySDI12.end();
									delay(500);
									break;									

	case	INTERFACE			:	mySDI12.begin();
									delay(500);							// Tempo para que mySDI12 seja iniciado.
									mySDI12.sendCommand("");
									
									Serial.println("                    | INTERFACE COM SENSORES SDI-12");
									Serial.println("                    | Insira o comando a enviar (''exit'' para sair)...");
									Serial.println("");
									
									while(estado){
										if(Serial.available() > 0)
										{
											myCommand = Serial.readStringUntil('\n');
											//x = Serial.parseInt();

											if (myCommand == "exit")
											{
											  Serial.println("                    | Saiu do envio de comandos");
											  Serial.println("");
											  estado = false;
											}

											if (estado){    
												//if ( (myCommand[0] >= '0' && myCommand[0] <= '9' || myCommand[0] >= 'a' && myCommand[0] <= 'z' || 
												//myCommand[0] >= 'A' && myCommand[0] <= 'Z' || myCommand[0] == '?') && (myCommand[1] == 'I' || 
												//myCommand[1] == 'M' || myCommand[1] == 'D' || myCommand[1] == 'A') && (myCommand[2] == '!' || 
												//(myCommand[3] == '!' && (myCommand[2] >= '0' && myCommand[2] <= '9' || myCommand[2] >= 'a' && 
												//myCommand[2] <= 'z' || myCommand[2] >= 'A' && myCommand[2] <= 'Z')) ) )
												if ( (myCommand[0] >= '0' && myCommand[0] <= '9' || myCommand[0] >= 'a' && myCommand[0] <= 'z' || 
												myCommand[0] >= 'A' && myCommand[0] <= 'Z' || myCommand[0] == '?') && (myCommand[1] == '!' || 
												myCommand[1] == 'I' || myCommand[1] == 'M' || myCommand[1] == 'D' || myCommand[1] == 'A') && 
												(myCommand[1] == '!' || myCommand[2] == '!' || (myCommand[3] == '!' && (myCommand[2] >= '0' && 
												myCommand[2] <= '9' || myCommand[2] >= 'a' && myCommand[2] <= 'z' || myCommand[2] >= 'A' && 
												myCommand[2] <= 'Z')) ) ) 
												{

													getDateTime();
													Serial.println(myCommand);

													for(int j = 0; j < 1; j++){
													  mySDI12.sendCommand(myCommand);
													  //      mySDI12.flush();
													  delay(300); 
													  if(mySDI12.available()>1) break;
													  if(mySDI12.available()) mySDI12.read(); 
													}

													delay(300);


													//mySDI12.read(); //consume sensor address (you can keep it if you'd like)

													if(mySDI12.available()){
														getDateTime();
													}
													
//													while(mySDI12.available()){
//														comandorecebido = (String)mySDI12.read();
//														if(comandorecebido == "\n"){
//															Serial.println("                    | ");
//															Serial.println(comandorecebido);
//														}
//														Serial.println(comandorecebido);
//														delay(5); 
//													}
													
													while(mySDI12.available()){
														Serial.write(mySDI12.read()); 
														delay(5); 
													}
													
													Serial.println("");
												}

												else{
													Serial.println("                    | Comando Invalido");
													Serial.println("");
												}
											}
										}
									}
									

//									if(!estado)
//										while(!estado){
//											if(Serial.available() > 0)
//											{
//												myCommand = Serial.readStringUntil('\n');
//												//if (myCommand == "run sdi monitor")
//												if (myCommand == "run")
//												{      
//													estado = true;
//													Serial.println("Entrou do envio de comandos");  
//												}
//											}
//										}
																		
								
									
									mySDI12.end();
									delay(500);
									estado = true;
									break;
									
									
									
	default						:	;							
	}
}







// Verificação da actividade de um determinado endereço.
// Espera um caracter entre '0'-'9', 'a'-'z', ou 'A'-'Z'.
boolean AgroShield::checkActive(char i){              
  //Serial.print("Checking address ");
  //Serial.print(i);
  //Serial.print("..."); 
  String myCommand = "";
  myCommand = "";
  myCommand += (char) i;                 // Envia um comando de 'acknowledge' - [address][!].
  myCommand += "!";

  for(int j = 0; j < 3; j++){            // Efectua  três tentativas rápidas de contacto.
    mySDI12.sendCommand(myCommand);
    if(mySDI12.available()>1) break;
    delay(30); 
  }
  if(mySDI12.available()>2){       		// Define o endereço como ocupado (occupied) (if it hears anything it assumes the address is occupied).
    //Serial.println("Occupied");
    mySDI12.flush(); 
    return true;
  } 
  else {								// Caso contrário define-o como livre (vacant).
    //Serial.println("Vacant"); 
    mySDI12.flush(); 
  }
  return false; 
}


// Define o bit no local adequado dentro do addressRegister
// para guardar a informação de que o sensor está activo
// e o endereço é "tomado" (taken). 
boolean AgroShield::setTaken(byte i){          
  boolean initStatus = isTaken(i);
  i = charToDec(i); // e.g. convert '0' to 0, 'a' to 10, 'Z' to 61. 
  byte j = i / 8;   // byte #
  byte k = i % 8;   // bit #
  addressRegister[j] |= (1 << k); 
  //Serial.println("set taken");
  return !initStatus; // returna falso se já está "tomado" (already taken).
}


// ESTE MÉTODO NÃO É UTILIZADO NESTE EXEMPLO, MAS PODE SER ÚTIL.
// Desactiva o bit no local adequado dentro do addressRegister
// para guardar a informação de que o sensor está activo
// e o endereço é "tomado" (taken). 
boolean AgroShield::setVacant(byte i){
  boolean initStatus = isTaken(i);
  i = charToDec(i); // e.g. convert '0' to 0, 'a' to 10, 'Z' to 61. 
  byte j = i / 8;   // byte #
  byte k = i % 8;   // bit #
  addressRegister[j] &= ~(1 << k); 
  return initStatus; // returna falso se já esta livre (vacant).
}


// Verifica rapidamente se o endereço já foi utilizado por um sensor activo
boolean AgroShield::isTaken(byte i){         
  i = charToDec(i); // e.g. convert '0' to 0, 'a' to 10, 'Z' to 61. 
  byte j = i / 8;   // byte #
  byte k = i % 8;   // bit #
  //Serial.println("is taken");
  return addressRegister[j] & (1<<k); // return bit status
}


// Obtém a informação de identificação do sensor e imprime-a através da serial port
// Espera um caracter entre '0'-'9', 'a'-'z', ou 'A'-'Z'.
char AgroShield::printInfo(char i){
  int j; 
  String command = "";
  command += (char) i; 
  command += "I!";
  for(j = 0; j < 1; j++){
    mySDI12.sendCommand(command);
    delay(30); 
    if(mySDI12.available()>1) break;
    if(mySDI12.available()) mySDI12.read(); 
  }
  
  //mySDI12.read();		//"Consome" o endereço do sensor (pode mantê-lo se quiser).
  //Tem no Ckeck_All_Addresses e não tem no Simple_Logger
  
  while(mySDI12.available()){
    Serial.write(mySDI12.read()); 
    delay(5); 
  } 
}


// Conver-te os endereços permitidos ('0'-'9', 'a'-'z', 'A'-'Z'),
// num numero decimal entre 0 e 61 (inclusive) para "cobrir" os 62 endereços possíveis.
byte AgroShield::charToDec(char i){
  if((i >= '0') && (i <= '9')) return i - '0';
  if((i >= 'a') && (i <= 'z')) return i - 'a' + 10;
  if((i >= 'A') && (i <= 'Z')) return i - 'A' + 37;
}


// ESTE MÉTODO NÃO É UTILIZADO NESTE EXEMPLO, MAS PODE SER ÚTIL. 
// Mapeia os números decimais entre 0 e 61 (inclusive) para
// para os caracteres de endereço permitidos ('0'-'9', 'a'-'z', 'A'-'Z').
char AgroShield::decToChar(byte i){
  if((i >= 0) && (i <= 9)) return i + '0';
  if((i >= 10) && (i <= 36)) return i + 'a' - 10;
  if((i >= 37) && (i <= 62)) return i + 'A' - 37;
}


///////////////////// Mais funções para Simple_Logger /////////////////////

void AgroShield::takeMeasurement(char i){
  String command = ""; 
  command += i;
  command += "M!";		// Formato do comando de medição SDI-12 - [address]['M'][!]
  mySDI12.sendCommand(command); 
  while(!mySDI12.available()>5);	// Espera por um "acknowlegement" com o formato - [address][ttt (3 char, seconds)][number of measurments available (0-9)]
  delay(100); 
  
  //mySDI12.read();		//"Consome" o endereço do sensor.
  
  // Saber quanto tempo temos que esperar pela medição (em segundos).
  int wait = 0; 
  wait += 100 * mySDI12.read()-'0';
  wait += 10 * mySDI12.read()-'0';
  wait += 1 * mySDI12.read()-'0';
  
  mySDI12.read();	// Ignora as # medições, para este exemplo simples
  mySDI12.read();	// Ignora o Carriage Return
  mySDI12.read();	// Ignora o Line Feed
  
  long timerStart = millis(); 
  while((millis() - timerStart) > (1000 * wait)){
    if(mySDI12.available()) break;		// O sensor pode-nos "interromper" para sabermos que as medições estão completas.
  }
  
  // Neste exemplo apenas vamos fazer a medição de "DO".  
  mySDI12.flush(); 
  command = "";
  command += i;
  command += "D0!";		// Comando SDI-12 para obtenção de dados - [address][D][dataOption][!]
  mySDI12.sendCommand(command);
  while(!mySDI12.available()>1);		// Espera por um "acknowlegement".
  delay(300);		// Tempo de transferência de dados.
  //getDateTime();
  printBufferToScreen(); 
  mySDI12.flush(); 
}


void AgroShield::printBufferToScreen(){
  String buffer = "";
  //mySDI12.read(); 		// "Consome" o endereço do sensor.
  while(mySDI12.available()){
    char c = mySDI12.read();
    //if(c == '+' || c == '-'){						//Sustitui o ''+'' pela '',''
    //  buffer += ',';   
    //  if(c == '-') buffer += '-'; 
    //} 
    //else {
      buffer += c;  
    //}
    delay(100); 
  }
  getDateTime();
 Serial.print(buffer);
}




//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////


void AgroShield::getDateTime(){
boolean run = true;
  Wire.begin();
  RTC.begin();
  if (! RTC.isrunning()) {
    Serial.print("RTC is NOT running  | ");
	run = false;
  }
  if(run){
  // This section grabs the current datetime and compares it to
  // the compilation time.  If necessary, the RTC is updated.
  DateTime now = RTC.now();
  DateTime compiled = DateTime(__DATE__, __TIME__);
  //if (now.unixtime() < compiled.unixtime() || now.unixtime() > compiled.unixtime()) {
  if (now.unixtime() < compiled.unixtime() ) {
    //Serial.println("RTC is older than compile time! Updating");
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }

  //Serial.println("Setup complete.");
  delay(100);
  
  
  // Get the current time
   now = RTC.now();   

  // Display the current time
  //Serial.print("Current time: ");
  if (now.day() <= 9)
  {
    Serial.print("0");
    Serial.print(now.day(), DEC);
  }
  else{
    Serial.print(now.day(), DEC);
  }
  Serial.print('/');
  if (now.month() <= 9)
  {
    Serial.print("0");
    Serial.print(now.month(), DEC);
  }
  else{
    Serial.print(now.month(), DEC);
  }
  Serial.print('/');
  Serial.print(now.year(), DEC);

  Serial.print(' ');

  if (now.hour() <= 9)
  {
    Serial.print("0");
    Serial.print(now.hour(), DEC);
  }
  else{
    Serial.print(now.hour(), DEC);
  }
  Serial.print(':');
  if (now.minute() <= 9)
  {
    Serial.print("0");
    Serial.print(now.minute(), DEC);
  }
  else{
    Serial.print(now.minute(), DEC);
  }
  Serial.print(':');
  if (now.second() <= 9)
  {
    Serial.print("0");
    Serial.print(now.second(), DEC);
	Serial.print(" | ");
  }
  else{
    Serial.print(now.second(), DEC);
	Serial.print(" | ");
  }

  delay(100);
  }
}




void AgroShield::setDateTime(){
Wire.begin();
  RTC.begin();
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running...");
  }
  // This section grabs the current datetime and compares it to
  // the compilation time.  If necessary, the RTC is updated.
  DateTime now = RTC.now();
  DateTime compiled = DateTime(__DATE__, __TIME__);
  if (now.unixtime() < compiled.unixtime() || now.unixtime() > compiled.unixtime()) {
    Serial.println("RTC is older than compile time! Updating");
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }

  Serial.println("Setup complete.");
  delay(100);

}
