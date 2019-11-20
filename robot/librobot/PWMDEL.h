#ifndef PWMDEL_H    
#define PWMDEL_H

#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#define BUTTON_IS_PRESSED PIND & 0X04
#define ROUGE 0X01
#define VERT 0X02
#define ETIENT 0X00

void my_delay(uint16_t const& NbOf25Us);
void boucle60hz(uint32_t a,uint32_t b);
void boucle400hz(uint16_t a,uint16_t b);
void delRouge(int delay);
void delRouge();
void delVerte(int delay);
void delVerte();
void delEteinte();


#endif // PWMDEL_H