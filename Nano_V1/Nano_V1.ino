/*
  ##############Anleitung##############
  Step1: Auswehlen des Richigen Boards: Unter dem menüpunkt   "Werkzeuge->Boards" Das "Arduino Nano" auswehlen.
  Step2: Board mit dem PC verbinden.
  Step3: Den Richtigen Port Auswehlen : Unter dem menüpunkt   "Werkzeuge->Port" den COM Port auswhelen. Info der COM1 ist meistens der Hardware Port dieser wird nicht benötigt.
  Step4: Software Hochladen           : Unter dem menüpunkt   "Sketch->Hochladen" Hochladen betätigen.
  Step5: Fertig!!!!!!!!!!!
  Info: Um die Geschwindichkeit des Motors zu verändern muss die Variable delay_speed(Gekenzeichniet mit //#) verändert werden. Umso höher die zahl umso Langsamer der Motor.
  Indo: Die Motorgeschwindichkeit kann auch über die digitalWrite(MS1, LOW), digitalWrite(MS2, LOW), digitalWrite(MS3, LOW) (Gekenzeichniet mit //$)verändern werden. Sind alles auf LOW ist der Motor Schnell, sind alles auf HIGH ist der Motor Langsam.  
  #####################################
*/

/*
  ##############Befehlssatz##############
  INI;    Initialisieren
  A9999;  Anzahl Intervall
  ST;     Step
  M0;     Move Rechts
  M1;     Move Links
  #####################################
*/

#include <EEPROM.h>

/////////_______LED_______
#define LED_ 13

/////////_______TASTER_______

#define T1 8
#define T2 9
#define T3 10

/////////_______StepMotor_______
#define DIR 7
#define STEP 6
#define MS1 3
#define MS2 4
#define MS3 5
#define ENABLE 2
int delay_speed = 1; //#

void setup() {
  /////////Step Motor Treiber-------
  pinMode(DIR, OUTPUT);
  pinMode(STEP, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  digitalWrite(ENABLE, LOW);
  digitalWrite(MS1, LOW); //$
  digitalWrite(MS2, LOW); //$
  digitalWrite(MS3, LOW); //$
  digitalWrite(DIR, LOW);
  /////////LED-----
  pinMode(LED_, OUTPUT);
  /////////Step Motor Treiber-------
  pinMode(T1, INPUT);
  pinMode(T2, INPUT);
  pinMode(T3, INPUT);
  Serial.begin(9600);

  digitalWrite(LED_, HIGH);
  delay(500);
  digitalWrite(LED_, LOW);
  delay(500);

}

int cunter = 0;
char message[10] = "";
char arry[10] = "";
int x = 0;
int Intervall = 0;
int Anzahl_Intervall = 0;
int Move = 0;
unsigned long stepps = 0;
int richtung = 0;
int richtung_int = 0;
void mesage();
void mass_cliar()
{
  for (x = 0; x <= 11; x++)
  {
    message[x] == 0;
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  mesage();
  while (digitalRead(T3) == 1)
  {
    while (digitalRead(T2) == 1)
    {
      stepps++;
      richtung = 0;
      richtung_int = 1;
      digitalWrite(ENABLE, LOW);
      digitalWrite(DIR, richtung);
      digitalWrite(STEP, LOW);
      delay(delay_speed);
      digitalWrite(STEP, HIGH);
      delay(delay_speed);
    }
    while (digitalRead(T1) == 1)
    {
      stepps++;
      richtung = 1;
      richtung_int = 0;
      digitalWrite(ENABLE, LOW);
      digitalWrite(DIR, richtung);
      digitalWrite(STEP, LOW);
      delay(delay_speed);
      digitalWrite(STEP, HIGH);
      delay(delay_speed);
    }
  }

  while (digitalRead(T2) == 1)
  {
    stepps = 0;
    richtung = 0;
    richtung_int = 1;
    digitalWrite(ENABLE, LOW);
    digitalWrite(DIR, richtung);
    digitalWrite(STEP, LOW);
    delay(delay_speed);
    digitalWrite(STEP, HIGH);
    delay(delay_speed);
  }

  while (digitalRead(T1) == 1)
  {
    stepps = 0;
    richtung = 1;
    richtung_int = 0;
    digitalWrite(ENABLE, LOW);
    digitalWrite(DIR, richtung);
    digitalWrite(STEP, LOW);
    delay(delay_speed);
    digitalWrite(STEP, HIGH);
    delay(delay_speed);
  }

}



void mesage()
{
  cunter = 0;
  if (Serial.available() > 0)
  {
    message[cunter] = Serial.read();
    cunter++;
    int err = 0;
    while (message[cunter - 1] != ';')
    {
      if (Serial.available() > 0)
      {
        message[cunter] = Serial.read();
        cunter++;
        err = 0;
      }
      err++;
      if (err == 1000)
      {
        //Serial.println("ERROR");
        break;
      }
    }
  }

  //////////////////////////<initialisieren>INI;////////////////////////////////////
  if ((message[0] == 'I') && (message[1] == 'N') && (message[2] == 'I'))
  {
    if (Anzahl_Intervall != 0)
    {
      for (int x = 0; x <= stepps; x++)
      {
        digitalWrite(ENABLE, LOW);
        digitalWrite(DIR, richtung_int);
        digitalWrite(STEP, LOW);
        delay(delay_speed);
        digitalWrite(STEP, HIGH);
        delay(delay_speed);
      }
      digitalWrite(LED_, HIGH);
    }
    message[0] = 0;
  }

  //////////////////////////<Anzahl Intervall>A9999;////////////////////////////////////
  if ((message[0] == 'A') && (message[1] != 0) && (message[2] != 0) && (message[3] != 0) && (message[4] != 0))
  {
    arry[0] = message[2];
    arry[1] = message[3];
    arry[2] = message[4];
    arry[3] = message[5];
    Anzahl_Intervall = atoi(arry);
    message[0] = 0;
    cunter = 0;
  }

  //////////////////////////<Stepp>ST;////////////////////////////////////
  if ((message[0] == 'S') && (message[1] == 'T'))
  {
    if (Anzahl_Intervall != 0)
    {
      for (int x = 0; x <= (stepps / Anzahl_Intervall); x++)
      {
        digitalWrite(ENABLE, LOW);
        digitalWrite(DIR, richtung);
        digitalWrite(STEP, LOW);
        delay(delay_speed);
        digitalWrite(STEP, HIGH);
        delay(delay_speed);
      }
    }
    message[0] = 0;
  }

  //////////////////////////<Move M1;>M1;////////////////////////////////////
  if ((message[0] == 'M') && (message[1] == '1'))
  {
    Move = 1;
    message[0] = 0;
    message[1] = 0;
    cunter = 0;
    //Serial.println("M1");
  }

  //////////////////////////<Move M0;>M0;////////////////////////////////////
  if ((message[0] == 'M') && (message[1] == '0'))
  {
    Move = 0;
    message[0] = 0;
    message[1] = 0;
    cunter = 0;
    //Serial.println("M0");
  }

  //////////////////////////<Speed;>MA8;////////////////////////////////////
  if ((message[0] == 'M') && (message[1] == 'C'))
  {
    arry[0] = message[2];
    delay_speed = atoi(arry);
    message[0] = 0;
    message[1] = 0;
    message[2] = 0;
    cunter = 0;
  }


  if (cunter == 7) cunter = 0;
}
