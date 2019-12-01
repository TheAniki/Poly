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
      ajustementPWM(0,0.6);
    _delay_ms(1800);
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
    _delay_ms(1800); //~95 100 degree
    arretMouvement();
}                                                                                                                                    
void tournerUnPeuDroite()
{
     arretMouvement();
   ajustementPWM(0.3,0.5);
}
void tournerUnPeuGauche()
{
     arretMouvement();
    ajustementPWM(0.5,0.3);
}
void tournerDroite()
{
     arretMouvement();
    ajustementPWM(0.2,0.6);
}
void tournerGauche()
{
     arretMouvement();
    ajustementPWM(0.6,0.2);
} 
                                                                                     