// include the library code:
#include <LiquidCrystal.h>
#include<EEPROM.h>
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 4, en = 3, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


int start = 10;
//int set =  9;
int relay = 2;
#define pot A5

//int set_flag;
int run_flag;
//int eeprom_value;

//int remaining;
int minutes;

int oldValue;
int newValue;
boolean StartbuttonWasLow = false;         // variable flag for when the pushbutton goes low
//boolean SetbuttonWasLow = false;         // variable flag for when the pushbutton goes low


void setup() {

//set_flag = 1;
run_flag = 1;

  pinMode(start,INPUT);
//  pinMode(set,INPUT);
  pinMode(relay,OUTPUT);
  pinMode(pot,INPUT);
  
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0,0);
  lcd.print("KTS and Printlay");
  lcd.setCursor(0,1);
  lcd.print("Timing Ctrl _/_");
  delay(1000);
  lcd.clear();
  Serial.print("Hello");
  oldValue = 0;
}

void loop() {
    digitalWrite(relay,LOW);
    Serial.print("old Vaue : ");
    Serial.print(oldValue);
    Serial.print(minutes);
    int value = analogRead(pot);
    int minutes = map(value,1,1023,1,50);
    newValue = minutes;
    Serial.print("new Vaue : ");
    Serial.println(newValue);
    if(newValue != oldValue){
    lcd.setCursor(11,0);
    lcd.print("   ");
    Serial.print("Changed state");
    lcd.setCursor(0,0);
    lcd.print("Run Min : ");
    lcd.setCursor(10,0);
    lcd.print(minutes);
    Serial.println(minutes);
    delay(50);    

    oldValue = minutes;
    }
    
    
    
    if(digitalRead(start) == LOW){
    StartbuttonWasLow = true;
    }
    
      if (digitalRead(start) == HIGH && StartbuttonWasLow)  {
      StartbuttonWasLow = false;
      run(minutes);
    }
  
    
}
  
  int run(int timer){
     for(int i= 0;i<=timer;i++){
      Serial.print("Minutes");
      Serial.println(timer);
      digitalWrite(relay,HIGH);
      lcd.setCursor(0,0);
      lcd.print("Run Min : ");
      lcd.setCursor(10,0);  
      lcd.print(timer);
      lcd.setCursor(0,1);      
      lcd.print("Rem Min : ");
      lcd.setCursor(10,1);
      lcd.print(timer - i);     
      delay(60000);

//      delay(1000);
      lcd.setCursor(11,1);
      lcd.print(" ");
      lcd.setCursor(12,1);
      lcd.print(" ");
    }
    
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Job_Finished");
    digitalWrite(relay,LOW);
    delay(100);
    exit;
    }
