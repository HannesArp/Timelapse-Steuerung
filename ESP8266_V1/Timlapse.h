

int Taster()
{ 
  int d = 0;
  while (Serial.available()) 
  {
    d = Serial.read();
    if(d==52)
    {
      return d-48;
    }
  }
  if(digitalRead(Taster1)==0)
  {
      return 1;  
  }
  if(digitalRead(Taster2)==0)
  {
      return 2;  
  }
  if(digitalRead(Taster3)==0)
  {
      return 3;  
  }
  if(digitalRead(Taster4)==0)
  {
      return 4;  
  }
  
  return 0;  
  
}


int menuCunter=0;
int menuCunter2=0;
int programmCunt =0;
void Intervall_prg()
{
    String f = String(Intervall);
    float h=Intervall;
    h=(h*(anzahl)/60);
    String f1 = String( h);
    display.clear();
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 0, "1:Intervall ");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 25, f+"sec");
    display.drawString(0, 42,"Dauer:"+f1+"min");
    display.display();
       if(Taster()==2)
      {
        Intervall+=1;
        belichtung=Intervall;
        belichtung=belichtung/2;
        if(Intervall>=101)Intervall=0;
        delay(100);
      }
      if(Taster()==3)
      {
        Intervall-=1;
        belichtung=Intervall;
        belichtung=belichtung/2;
        if(Intervall<=-1)Intervall=100;
        delay(100);
      }
}

void Anzhl_prg()
{
    String f = String(anzahl);
    float h=Intervall;
    h=(h*(anzahl)/60);
    String f1 = String( h);
    display.clear();
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 0, "2:Anzahl Int");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 25, f);
    display.drawString(0, 42,"Dauer:"+f1+"min");
    display.display();
       if(Taster()==2)
      {
        anzahl+=1;
        delay(100);
      }
      if(Taster()==3)
      {
        anzahl-=1;
        if(anzahl==0)anzahl=1;
        delay(100);
      }
}
void Installieren()
{ 
  
  display.clear();
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 0, "3:Ini");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 25, "Alles Achsen");
  display.display();
  if(Taster()==2)
    {
      if(anzahl<100)
      {
      mySerial.print("A00");
      mySerial.print(anzahl);
      mySerial.print(';');
      }
      
      if((anzahl>=100)&&(anzahl<1000))
      {
      mySerial.print("A0");
      mySerial.print(anzahl);
      mySerial.print(';');
      }
      if((anzahl>=1000))
      {
      mySerial.print("A");
      mySerial.print(anzahl);
      mySerial.print(';');
      }
      while(Taster()==2);
      delay(500);
      mySerial.print("INI;");
    
   }
} 
void Belichtung()
{
  String f = String(belichtung);
    display.clear();
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 0, "4:Belichtung");
    display.drawString(0, 28, f+"sec");
    display.display();
       if(Taster()==2)
      {
        belichtung+=0.1;
        delay(100);
      }
      if(Taster()==3)
      {
        belichtung-=0.1;
        if(belichtung==0)belichtung=1;
        delay(100);
      }
}

#define Start_width 32
#define Start_height 32
const uint8_t Start[] PROGMEM = {
  0x00, 0xC0, 0x07, 0x00, 0x00, 0xFC, 0x3F, 0x00, 0x00, 0xFF, 0xFF, 0x00, 
  0x80, 0xFF, 0xFF, 0x03, 0xE0, 0xFF, 0xFF, 0x07, 0xF0, 0xFF, 0xFF, 0x0F, 
  0xF0, 0xFF, 0xFF, 0x1F, 0xF8, 0xFF, 0xFF, 0x1F, 0xFC, 0xFF, 0xFF, 0x3F, 
  0xFC, 0xFF, 0xFF, 0x7F, 0xFE, 0xCF, 0xFF, 0x7F, 0xFE, 0x8F, 0xFF, 0x7F, 
  0xFE, 0x0F, 0xFE, 0xFF, 0xFE, 0x0F, 0xF8, 0xFF, 0xFF, 0x0F, 0xE0, 0xFF, 
  0xFF, 0x0F, 0xC0, 0xFF, 0xFF, 0x0F, 0x80, 0xFF, 0xFF, 0x0F, 0xE0, 0xFF, 
  0xFF, 0x0F, 0xF0, 0xFF, 0xFE, 0x0F, 0xFC, 0xFF, 0xFE, 0x0F, 0xFF, 0x7F, 
  0xFE, 0x8F, 0xFF, 0x7F, 0xFC, 0xEF, 0xFF, 0x7F, 0xFC, 0xFF, 0xFF, 0x3F, 
  0xF8, 0xFF, 0xFF, 0x3F, 0xF8, 0xFF, 0xFF, 0x1F, 0xF0, 0xFF, 0xFF, 0x0F, 
  0xE0, 0xFF, 0xFF, 0x07, 0xC0, 0xFF, 0xFF, 0x03, 0x00, 0xFF, 0xFF, 0x01, 
  0x00, 0xFE, 0x7F, 0x00, 0x00, 0xF0, 0x0F, 0x00, 
};
void Start_()
{
  //String f = String(int_cunt);
  display.clear();
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 0, "5:Start ");
  display.drawXbm(48, 31, Start_width, Start_height, Start);
  //display.drawString(0, 28, f);
  display.display();
  int en=1;
  int cunter=1;
  if(Taster()==2)
    { 
      Timer_=0;
      digitalWrite(AUSLOSER, HIGH); 
      while(1)
      {        
          if((Timer_>=belichtung)&& (en==1))
          {
            digitalWrite(AUSLOSER, LOW);
            mySerial.print("ST;");
            en=0;
          }
          if(Timer_>=Intervall)
          {
            digitalWrite(AUSLOSER, HIGH); 
            Timer_=0;
            en=1;
            cunter++;
          }
          if(cunter>=anzahl)break;
          if(Taster()==3)break;
          String f = String(Timer_);
          String f1 = String(cunter);
          String f2 = String(anzahl);
          float h=Intervall;
           h=(h*(anzahl-cunter)/60);
          String f3 = String(h);
          display.clear();
          display.setFont(ArialMT_Plain_24);
          display.drawString(5, 0, ">>Work<<");
          display.setFont(ArialMT_Plain_16);
          display.drawString(0, 28, f+"sec "+f3+"min");
          display.drawString(0, 45, f1+" von "+f2);
          display.display();
      }
       
   }
}

int Timlapse_app()
{
  display.clear();
  display.setFont(ArialMT_Plain_24);
  display.drawString(5, 20, "Timelapse");
  display.display();
  int cunt=0;
  if(Taster() == 2)
  {
    while(Taster() == 2);
    while(1)
    {
      while(Taster() == 1)
          { 
            cunt++;
            if(cunt==6)cunt=0;
            delay(300);
          }
          
          switch(cunt)
            {
              case 0: Intervall_prg();break;
              case 1: Anzhl_prg(); break;
              case 2: Installieren(); break;
              case 3: Belichtung(); break;
              case 4: Start_(); break;
              case 5: display.clear();
                      display.setFont(ArialMT_Plain_24);
                      display.drawString(5, 20, "Zuruck");
                      display.display();
                       if(Taster()==3)
                          {
                            return 0;
                          }
                           break;
              default: break;
            }
    }
  }
}
