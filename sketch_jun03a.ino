#include <NewPing.h>
#include <stdio.h>
#include <stdlib.h>


const int button = 8;            // GPIO 8 for the button
const int led =7;                // GPIO 7 for the LED
int ledflag=0;                   // LED status flag
int flag=0;
int flag2 =1;
int distance=0;
int timer = 3000;
int timecounter = 0;
int flag3=0;
int flag4 =0;

NewPing sonar(10,11,20);

void setup()
{    
  Serial.begin(9600);
  delay(50);   
  pinMode(button,INPUT);         // define button as an input 
  pinMode(led,OUTPUT);           // define LED as an output
  digitalWrite(led,LOW);     
}

void loop()
{ 
   if(sonar.ping_cm() > 0 && sonar.ping_cm() < 11){
    if(flag2==0){
      flag2=1;
      timer = millis();
    }
    if(millis()-timer > 3000){
      timer = millis();
      flag=0; 
      ledflag=0;                  
      digitalWrite(led,LOW);           
    }
   }
   else{
    flag2=0;
   }
   Serial.print(flag);
   Serial.print("distance is:");
   Serial.println(sonar.ping_cm());
   delay(800);
   if (digitalRead(button)==HIGH){
      flag =1;
    }
   if (flag==1){
       if(sonar.ping_cm()>=15)
          {              
             ledflag=1;                  // make status flag HIGH
             digitalWrite(led,HIGH);     // and turn on the LED
         }                                    
         delay(1000); 
           
   }
   if(ledflag == 1){
    if(flag3 == 0){
      timecounter = millis();
      flag3=1;
    }
    else if((millis() - timecounter >10000)||(millis() - timecounter >7000 && sonar.ping_cm()==0)){
      ledflag=0;
      digitalWrite(led,LOW);
      flag3=0;
      flag=0;
    }
    
   }
   
}
