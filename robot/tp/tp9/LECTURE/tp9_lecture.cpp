#include <avr/io.h>
#include <string.h>

#include "debug.h"
#include "can.h"
#include "Son.h"
#include "mouvement.h"
#include "PWMDEL.h"
#include "memoire_24.h"


enum Instructions{
    dbt = 0x01, //debut
    att = 0x02, //attendre
    dal = 0x44, //allumer Del
    det = 0x45, //eteindre Del
    sgo = 0x48, //jouer son
    sar = 0x09, // arreter son
    mara = 0x60, //arreter moteur a
    marb = 0x61, // arreter moteur b
    mav = 0x62, //avancer
    mre = 0x63, //reculer
    trd = 0x64, //tourner droite
    trg = 0x65, //tourner gauche
    dbc = 0xC0, // debut boucle
    fbc = 0xC1, // fin boucle
    fin = 0xFF // The End
};

void initialisationVariables()
{
    //led
    DDRA = 0xFF;
    //moteurs
    DDRD=0xFF; //moutueur droit : d6d7 et mouteur gauche: d5d8

      //memoire externe
    DDRC = 0x03;
    //haut-parleur
    DDRB =0xff;

}

int main()
{
    initialisationVariables();  

    //initialisation de la memoire externe et de la taille du fichier

    Memoire24CXXX memoire;
    uint16_t tailleDuFichier;

    //initialisation des variables locale de la boucle
    
    uint16_t compteurAdresse = 0x00;
    uint16_t adresseDeLaBoucle;
    uint8_t  compteur; 

    //initalisation Son
    Son son;

    //initialisation des varibles locale pour le stockage
    uint8_t donnee;
    uint8_t operande;

    delVerte(1000); //allume la del verte pendnant 1 sec lorsque les etapes precedentes sont accomplie

    bool debuter = false;

    while (donnee!=dbt)
    {//lecture de la memoire
        memoire.lecture(compteurAdresse, &donnee);
        compteurAdresse+=2;// ++ avant, changer selon prof mais ca marcahit bien avant
    }

    debuter=true;

    
    while(debuter)
    {
        memoire.lecture(compteurAdresse,&operande);
        compteurAdresse++;
        if (donnee == dbt)
        {
            debuter = true;
            DEBUG_PRINT((" signal debut recu \n"));    
        }
        
        if (debuter == true)
        {
            switch (donnee)
            {

            case dbt:
                DEBUG_PRINT(("debut \n"));
                delVerte(1000); //on allume la del pour marquer le debut
                break;

            case att:   
                _delay_ms(5);
                DEBUG_PRINT(("j'attends\n"));
                
                for (uint8_t i = 0; i < operande; i++)
                {
                    _delay_ms(10); //attende de 10ms fois l'operande donnee
                }
                
                break;

            case dal:
                DEBUG_PRINT(("allume la del\n"));
                delRouge(1000);  //on allume la del rouge une sec
                son.operationFaite(); //indice sonore que l'operation a ete faite
                break;

            case det:
                DEBUG_PRINT(("eteindre la del\n"));
                delEteinte();
                son.operationFaite();//indice sonore que l'operation a ete faite
                break;

            case sgo:
                DEBUG_PRINT(("joue une sonorite\n"));
                              
                switch (operande) // on a le droit a soit l'operoande 6 ou 9 pour jouer l'une des deux melodies sinon on joue rien
                {
                case 6:
                    son.DejaVu();
                    break;
                case 9:
                    son.GameOfThrones();
                    break;
                default:
                    break;
                }

            case sar:
                DEBUG_PRINT(("arrete de jouer la sonorite\n"));
                son.arreterSon();
                break;

            case mara:
                DEBUG_PRINT(("arrete le moteur a\n"));
                arreterMoteurA();
                arreterMoteurB();
                break;

            case marb:
                DEBUG_PRINT(("arrete le moteur b\n"));
                arreterMoteurA();
                arreterMoteurB();
                break;

            case mav:
                _delay_ms(5);
                DEBUG_PRINT(("avance\n"));
                for (uint8_t i = 0; i < operande; i++)
                {
                    avancerVitesseConst(0.5); //on avance a une vitesse constante pendant un temps determine par l'operande
                    _delay_ms(100);
                }
                
                break;

            case mre:
                DEBUG_PRINT(("reculer\n"));
                for (uint8_t i = 0; i < operande; i++)
                {
                    reculerVitesseConst(0.5); //on recule a une vitesse constante pendant un temps determine par l'operande
                    _delay_ms(100);
                }
                
                break;

            case trd:
                DEBUG_PRINT(("tourner a droite\n"));
                tournerDroite90();
                break;

            case trg:
                DEBUG_PRINT(("tourner a gauche\n"));
                tournerGauche90();
                break;

            case dbc:
                DEBUG_PRINT(("debut de boucle\n"));
                adresseDeLaBoucle = compteurAdresse; //on marque a quel endroit la boucle commence avec compteurAdresse qui s'incremente a chaque case
                compteur = operande;

                break;

            case fbc:            
                DEBUG_PRINT(("fin de boucle\n"));
                if (compteur>0)
                {
                    compteurAdresse = adresseDeLaBoucle;
                    compteur--; //on deduit les operation refaite
                }
                                          
                break;

            case fin:
                DEBUG_PRINT(("fin\n"));
                return 0;
                arretMouvement();
                break;

            }

        memoire.lecture(compteurAdresse, &donnee);
        compteurAdresse++;
        }
    } 
    return 0;
}      

