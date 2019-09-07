#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>
#include <Console.h>
#include <FileIO.h>
#include <HttpClient.h>
#include <Mailbox.h>
#include <Process.h>
#include <SPI.h>

#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#define RxPin 11 //Pin to read data 
#define TxPin 12 //Pin to write data 


SoftwareSerial rfid (RxPin,TxPin); // RX and TX
LiquidCrystal lcd (5,6,7,8,9,10); 


YunClient client;


IPAddress server(192,168,1,12);

String msg="";
String parametri ="";

void setup()
{
  Bridge.begin();
  
  rfid.begin(9600);    // start serial to RFID reader
  
  Serial.begin(115200);
 
 pinMode(4,OUTPUT);
 pinMode(3,OUTPUT); 
 pinMode(2,OUTPUT);

  

    Serial.println("swipe u card");
    lcd.begin(16 , 2);
    lcd.print("swipe u card");
  
  
 
}

 char c;
void loop(){
  
  if(rfid.available()){
  while(rfid.available()>0)
  {
      
      c= rfid.read();
      
      msg += c;
  }
 
  if (msg.length() > 10) {
      msg = msg.substring(3,11);
      }
      Serial.println(msg);
      lcd.clear();
      lcd.print(msg);
      digitalWrite(2, HIGH);
      buzz(4, 5000, 500);
      delay(3000);
      digitalWrite(2, LOW);
 
      
parametri="RFID_Tag="+String(msg);   

if(client.connect(server, 80)){
    Serial.println("Connected to the server."); 
    
         
    client.println("POST /ard/index.php HTTP/1.1");
    client.print("Content-length:");
    client.println(parametri.length());
    Serial.println(parametri.length());
    Serial.println(parametri);
    client.println("Connection: Close");
    client.println("Host:192.168.1.12");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println();
    client.println(parametri);     //Set Remote temperture to ___
    //client.print(temp);
    //client.println("}");

  digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW

Serial.println("disconnecting.");
    client.stop();
    lcd.clear();
    lcd.print("Saved ! ");
       
}else
    {digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)
     delay(1000);              // wait for a second
     digitalWrite(3, LOW);    // turn the LED off by making the voltage LOW

     Serial.println("Could not connect to the server.");        
     lcd.clear();
     lcd.print("error!again plz.");
    }
  

}
delay(3000);
parametri = "";
msg = "";
lcd.clear();
lcd.print("swipe u card");   
}







void buzz(int targetPin, long frequency, long length) {
  long delayValue = 1000000/frequency/2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length/ 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to 
  //// get the total number of cycles to produce
 for (long i=0; i < numCycles; i++){ // for the calculated length of time...
    digitalWrite(targetPin,HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin,LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait againf or the calculated delay value
  }
}

