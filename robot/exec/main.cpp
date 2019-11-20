
#include "mouvement.h"
#include "Son.h"

#define capteur1 PINA & 0x11
#define capteur2 PINA & 0x12
#define capteur3 PINA & 0x14
#define capteur4 PINA & 0x18
#define capteur5 PINA & 0x30


bool lireCapteur1(void)
{
    if((!capteur3 || capteur1 || !capteur2 || !capteur4 || !capteur5 ))
        {
            _delay_ms(1);
            if((!capteur3 || capteur1 || !capteur2 || !capteur4 || !capteur5 )){return true;}
            return false;
        }
        return false;
}
bool lireCapteur2(void)
{
    if((!capteur3 || !capteur1 || capteur2 || !capteur4 || !capteur5 ))
        {
            _delay_ms(1);
            if((!capteur3 || !capteur1 || capteur2 || !capteur4 || !capteur5 )){return true;}
            return false;
        }
        return false;
}
bool lireCapteur3(void)
{
    if((capteur3 || !capteur1 || !capteur2 || !capteur4 || !capteur5 ))
        {
            _delay_ms(1);
            if((capteur3 || !capteur1 || !capteur2 || !capteur4 || !capteur5 )){return true;}
            return false;
        }
        return false;
}
bool lireCapteur4(void)
{
    if((!capteur3 || !capteur1 || !capteur2 || capteur4 || !capteur5 ))
        {
            _delay_ms(1);
            if((!capteur3 || !capteur1 || !capteur2 || capteur4 || !capteur5 )){return true;}
            return false;
        }
        return false;
}
bool lireCapteur5(void)
{
    if((!capteur3 || !capteur1 || !capteur2 || !capteur4 || capteur5 ))
        {
            _delay_ms(1);
            if((!capteur3 || !capteur1 || !capteur2 || !capteur4 || capteur5 )){
                return true;}
            return false;
        }
        return false;
}
bool lireCapteurs(void)
{
    if((capteur1 || capteur2 || capteur3 || capteur4 || capteur5))
    {
        _delay_ms(10);
        if ((capteur1 || capteur2 || capteur3 || capteur4 || capteur5))
        {
            return true;
        }
        return false;
    }
    return false;
}
bool AucunCapteurs(void)
{

    if((capteur1 && capteur2 && capteur3 && capteur4 && capteur5))
    {
        _delay_ms(1);
        if ((capteur1 && capteur2 && capteur3 && capteur4 && capteur5))
        {
            return true;
        }
        return false;
    }
    return false;

}
bool CapteursGauche(void)
{
    if((capteur3 || capteur1 || capteur2 || !capteur4 || !capteur5 ))
    {
            _delay_ms(1);
            if((capteur3 || capteur1 || capteur2 || !capteur4 || !capteur5 ))
            {
                return true;
            }
        return false;
    }
    return false;
}
bool CapteursDroite(void)
{
    if((capteur3 || !capteur1 || !capteur2 || capteur4 || capteur5 ))
        {
            _delay_ms(1);
            if((capteur3 || !capteur1 || !capteur2 || capteur4 || capteur5 )){
                return true;
            }
            return false;
        }
        return false;
}

void suivreLigne()
{
     DDRA = 0x00;
    DDRB =0xff;
    //Son son;

    initialisationMouvement();
    for(;;)
    {
     while(lireCapteurs())
     {
         if ((lireCapteur1()&&lireCapteur2() )|| lireCapteur1())
         {
             while(lireCapteur1()){tournerGauche();}
             arretMouvement();
             //son.operationFaite();

         }
         if (lireCapteur2())
         {
            while(lireCapteur2()){tournerUnPeuGauche();}
             arretMouvement();
             //son.operationFaite();
         }
         if (lireCapteur3())
         {
             while(lireCapteur3()){avancerVitesseConst(0.4);}
              arretMouvement();
              //son.operationFaite();
         }
         if (lireCapteur4())
         {
             while(lireCapteur4()){tournerUnPeuDroite();}
              arretMouvement();
             //son.operationFaite();
         }
         if (lireCapteur5())
         {
             while(lireCapteur5()){tournerDroite();}
              arretMouvement();
              //son.operationFaite();
         }
         if(CapteursGauche())
         {
             while(!lireCapteur5()){
                    //son.operationFaite();
                    tournerGauche90();
                    //son.operationFaite();

                }

        }
        if(CapteursDroite())
        {
                while(!lireCapteur1()){avancerVitesseConst(0.5);}
        }
        
        }
    }
}
void suivreCouloir(bool running)
{
    DDRA = 0x00;
    DDRB =0xff;
    Son son;

    initialisationMouvement();
 for(;;)
 {
      if ((lireCapteur1() && lireCapteur2()) || lireCapteur1())
      {
          while((lireCapteur1() && lireCapteur2()) || lireCapteur1())
          {
              tournerDroite();
          }
      }
      else if(lireCapteur2())
      {
          while(lireCapteur2())
          {
              tournerUnPeuDroite();
          }
      }
      else if(lireCapteur4())
      {
          while(lireCapteur4())
          {
              tournerUnPeuGauche();
          }
      }
      else if((lireCapteur5() && lireCapteur4()) || lireCapteur5())
      {
          while ((lireCapteur5() && lireCapteur4()) || lireCapteur5())
          {
              tournerGauche();             
          }  
          avancerVitesseConst(0.5);
      }
     
      
  }
    
  arretMouvement();
}


int main()
{
    DDRD = 0xFF;
    DDRA = 0x00;
    suivreLigne();
    //suivreCouloir(true);

  
    return 0;

}
