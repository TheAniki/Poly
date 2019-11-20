#define F_CPU 8000000	
#include <avr/io.h>
#include <util/delay.h>
#include "memoire_24.h"


using namespace std;

const uint8_t ROUGE = 0x01;
const uint8_t VERTE = 0x02;
const uint8_t SORTIE = 0xFF;
const uint8_t ENTREE = 0x00;


int main()
{
    
    DDRA = SORTIE;    

    uint8_t chaine[46] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*"; 
    Memoire24CXXX memoire;

    memoire.ecriture(0x00, chaine, 40);
    _delay_ms(5);
    uint8_t lireChaine[40]="";
    memoire.lecture(0x00, lireChaine,40);
    if (*chaine == *lireChaine)
    {
        PORTA = VERTE;
    }
    else
    {
        PORTA = ROUGE;
    }    
    

    return 0;
}
