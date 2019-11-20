/*
Auteurs : Ouassim Ouali et Kevin Wassef
*/

#include <avr/io.h> 
#define F_CPU 1000000
#include <util/delay.h>

#define B_P PIND & 0x04

int main()
{
  DDRA = 0xff; // PORT B est en mode sortie
  int a = 3000;
  int c = 0;
for(;;)
{
    PORTA=0x01;  
  if (B_P) 
   {
      _delay_ms(10);
      if (B_P)
      {
         for(;;)
         {
           for (int i = 0; i < a; i++)
           {
             PORTA = 0x02;                                    
           }
           for (int j = 0; j < c; j++)
           {
             PORTA = 0x00;             
           }
           a-=3;
           c+=3;                 

           
         }
         
         
                
      }      
  }  
}

return 0;  
} 