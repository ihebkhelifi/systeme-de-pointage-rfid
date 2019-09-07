#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#define RxPin 11 //Pin to read data 
#define TxPin 12 //Pin to write data 

SoftwareSerial rfid (RxPin,TxPin); // RX and TX
LiquidCrystal lcd (5,6,7,8,9,10); 

String msg="";
int i=0; 

void setup()
{
  rfid.begin(9600);    // start serial to RFID reader
  Serial.begin(9600);
  while (!Serial) ;
  Serial.println("swipe u card");
  lcd.begin(16 , 2);
  lcd.print("swipe u card");

}
 char c;
void loop()
{
  while(rfid.available()>0)
  {
      c= rfid.read();
      
      msg += c;
  }
 
  if (msg.length() > 10) {
      msg = msg.substring(3,11);
      Serial.println(msg);
      lcd.clear();
      lcd.print(msg);
      delay(4000);
  }


delay(1000);
msg = "";
lcd.clear();
lcd.print("swipe u card");   
}

