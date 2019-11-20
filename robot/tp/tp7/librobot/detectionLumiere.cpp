#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "can.h"
#define VERT 0X01
#define ROUGE 0x02
#define ETEINT 0x00


using namespace std;

//ces resultat on etait mesure par un multimetre 
//Bornes sont des valeur en volt 
const double borneSupRien=3.96;
const double borneSupLumineux=4.38;
const double borneSupSombre=2.5;
const double MAX_VOLTAGE=4.41; //c'est la tension mesurer avec un usb si vous utiliser l'alimenteur de tension elle augmente vers 5
const uint8_t MAX_8_BIT=255;


void detecterLumiere()
{
  DDRA = 0x00; // PORT A est en mode entree  
  DDRB = 0xff; //PORTB est en mode sortie
  can test;
  uint8_t resultat;
  resultat = (uint8_t)test.lecture(0);//converssion du resultat de 10 bits vers 8;
  for(;;) 
  {
    resultat = (uint8_t)(test.lecture(0)>>2);
    if(resultat<borneSupLumineux*MAX_8_BIT/MAX_VOLTAGE && resultat>borneSupRien*MAX_8_BIT/MAX_VOLTAGE) //  la lumière est trop forte, on affiche vert 
    {
      PORTB=ROUGE;
    }
    if(resultat<borneSupSombre*MAX_8_BIT/MAX_VOLTAGE && resultat>0) //  la lumière est trop faible, on affiche rouge
    {
      PORTB=VERT;
    }
    if(resultat<borneSupRien*MAX_8_BIT/MAX_VOLTAGE && resultat>borneSupSombre*MAX_8_BIT/MAX_VOLTAGE) //  la lumière est ambiante, on affiche ambre!
    {
      PORTB=VERT;
      _delay_ms(5);
      PORTB=ROUGE;
      _delay_ms(10);
    }
  } 
}