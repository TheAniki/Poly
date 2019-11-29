#include "operation.h"

#define capteur1 PINA & 0x01
#define capteur2 PINA & 0x02
#define capteur3 PINA & 0x04
#define capteur4 PINA & 0x08
#define capteur5 PINA & 0x10
uint8_t compteurDeCoupure = 0;

void initialisationGeneraleDesOperations()
{
    DDRA = 0x00;
    DDRB = 0xff;
    initialisationMouvement();
}
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
bool lireTousCapteurs(void)
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
            if((capteur3 || !capteur1 || !capteur2 || capteur4 || capteur5 ))
            {
                return true;
            }
            return false;
        }
        return false;
}

void suivreToutesLignes()
{
   initialisationGeneraleDesOperations();
   
    
         if ((lireCapteur1()&&lireCapteur2()) || lireCapteur1())
         {
             while(lireCapteur1()){tournerGauche();}
             arretMouvement();            

         }
         else if (lireCapteur2())
         {
            while(lireCapteur2()){tournerUnPeuGauche();}
             arretMouvement();
            
         }
         else if (lireCapteur3())
         {
             while(lireCapteur3()){avancerVitesseConst(0.5);}
              arretMouvement();
             
         }
         else if (lireCapteur4())
         {
             while(lireCapteur4()){tournerUnPeuDroite();}
              arretMouvement();
            
         }
         else if (lireCapteur5())
         {
             while(lireCapteur5())
             {
                 tournerDroite(); 
                if(!lireCapteur5())
                {
                    arretMouvement();
                    break; 
                }
            }           
             
              arretMouvement();
              
         }
         else if(CapteursGauche())
         {
             while(!lireCapteur5()){
                   
                    tournerGauche();            
                }
                arretMouvement();

        }
        else if(CapteursDroite())
        {
                while(!lireCapteur1()){
                    tournerDroite();
                   }
                   arretMouvement();
        }
        else
        {
            
            while(!lireCapteur5() && !lireCapteur1()){
                  
                    tournerGauche();           
                }   
                arretMouvement();        
           
        }       

}
void suivreLigneSimplement()
{
     if ((lireCapteur1()&&lireCapteur2()) || lireCapteur1())
         {
             while(lireCapteur1()){tournerGauche();}
             arretMouvement();            

         }
         else if (lireCapteur2())
         {
            while(lireCapteur2()){tournerUnPeuGauche();}
             arretMouvement();
            
         }
         else if (lireCapteur3())
         {
             while(lireCapteur3()){avancerVitesseConst(0.5);}
              arretMouvement();
             
         }
         else if (lireCapteur4())
         {
             while(lireCapteur4()){tournerUnPeuDroite();}
              arretMouvement();
            
         }
         else if (lireCapteur5())
         {
             while(lireCapteur5())
             {
                 tournerDroite(); 
                if(!lireCapteur5())
                {
                    arretMouvement();
                    break; 
                }
            }           
             
              arretMouvement();
              
         }
         else
         {}           
          
}

void suivreCouloir()
{     
       

}

void faireCoupureDroite(bool faire)
{    
     
    
     if(!lireCapteurs())
     {
        _delay_ms(10);
        if(!lireCapteurs()){tournerUnPeuDroite();_delay_ms(10); while(!lireCapteurs()){}} 
     }
   

   
                             
}

void faireCoupureGauche(bool faire)
{
    
     if(!lireCapteurs())
     {
        _delay_ms(10);
        if(!lireCapteurs()){tournerUnPeuGauche();_delay_ms(10);while(!lireCapteurs()){}}     
     } 
         
    
}

void faireCoupure(bool faireCoupure)
{
    bool faireGauche = false;
    bool faireDroite = false;
    while(faireCoupure)
    {
        while(lireCapteurs()){suivreLigneSimplement();}
        if(!lireCapteurs())
        {
            _delay_ms(25);
            if(!lireCapteurs())
             {
                switch (compteurDeCoupure%2)
                {
                case 0:
                    faireDroite = true;
                    faireGauche = false;
                    break;
                case 1:
                    faireGauche = true;
                    faireDroite = false;    
                    break;
                default:
                    break;
                }
                if(faireDroite && !faireGauche)
                {   
                    arretMouvement();
                    faireCoupureDroite(faireDroite);
                }
                else if (!faireDroite && faireGauche)
                {
                    arretMouvement();
                    faireCoupureGauche(faireGauche);
                }
                else
                {
                    break;
                }
             }       
        }
        compteurDeCoupure++;        

    }
}

void faireBoucle()
{

}

