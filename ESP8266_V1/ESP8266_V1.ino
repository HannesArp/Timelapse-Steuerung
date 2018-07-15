/*
##############Anleitung##############
Step1: Einbinden der ESP Boards     : Unter dem menüpunkt   "Datei->Voreinstellungen->Zusätzlichen Boardverwalter-URLs:" Diesen Link einfügen: http://arduino.esp8266.com/stable/package_esp8266com_index.json
Step2: Auswehlen des Richigen Boards: Unter dem menüpunkt   "Werkzeuge->Boards" Das "WeMos D1 R2 & mini" auswehlen.
Step3: Board Mit dem PC verbinden.
Step4: Den Richtigen Port Auswehlen : Unter dem menüpunkt   "Werkzeuge->Port" den COM Port auswhelen. Info Der COM1 ist meistens der Hardware Port dieser wird nicht benötigt.
Step5: Software Hochladen           : Unter dem menüpunkt   "Sketch->Hochladen" betätigen.
Step6: Fertig!!!!!!!!!!!
#####################################
*/


#include <EEPROM.h>

/////Display\\\\\

#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
SSD1306  display(0x3c,D1, D2);

/////Taster\\\\\

#define  Taster1 D3
#define  Taster2 D6
#define  Taster3 D7
#define  Taster4 D5


/////Variablen\\\\\

int Intervall=1;
int anzahl=400;
float Timer_=0;
float belichtung=0.5;


#define AUSLOSER    D8

#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, D4); // RX, TX
void timer0_ISR (void) { 


    Timer_ +=0.01;    
    timer0_write(ESP.getCycleCount() + 800000L); // 80MHz == 1sec 
 
}



/////include\\\\\

#include "Image.h"
#include "Timlapse.h"

void setup() {

  /////EEPROM
  EEPROM.begin(2);
  
  /////Serial
  Serial.begin(9600);
  mySerial.begin(9600);

  ////STEPP MOTOR

  
  pinMode(AUSLOSER, OUTPUT);
  digitalWrite(AUSLOSER, LOW);
  
  
  /////Taster
  pinMode(Taster1, INPUT_PULLUP);
  pinMode(Taster2, INPUT_PULLUP);
  pinMode(Taster3, INPUT_PULLUP);
  pinMode(Taster4, INPUT_PULLUP);
  
  /////Display
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  
  display.clear();  
  display.drawXbm(0, 0, Logo_width, Logo_height, Logo);
  display.display();
  
  delay(1000);
  Serial.begin(9600); 
      noInterrupts(); 
      timer0_isr_init(); 
      timer0_attachInterrupt(timer0_ISR); 
      timer0_write(ESP.getCycleCount() + 800000L);// 80000000L); // 80MHz == 1sec 
      interrupts();
      Timer_=0;
  
  
}

 int cunt_1=0;
void loop() {
      
      while(Taster() == 1)
      { 
        cunt_1++;
        if(cunt_1==2)cunt_1=0;
        delay(300);
      }
      
      switch(cunt_1)
        {
          case 0: Timlapse_app();break;
          case 1: Langzeitbelichtung_app(); break;
          default: break;
        }
        
  
}

