float belichtung_L=1;
void Belichtung_L()
{
  String f = String(belichtung_L);
    display.clear();
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 0, "1:Belichtung");
    display.drawString(0, 28, f+"sec");
    display.display();
       if(Taster()==2)
      {
        belichtung_L+=1.0;
        delay(100);
      }
      if(Taster()==3)
      {
        belichtung_L-=1.0;
        if(belichtung_L==0)belichtung_L=1;
        delay(100);
      }
}
void Start_L()
{
  //String f = String(int_cunt);
  display.clear();
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 0, "1:Start ");
  display.drawXbm(48, 31, Start_width, Start_height, Start);
  display.display();
  if(Taster()==2)
    { 
      Timer_=0;
      digitalWrite(AUSLOSER, HIGH); 
      while(1)
      {        
          if((Timer_>=belichtung_L))
          {
            digitalWrite(AUSLOSER, LOW);
            break;
          }
          if(Taster()==3)break;
          String f = String(Timer_);
          String f1 = String(belichtung_L);
          display.clear();
          display.setFont(ArialMT_Plain_24);
          display.drawString(5, 0, ">>Work<<");
          display.setFont(ArialMT_Plain_16);
          display.drawString(0, 28, f1+"sec ");
          display.drawString(0, 45, f+"sec ");
          display.display();
      }
       
   }
}


int Langzeitbelichtung_app()
{
  int cunt_2=0;
  display.clear();
  display.setFont(ArialMT_Plain_24);
  display.drawString(5, 20, "Langzeitbelichtung");
  display.display();
  
  if(Taster() == 2)
  {
    while(Taster() == 2);
    while(1)
    {
      while(Taster() == 1)
          { 
            cunt_2++;
            if(cunt_2==3)cunt_2=0;
            delay(300);
          }
          
          switch(cunt_2)
            {
              case 0: Belichtung_L(); break;
              case 1: Start_L(); break;
              case 2: display.clear();
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
