/*	Auteurs: Ouassim Ouali et Kevin Wassef 
	equipe :  40
	tp6 probleme 2: Ce programme prend en entree l'intensite lumineuse captee par la photoresistance fait la conversion du signal analogique
	vers numerique ( de 10 bits ) puis fait la convertion de 10 bits vers 8 bits 
	afin d'afficher une couleur differente en fonction de l'intensite lumineuse recue selon des seuils predefinis suivant:
	 
	|=========================================|
	|Couleur de la del | interval d'intensite |
	|------------------|----------------------|
	|	    Verte      |     [ 0 , 180 ]      |
	|       Ambre      |    ] 180 , 240 [	  |
	|       Rouge      |    [ 240 , 255 [     |
	|=========================================|

	La valeur maximale du Rouge est definie par le fait que la convertion analogique => numerique
	est faite sur 8 bits donc le bit maximal est (2^8 - 1) = 255, ce qui explique la valeur maximale de conversion.

	Utilisation des broches : Le cable rouge et noir est relié au PORTA, le fil rouge etant connecté au VCC et
							  le fil noir au GND.

							  Le cable bleu et brun sont connectes au PORTA, le fil bleu étant connecté au port A0 et
							  le brun au port A1.

							  La DEL est connectee au PORTB a B0 et B1.
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "can.h"

using namespace std;

const uint8_t ETEINTE = 0x00;
const uint8_t ROUGE = 0x01;
const uint8_t VERTE = 0x02;
const uint8_t SORTIE = 0xFF;
const uint8_t ENTREE = 0x00;
volatile uint8_t ETAT = 0;

struct seuilLumiere // creation d'une structure seuilLumiere permettant d'initialiser les valeurs maximales
{
	uint8_t basse = 180;	//initialisation de la valeur maximale pour une lumiere consideree basse.
	uint8_t ambre = 240;	//initialisation de la valeur maximale pour une lumiere consideree ambiante.
};
// Fonction Ambre
// permet a la del d'emettre la couleur ambree, en alternant entre les couleurs rouge et vert avec un interval de 3 ms
// la fonction ne retourne rien.
void AMBRE() 
{
	PORTB = ROUGE; 
	_delay_ms(3);	// delais de 3 ms 
	PORTB = VERTE;
	_delay_ms(3);	// delais de 3 ms
}
int main()
{
    DDRB = SORTIE; //initialisation des pin de B en sortie
    DDRA = ENTREE; // initialisation des pin de A en entree 
    can convertiseur; // convetiseur de la classe can permetant l'utilisation de la methode lecture permettant de lire les signaux analogique
	seuilLumiere lumiere; // initialisation d'une variable de la structure seuilLumiere contenant les seuils maximaux.

    for(;;)
    {

        uint8_t puissance = (convertiseur.lecture(1) >> 2); // intialisation de la variable puissance contenant la conversion de la valeur	
															//analogique vers numerique de la lumiere emise par le capteur
															// prend un signal en 10bits et le converti
															// en 8 bit en decalant le bit de 2 vers la droite.

		if (puissance <= lumiere.basse) // lorsque la puissance est inferieure ou egale au seuil maximal d'une lumiere basse
			PORTB = VERTE;				// la del emet une lumiere verte.
		else if (puissance > lumiere.basse && puissance < lumiere.ambre)	// lorsque la puissance est superieure au seuil maximal d'une lumiere basse et inferieure au seuil maximal d'une lumiere ambree.
			AMBRE();														// alors la del emet une couleur ambree.
        else
            PORTB = ROUGE;        //si la puissance est superieur ou egal au seuil maximal d'une lumiere ambre alors la del emet une couleur rouge.
    }

    return 0;
}