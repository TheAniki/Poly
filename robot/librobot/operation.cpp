#include "operation.h"

#define capteur1 PINA & 0x01
#define capteur2 PINA & 0x02
#define capteur3 PINA & 0x04
#define capteur4 PINA & 0x08
#define capteur5 PINA & 0x10
uint8_t compteurDeCoupure = 0;
uint8_t compteurDeCote = 0;
bool faireGauche = false;
bool faireDroite = false;
bool ligneGauche = false;
bool ligneDroite = false;



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
void faireLigneGauche()
{
    while(!lireCapteur5())
    {
        ajustementPWM(0.2,0.4);
    }
    
}
void faireLigneDroite()
{
     while(!lireCapteur1())
    {
        ajustementPWM(0.5,0.2);
    }
    
}
void suivreCouloir()
{     
     //while(!lireCapteurs()){avancerVitesseConst(0.4);}
     if(lireCapteurs())
     {
         switch (compteurDeCote%2)
         {
         case 0:
            ligneDroite = false;
            ligneGauche = true;
            break;
         case 1:
            ligneDroite = true;
            ligneGauche = false;
            break;
         default:
             break;
         }
         if(!ligneDroite && ligneGauche)
         {
             arretMouvement();
            faireLigneGauche();            
         }
         else if (ligneDroite && !ligneGauche)
         {
             arretMouvement();
            faireLigneDroite();    
         }
         else
         {
             
         }
         
         
     }
     compteurDeCote++;
  
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

void faireCoupure()
{
   
    // while(faireCoupure)
    // {
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
                    
                }
             }       
        }
        compteurDeCoupure++;
        if(compteurDeCoupure>5)
        {
            if(lireCapteurs())
            {
                bool faireGauche = false;
                bool faireDroite = false;
            }
            
        }       

    
}
void faireCouloir(bool faireCouloir)
{
    while(faireCouloir)
    {
        if(!lireCapteurs())
        {
            ajustementPWM(0.5,0.2);
            while(!lireCapteurs()){}
        }
        else if(lireCapteur5())
        {
            arretMouvement();
            ajustementPWM(1,0);
            _delay_ms(100);
            arretMouvement();
            ajustementPWM(0.5,0.2);
            while(!lireCapteur5()){}
        }
        else if(lireCapteur1())
        {
            arretMouvement();
            ajustementPWM(0,1);
            _delay_ms(100);
            arretMouvement();
            ajustementPWM(0.2,0.5);
            while(!lireCapteur1()){}
        }
        /*if(!lireCapteur5&&!lireCapteur1())
        {
            _delay_ms(10);
            while(!lireCapteurs()){
                ajustementPWM(0.5,0.2);
                _delay_ms(100);
                ajustementPWM(0.2,0.5);
            }
            suivreLigneSimplement();
        }*/
    }
}


void suivreLigneBis()// pour faireBoucle, ne va pas continuer jusqua plus rien
{

     if ((lireCapteur1()&&lireCapteur2()) || lireCapteur1())
     {
       while(lireCapteur1() && !(  lireCapteur1()&&lireCapteur2()&&lireCapteur3()  )){tournerGauche();}
       arretMouvement();            
     }
     else if (lireCapteur2())
     {
        while(lireCapteur2() && !(  lireCapteur1()&&lireCapteur2()&&lireCapteur3()  )){tournerUnPeuGauche();}
        arretMouvement();
     }

         else if (lireCapteur3())

         {

            while(lireCapteur3() && !(  lireCapteur1()&&lireCapteur2()&&lireCapteur3()  ))

            {

                avancerVitesseConst(0.5);

            }

            arretMouvement();

             

         }

         else if (lireCapteur4())

         {

             while(lireCapteur4() && !(  lireCapteur1()&&lireCapteur2()&&lireCapteur3()  )){tournerUnPeuDroite();}

              arretMouvement();

            

         }

         else if (lireCapteur5())

         {

             while(lireCapteur5() && !(  lireCapteur1()&&lireCapteur2()&&lireCapteur3()  ))

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

void faireBoucle()

{

    suivreLigneBis();//On part de L
    
    int intersections = 0;

    bool faireCouloir = true;

    while(faireCouloir)

    {

        if (lireCapteur1()&&lireCapteur2()&&lireCapteur3()){ //on detecte la ligne transversale sur la gauche

            _delay_ms(10);

            if (lireCapteur1()&&lireCapteur2()&&lireCapteur3()){

                intersections++;

                avancerVitesseConst(0.5);

                _delay_ms(300);

            }
            if ((intersections >= 3)&&(intersections <= 10)){ //intersections qui correspondent a un virage sur la gauche

                //tournerGauche90();
                while(!lireCapteur1())
                {
                    tournerGauche();
                }
                arretMouvement();
                //suivreLigneBis();

            }
            else if ((intersections == 12))
            {
                  while(!lireCapteur1())
                {
                    tournerGauche();
                }
                arretMouvement();
                faireCouloir = false;
            }
            else{

                avancerVitesseConst(0.4);

            }
                       
        }
        else
        {
            suivreLigneBis();

        } 

    }
}

    //suivreLigneSimplement();//On va jusqu a T, tourner apres ou pas


