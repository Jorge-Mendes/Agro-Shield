#include <SDI12.h>

#define _BUFFER_SIZE 64		
#define DISABLED 0
#define ENABLED 1
#define HOLDING 2
#define TRANSMITTING 3
#define LISTENING 4
#define SPACING 830	

#define DATAPIN 9 

SDI12 mySDI12(DATAPIN); 

String comandorecebido = "";
//int g = 1;
int i = 0;

int led = 13;

char sensor1 = 'a';
char sensor2 = 'b';
char sensor3 = 'c';
char sensor4 = 'd';
char sensor5 = 'e';
char sensor6 = 'f';
char sensor7 = 'g';
char sensor8 = 'h';

void setup(){
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW); 
  mySDI12.begin(); 
  delay(500); // allow things to settlev
  setState(LISTENING);
}


void setState(uint8_t state){
  if(state == HOLDING){
    pinMode(DATAPIN,OUTPUT);
    digitalWrite(DATAPIN,LOW);
    *digitalPinToPCMSK(DATAPIN) &= ~(1<<digitalPinToPCMSKbit(DATAPIN));
    return; 
  }
  if(state == TRANSMITTING){
    pinMode(DATAPIN,OUTPUT);
    noInterrupts(); 			// supplied by Arduino.h, same as cli()
    return; 
  }
  if(state == LISTENING) {
    digitalWrite(DATAPIN,LOW);
    pinMode(DATAPIN,INPUT); 
    interrupts();				// supplied by Arduino.h, same as sei()
    *digitalPinToPCICR(DATAPIN) |= (1<<digitalPinToPCICRbit(DATAPIN));
    *digitalPinToPCMSK(DATAPIN) |= (1<<digitalPinToPCMSKbit(DATAPIN));
  } 
  else { 						// implies state==DISABLED 
    digitalWrite(DATAPIN,LOW); 
    pinMode(DATAPIN,INPUT);
    *digitalPinToPCMSK(DATAPIN) &= ~(1<<digitalPinToPCMSKbit(DATAPIN));
    if(!*digitalPinToPCMSK(DATAPIN)){
      *digitalPinToPCICR(DATAPIN) &= ~(1<<digitalPinToPCICRbit(DATAPIN));
    }
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////


void loop(){



  //Serial.println(mySDI12.read()); //consume sensor address (you can keep it if you'd like)
  while(mySDI12.available()){


    comandorecebido += (char) mySDI12.read();

    //String comandoreceb = comandorecebido;
    //Serial.print("-");
    //Serial.println(comandoreceb);
    if (comandorecebido[i] == '!' && i > 2){
      //    Serial.println("comando completo");
      Serial.println(comandorecebido);
      //Serial.println(comandorecebidobackup);
      //for (i = 0; i < comandorecebido.length(); i++){
      //
      //	Serial.write(comandorecebido[i]);
      //        Serial.println();
      //        
      //        comandorecebido = " ";						// escreve cada caractere
      //  }
      //  comandorecebido = " ";	
      //  i=0;
    }

    //g++;
    //      if (mySDI12.read() == 'a')
    //      if (mySDI12.read() == 'I')
    //      if (mySDI12.read() == '!')


    //////////////////////////   Serial.write("enconctrado\n");
    // Serial.print("-----------------------------------------");

    // if ((comandorecebido[i-1] == 'a' || comandorecebido[i-1] == 't' || comandorecebido[i-1] == 'K') && comandorecebido[i] == '!'){
    ////Serial.println("encontrou a!");
    // //  Serial.println(comandorecebidobackup);
    //   
    ////   if (mySDI12.read() == 'I')
    // ////////////////////////////  Serial.write("Pedido de Informação\n");
    //   
    //
    ////   int j; 
    ////  String command = "";
    //
    //  //command += "a"; 
    //
    // // String command = "<CR><LF>";
    ////for(j = 0; j < 1; j++){
    //   // setState(TRANSMITTING);
    //    mySDI12.sendCommand("<CR><LF>");
    //    setState(LISTENING);
    ///////////////////////    Serial.print(command);
    ////delay(30);
    //
    //   
    //   
    //   
    //   // }
    ////   delay(20.5);
    // }
    // 


    if (comandorecebido[i-1] == sensor1 && comandorecebido[i] == '!'){
      setState(TRANSMITTING);
      //mySDI12.sendCommand(sensor1 + "\r\n");
      mySDI12.sendCommand("\r\n");
      digitalWrite(led, HIGH);
      setState(LISTENING);
    }
    if ( comandorecebido[i-1] == sensor2 && comandorecebido[i] == '!'){
      setState(TRANSMITTING);
      //mySDI12.sendCommand(sensor2 + "\r\n");
      mySDI12.sendCommand("\r\n");
      setState(LISTENING);
    }
    if ( comandorecebido[i-1] == sensor3 && comandorecebido[i] == '!'){
      setState(TRANSMITTING);
      //mySDI12.sendCommand(sensor3 + "\r\n");
      mySDI12.sendCommand("\r\n");
      setState(LISTENING);
    }
     if (comandorecebido[i-1] == sensor4 && comandorecebido[i] == '!'){
      setState(TRANSMITTING);
      //mySDI12.sendCommand(sensor4 + "\r\n");
      mySDI12.sendCommand("\r\n");
      setState(LISTENING);
    }
    if ( comandorecebido[i-1] == sensor5 && comandorecebido[i] == '!'){
      setState(TRANSMITTING);
      //mySDI12.sendCommand(sensor5 + "\r\n");
      mySDI12.sendCommand("\r\n");
      setState(LISTENING);
    }
    if ( comandorecebido[i-1] == sensor6 && comandorecebido[i] == '!'){
      setState(TRANSMITTING);
      //mySDI12.sendCommand(sensor6 + "\r\n");
      mySDI12.sendCommand("\r\n");
      setState(LISTENING);
    }
    if ( comandorecebido[i-1] == sensor7 && comandorecebido[i] == '!'){
      setState(TRANSMITTING);
      //mySDI12.sendCommand(sensor7 + "\r\n");
      mySDI12.sendCommand("\r\n");
      setState(LISTENING);
    }
    if ( comandorecebido[i-1] == sensor8 && comandorecebido[i] == '!'){
      setState(TRANSMITTING);
      //mySDI12.sendCommand(sensor8 + "\r\n");
      mySDI12.sendCommand("\r\n");
      setState(LISTENING);
    }



    //  if ((comandorecebido[i-1] == 'b') && comandorecebido[i] == '!'){
    //
    //    setState(TRANSMITTING);
    //    mySDI12.sendCommand("<CR><LF>");
    //    setState(LISTENING);
    //
    // }


//    //Serial.print("-----------------------------------------");
//    // Serial.println(i);
//    if ((comandorecebido[i-2] == 'a') && (comandorecebido[i-1] == 'I') && (comandorecebido[i] == '!') ){
//
//      // Serial.println("pedido de imformção");
//
//      //   if (mySDI12.read() == 'I')
//      ////////////////////////////  Serial.write("Pedido de Informação\n");
//
//      int z = 254;
//      //   int j; 
//      //  String command = "";
//      //  String command1 = "";
//      //command += "a"; 
//      //  command1 += (String) z;
//      String command = "013NRSYSINC1000001.2101\r\n";
//      //for(j = 0; j < 1; j++){
//      setState(TRANSMITTING);
//      //    mySDI12.sendCommand1(command1);
//      ///////////////////    Serial.print(command1);
//      mySDI12.sendCommand(command);
//      setState(LISTENING);
//      /////////////////////    Serial.print(command);
//      //delay(30) 
//      //  }
//      //   delay(20.5);
//    }


    ///////////////
    if ((comandorecebido[i-2] == sensor1) && (comandorecebido[i-1] == 'I') && (comandorecebido[i] == '!')){
      String command = "13NRSYSINC1000001.2101";
      setState(TRANSMITTING);
      mySDI12.sendCommand(sensor1 + command + "\r\n");
      digitalWrite(led, LOW);
      setState(LISTENING);
    }
    
    if ((comandorecebido[i-2] == sensor2) && (comandorecebido[i-1] == 'I') && (comandorecebido[i] == '!')){
      String command = "[COMPAT_N][COMPANY_NAME][MOD_N][SENS_VER][SERIAL_N]";
      setState(TRANSMITTING);
      mySDI12.sendCommand(sensor2 + command + "\r\n");
      setState(LISTENING);
    }
    
    if ((comandorecebido[i-2] == sensor3) && (comandorecebido[i-1] == 'I') && (comandorecebido[i] == '!')){
      String command = "[COMPAT_N][COMPANY_NAME][MOD_N][SENS_VER][SERIAL_N]";
      setState(TRANSMITTING);
      mySDI12.sendCommand(sensor3 + command + "\r\n");
      setState(LISTENING);
    }
    
    if ((comandorecebido[i-2] == sensor4) && (comandorecebido[i-1] == 'I') && (comandorecebido[i] == '!')){
      String command = "[COMPAT_N][COMPANY_NAME][MOD_N][SENS_VER][SERIAL_N]";
      setState(TRANSMITTING);
      mySDI12.sendCommand(sensor4 + command + "\r\n");
      setState(LISTENING);
    }
    
    if ((comandorecebido[i-2] == sensor5) && (comandorecebido[i-1] == 'I') && (comandorecebido[i] == '!')){
      String command = "[COMPAT_N][COMPANY_NAME][MOD_N][SENS_VER][SERIAL_N]";
      setState(TRANSMITTING);
      mySDI12.sendCommand(sensor5 + command + "\r\n");
      setState(LISTENING);
    }
    
    if ((comandorecebido[i-2] == sensor6) && (comandorecebido[i-1] == 'I') && (comandorecebido[i] == '!')){
      String command = "[COMPAT_N][COMPANY_NAME][MOD_N][SENS_VER][SERIAL_N]";
      setState(TRANSMITTING);
      mySDI12.sendCommand(sensor6 + command + "\r\n");
      setState(LISTENING);
    }
    
    if ((comandorecebido[i-2] == sensor7) && (comandorecebido[i-1] == 'I') && (comandorecebido[i] == '!')){
      String command = "[COMPAT_N][COMPANY_NAME][MOD_N][SENS_VER][SERIAL_N]";
      setState(TRANSMITTING);
      mySDI12.sendCommand(sensor7 + command + "\r\n");
      setState(LISTENING);
    }
    
    if ((comandorecebido[i-2] == sensor8) && (comandorecebido[i-1] == 'I') && (comandorecebido[i] == '!')){
      String command = "[COMPAT_N][COMPANY_NAME][MOD_N][SENS_VER][SERIAL_N]";
      setState(TRANSMITTING);
      mySDI12.sendCommand(sensor8 + command + "\r\n");
      setState(LISTENING);
    }
    ///////////////







    ///////////////
    if ((comandorecebido[i-3] == sensor1) && (comandorecebido[i-2] == 'D') && (comandorecebido[i] == '!')){
      //String command = "[COMPATIBILITY_NUMB][COMPANY_NAME][MODEL_NUMB][SENSOR_VERS][SERIAL_NUMB]";
      setState(TRANSMITTING);
      
      int pressure1 = 0;   
      int pressure2 = 0;
      
      String soma = "+";
      
      pressure1 = 500; //sensor output (mV)  
      pressure1 = ( pressure1 / ( 0.009 * 5 ) ) + ( 0.095 / 0.009 ); // kPa
      pressure1 = 25;
      pressure2 = 27;
      String command1 = (String) pressure1;
      String command2 = (String) pressure2;
      
      mySDI12.sendCommand(sensor1 + soma + command1 + soma + command2 + "\r\n");
      //mySDI12.sendCommand(sensor1 + "+" + command + "\r\n");
      digitalWrite(led, LOW);
      setState(LISTENING);
    }
    
    if ((comandorecebido[i-3] == sensor2) && (comandorecebido[i-2] == 'D') && (comandorecebido[i] == '!')){
      String command = "[VALUE]";
      String soma = "+";
      setState(TRANSMITTING);
      mySDI12.sendCommand(sensor2 + soma + command + soma + command + "\r\n");
      //mySDI12.sendCommand(sensor2 + "+" + command +  "+" + command + "\r\n");
      setState(LISTENING);
    }
    
    if ((comandorecebido[i-3] == sensor3) && (comandorecebido[i-2] == 'D') && (comandorecebido[i] == '!')){
      String command = "[VALUE]";
      String soma = "+";
      setState(TRANSMITTING);
      mySDI12.sendCommand(sensor3 + soma + command + "\r\n");
      //mySDI12.sendCommand(sensor3 + "+" + command + "\r\n");
      setState(LISTENING);
    }
    
    if ((comandorecebido[i-3] == sensor4) && (comandorecebido[i-2] == 'D') && (comandorecebido[i] == '!')){
      String command = "[VALUE]";
      String soma = "+";
      setState(TRANSMITTING);
      mySDI12.sendCommand(sensor4 + soma + command + "\r\n");
      //mySDI12.sendCommand(sensor4 + "+" + command + "\r\n");
      setState(LISTENING);
    }
    
    if ((comandorecebido[i-3] == sensor5) && (comandorecebido[i-2] == 'D') && (comandorecebido[i] == '!')){
      String command = "[VALUE]";
      String soma = "+";
      setState(TRANSMITTING);
      mySDI12.sendCommand(sensor5 + soma + command + "\r\n");
      //mySDI12.sendCommand(sensor5 + "+" + command + "\r\n");
      setState(LISTENING);
    }
    
    if ((comandorecebido[i-3] == sensor6) && (comandorecebido[i-2] == 'D') && (comandorecebido[i] == '!')){
      String command = "[VALUE]";
      String soma = "+";
      setState(TRANSMITTING);
      mySDI12.sendCommand(sensor6 + soma + command + "\r\n");
      //mySDI12.sendCommand(sensor6 + "+" + command + "\r\n");
      setState(LISTENING);
    }
    
    if ((comandorecebido[i-3] == sensor7) && (comandorecebido[i-2] == 'D') && (comandorecebido[i] == '!')){
      String command = "[VALUE]";
      String soma = "+";
      setState(TRANSMITTING);
      mySDI12.sendCommand(sensor7 + soma + command + "\r\n");
      //mySDI12.sendCommand(sensor7 + "+" + command + "\r\n");
      setState(LISTENING);
    }
    
    if ((comandorecebido[i-3] == sensor8) && (comandorecebido[i-2] == 'D') && (comandorecebido[i] == '!')){
      String command = "[VALUE]";
      String soma = "+";
      setState(TRANSMITTING);
      mySDI12.sendCommand(sensor8 + soma + command + "\r\n");
      //mySDI12.sendCommand(sensor8 + "+" + command + "\r\n");
      setState(LISTENING);
    }
    ///////////////










    ///////////////
    if ((comandorecebido[i-2] == sensor1) && (comandorecebido[i-1] == 'M') && (comandorecebido[i] == '!')){
      String command = "0012";
      setState(TRANSMITTING);
      mySDI12.sendCommand(sensor1 + command + "\r\n");
      digitalWrite(led, LOW);
      setState(LISTENING);
    }
    
    if ((comandorecebido[i-2] == sensor2) && (comandorecebido[i-1] == 'M') && (comandorecebido[i] == '!')){
      String command = "0012";
      setState(TRANSMITTING);
      mySDI12.sendCommand(sensor2 + command + "\r\n");
      setState(LISTENING);
    }
    
    if ((comandorecebido[i-2] == sensor3) && (comandorecebido[i-1] == 'M') && (comandorecebido[i] == '!')){
      String command = "0011";
      setState(TRANSMITTING);
      mySDI12.sendCommand(sensor3 + command + "\r\n");
      setState(LISTENING);
    }
    
    if ((comandorecebido[i-2] == sensor4) && (comandorecebido[i-1] == 'M') && (comandorecebido[i] == '!')){
      String command = "0011";
      setState(TRANSMITTING);
      mySDI12.sendCommand(sensor4 + command + "\r\n");
      setState(LISTENING);
    }
    
    if ((comandorecebido[i-2] == sensor5) && (comandorecebido[i-1] == 'M') && (comandorecebido[i] == '!')){
      String command = "0011";
      setState(TRANSMITTING);
      mySDI12.sendCommand(sensor5 + command + "\r\n");
      setState(LISTENING);
    }
    
    if ((comandorecebido[i-2] == sensor6) && (comandorecebido[i-1] == 'M') && (comandorecebido[i] == '!')){
      String command = "0011";
      setState(TRANSMITTING);
      mySDI12.sendCommand(sensor6 + command + "\r\n");
      setState(LISTENING);
    }
    
    if ((comandorecebido[i-2] == sensor7) && (comandorecebido[i-1] == 'M') && (comandorecebido[i] == '!')){
      String command = "0011";
      setState(TRANSMITTING);
      mySDI12.sendCommand(sensor7 + command + "\r\n");
      setState(LISTENING);
    }
    
    if ((comandorecebido[i-2] == sensor8) && (comandorecebido[i-1] == 'M') && (comandorecebido[i] == '!')){
      String command = "0011";
      setState(TRANSMITTING);
      mySDI12.sendCommand(sensor8 + command + "\r\n");
      setState(LISTENING);
    }
    ///////////////


    ///////////////
    //if ((comandorecebido[i-2] == '?' && (comandorecebido[i-1] == 'I') && (comandorecebido[i] == '!') )){
    if ((comandorecebido[i-1] == '?' && (comandorecebido[i] == '!') )){
      String command = "";
//      command += "a\r\n";
//      command += "b\r\n";
//      command += "c\r\n";
//      command += "d\r\n";
//      command += "e\r\n";
//      command += "f\r\n";
//      command += "g\r\n";
//      command += "h\r\n";
      setState(TRANSMITTING);
      //mySDI12.sendCommand(command + sensor1 + "\r\n" + sensor2 + "\r\n" + sensor3 + "\r\n" + sensor4 + "\r\n" + sensor5 + "\r\n" + sensor6 + "\r\n" + sensor7 + "\r\n" + sensor8 + "\r\n");
      mySDI12.sendCommand(command + "  " + sensor1 + "\t" + sensor2 + "\t" + sensor3 + "\t" + sensor4 + "\t" + sensor5 + "\t" + sensor6 + "\t" + sensor7 + "\t" + sensor8 + "\r\n");
      setState(LISTENING);
    }
    ///////////////








    ///////////////
    if ((comandorecebido[i-3] == sensor1) && (comandorecebido[i-2] == 'A') && (comandorecebido[i] == '!')){
      if(comandorecebido[i-1] == sensor1){
        setState(TRANSMITTING);
        mySDI12.sendCommand("Inseriu o mesmo endereco!\r\n");
        setState(LISTENING);
      }
      else if (comandorecebido[i-1] == sensor2 || comandorecebido[i-1] == sensor3 || comandorecebido[i-1] == sensor4 || comandorecebido[i-1] == sensor5 || comandorecebido[i-1] == sensor6 || comandorecebido[i-1] == sensor7 || comandorecebido[i-1] == sensor8){
        setState(TRANSMITTING);
        mySDI12.sendCommand("Endereco ja utilizado!\r\n");
        setState(LISTENING);
      }
      else{
      sensor1 = comandorecebido[i-1];
      setState(TRANSMITTING);
      String command = (String)comandorecebido[i-1];
      //mySDI12.sendCommand("" + (String)comandorecebido[i-1] + "\r\n");
      mySDI12.sendCommand("" + command + "\r\n");
      setState(LISTENING);
      }
    }
    
    if ((comandorecebido[i-3] == sensor2) && (comandorecebido[i-2] == 'A') && (comandorecebido[i] == '!')){
      if(comandorecebido[i-1] == sensor2){
        setState(TRANSMITTING);
        mySDI12.sendCommand("Inseriu o mesmo endereco!\r\n");
        setState(LISTENING);
      }
      else if (comandorecebido[i-1] == sensor1 || comandorecebido[i-1] == sensor3 || comandorecebido[i-1] == sensor4 || comandorecebido[i-1] == sensor5 || comandorecebido[i-1] == sensor6 || comandorecebido[i-1] == sensor7 || comandorecebido[i-1] == sensor8){
        setState(TRANSMITTING);
        mySDI12.sendCommand("Endereco ja utilizado!\r\n");
        setState(LISTENING);
      }
      else{
      sensor2 = comandorecebido[i-1];
      setState(TRANSMITTING);
      String command = (String)comandorecebido[i-1];
      mySDI12.sendCommand("" + command + "\r\n");
      setState(LISTENING);
      }
    }
    
    if ((comandorecebido[i-3] == sensor3) && (comandorecebido[i-2] == 'A') && (comandorecebido[i] == '!')){
      if(comandorecebido[i-1] == sensor3){
        setState(TRANSMITTING);
        mySDI12.sendCommand("Inseriu o mesmo endereco!\r\n");
        setState(LISTENING);
      }
      else if (comandorecebido[i-1] == sensor1 || comandorecebido[i-1] == sensor2 || comandorecebido[i-1] == sensor4 || comandorecebido[i-1] == sensor5 || comandorecebido[i-1] == sensor6 || comandorecebido[i-1] == sensor7 || comandorecebido[i-1] == sensor8){
        setState(TRANSMITTING);
        mySDI12.sendCommand("Endereco ja utilizado!\r\n");
        setState(LISTENING);
      }
      else{
      sensor3 = comandorecebido[i-1];
      setState(TRANSMITTING);
      String command = (String)comandorecebido[i-1];
      mySDI12.sendCommand("" + command + "\r\n");
      setState(LISTENING);
      }
    }
    
    if ((comandorecebido[i-3] == sensor4) && (comandorecebido[i-2] == 'A') && (comandorecebido[i] == '!')){
      if(comandorecebido[i-1] == sensor4){
        setState(TRANSMITTING);
        mySDI12.sendCommand("Inseriu o mesmo endereco!\r\n");
        setState(LISTENING);
      }
      else if (comandorecebido[i-1] == sensor1 || comandorecebido[i-1] == sensor2 || comandorecebido[i-1] == sensor3 || comandorecebido[i-1] == sensor5 || comandorecebido[i-1] == sensor6 || comandorecebido[i-1] == sensor7 || comandorecebido[i-1] == sensor8){
        setState(TRANSMITTING);
        mySDI12.sendCommand("Endereco ja utilizado!\r\n");
        setState(LISTENING);
      }
      else{
      sensor4 = comandorecebido[i-1];
      setState(TRANSMITTING);
      String command = (String)comandorecebido[i-1];
      mySDI12.sendCommand("" + command + "\r\n");
      setState(LISTENING);
      }
    }
    
    if ((comandorecebido[i-3] == sensor5) && (comandorecebido[i-2] == 'A') && (comandorecebido[i] == '!')){
      if(comandorecebido[i-1] == sensor5){
        setState(TRANSMITTING);
        mySDI12.sendCommand("Inseriu o mesmo endereco!\r\n");
        setState(LISTENING);
      }
      else if (comandorecebido[i-1] == sensor1 || comandorecebido[i-1] == sensor2 || comandorecebido[i-1] == sensor3 || comandorecebido[i-1] == sensor4 || comandorecebido[i-1] == sensor6 || comandorecebido[i-1] == sensor7 || comandorecebido[i-1] == sensor8){
        setState(TRANSMITTING);
        mySDI12.sendCommand("Endereco ja utilizado!\r\n");
        setState(LISTENING);
      }
      else{
      sensor5 = comandorecebido[i-1];
      setState(TRANSMITTING);
      String command = (String)comandorecebido[i-1];
      mySDI12.sendCommand("" + command + "\r\n");
      setState(LISTENING);
      }
    }
    
    if ((comandorecebido[i-3] == sensor6) && (comandorecebido[i-2] == 'A') && (comandorecebido[i] == '!')){
      if(comandorecebido[i-1] == sensor6){
        setState(TRANSMITTING);
        mySDI12.sendCommand("Inseriu o mesmo endereco!\r\n");
        setState(LISTENING);
      }
      else if (comandorecebido[i-1] == sensor1 || comandorecebido[i-1] == sensor2 || comandorecebido[i-1] == sensor3 || comandorecebido[i-1] == sensor4 || comandorecebido[i-1] == sensor5 || comandorecebido[i-1] == sensor7 || comandorecebido[i-1] == sensor8){
        setState(TRANSMITTING);
        mySDI12.sendCommand("Endereco ja utilizado!\r\n");
        setState(LISTENING);
      }
      else{
      sensor6 = comandorecebido[i-1];
      setState(TRANSMITTING);
      String command = (String)comandorecebido[i-1];
      mySDI12.sendCommand("" + command + "\r\n");
      setState(LISTENING);
      }
    }
    
    if ((comandorecebido[i-3] == sensor7) && (comandorecebido[i-2] == 'A') && (comandorecebido[i] == '!')){
      if(comandorecebido[i-1] == sensor7){
        setState(TRANSMITTING);
        mySDI12.sendCommand("Inseriu o mesmo endereco!\r\n");
        setState(LISTENING);
      }
      else if (comandorecebido[i-1] == sensor1 || comandorecebido[i-1] == sensor2 || comandorecebido[i-1] == sensor3 || comandorecebido[i-1] == sensor4 || comandorecebido[i-1] == sensor5 || comandorecebido[i-1] == sensor6 || comandorecebido[i-1] == sensor8){
        setState(TRANSMITTING);
        mySDI12.sendCommand("Endereco ja utilizado!\r\n");
        setState(LISTENING);
      }
      else{
      sensor7 = comandorecebido[i-1];
      setState(TRANSMITTING);
      String command = (String)comandorecebido[i-1];
      mySDI12.sendCommand("" + command + "\r\n");
      setState(LISTENING);
      }
    }
    
    if ((comandorecebido[i-3] == sensor8) && (comandorecebido[i-2] == 'A') && (comandorecebido[i] == '!')){
      if(comandorecebido[i-1] == sensor8){
        setState(TRANSMITTING);
        mySDI12.sendCommand("Inseriu o mesmo endereco!\r\n");
        setState(LISTENING);
      }
      else if (comandorecebido[i-1] == sensor1 || comandorecebido[i-1] == sensor2 || comandorecebido[i-1] == sensor3 || comandorecebido[i-1] == sensor4 || comandorecebido[i-1] == sensor5 || comandorecebido[i-1] == sensor6 || comandorecebido[i-1] == sensor7){
        setState(TRANSMITTING);
        mySDI12.sendCommand("Endereco ja utilizado!\r\n");
        setState(LISTENING);
      }
      else{
      sensor8 = comandorecebido[i-1];
      setState(TRANSMITTING);
      String command = (String)comandorecebido[i-1];
      mySDI12.sendCommand("" + command + "\r\n");
      setState(LISTENING);
      }
    }
    
    
//    if ((comandorecebido[i-3] != sensor1) && (comandorecebido[i-3] != sensor2) && (comandorecebido[i-3] != sensor3) && (comandorecebido[i-3] != sensor4) && (comandorecebido[i-3] != sensor5) && (comandorecebido[i-3] != sensor6) && (comandorecebido[i-3] != sensor7) && (comandorecebido[i-3] != sensor8) && (comandorecebido[i-2] == 'A') && (comandorecebido[i] == '!')){
//      setState(TRANSMITTING);
//      //String command = "";
//      mySDI12.sendCommand("Sensor " + (String)comandorecebido[i-3] + " nao conectado\r\n");
//      setState(LISTENING);
//    }
    ///////////////









//    if (comandorecebido[i-1] == 'a' && (comandorecebido[i] == 'M')){
//
//      // Serial.println("pedido de MEDIÇAO");
//
//      //   if (mySDI12.read() == 'I')
//      ////////////////////////////  Serial.write("Pedido de Informação\n");
//
//      int z = 25497;
//      int j; 
//      String command = "";
//      String command1 = "";
//      //command += "a"; 
//      command1 += (String) z;
//      command += "*!";
//      for(j = 0; j < 1; j++){
//        setState(TRANSMITTING);
//        mySDI12.sendCommand1(command1);
//        ///////////////////    Serial.print(command1);
//        mySDI12.sendCommand1(command);
//        /////////////////////    Serial.print(command);
//        //delay(30) 
//      }
//      //   delay(20.5);
//    }












    i++;
    if (comandorecebido[i-1] == '!'){
      comandorecebido = "";	
      i=0;
    }


  }






}
//}

