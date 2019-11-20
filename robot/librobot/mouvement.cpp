#include "mouvement.h"


void initialisationMouvement()
{
    DDRD = 0xFF; //port D en sortie
    PORTD=(0X00<<6);
}
void arretMouvement()
{
    ajustementPWM(0,0);    
}
void tournerDroite45()
{
    PORTD=(0X00<<6);
    ajustementPWM(0,0.5);
    _delay_ms(1000);
    arretMouvement();
}
void tournerDroite90()
{
    PORTD=(0X00<<6);
      ajustementPWM(0,0.5);
    _delay_ms(2000);
    arretMouvement();
}
void tournerGauche45()
{
    PORTD=(0X00<<6);
    ajustementPWM(0.5,0);
    _delay_ms(1000);
    arretMouvement();
}
void tournerGauche90()
{
    PORTD=(0X00<<6);
      ajustementPWM(0.5,0);
    _delay_ms(2000); //~95 100 degree
    arretMouvement();
}                                                                                                                                    
void tournerUnPeuDroite()
{
   ajustementPWM(0.3,0.5);
}
void tournerUnPeuGauche()
{
    ajustementPWM(0.5,0.3);
}
void tournerDroite()
{
    ajustementPWM(0.2,0.7);
}
void tournerGauche()
{
    ajustementPWM(0.7,0.2);
} 
void arreterMoteurA()
{
    //ajustementPWMmoteurA(0);
}
void arreterMoteurB()
{
    //ajustementPWMmoteurB(0);
}                                                                                           