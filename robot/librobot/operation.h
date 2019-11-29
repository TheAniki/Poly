#ifndef OPERATION_H
#define OPERATION_H

#include "mouvement.h"

void initialisationGeneraleDesOperations(void);

//methode de lecture des capteurs:
bool lireCapteur1(void);
bool lireCapteur2(void);
bool lireCapteur3(void);
bool lireCapteur4(void);
bool lireCapteur5(void);
bool lireCapteurs(void);
bool lireTousCapteurs(void);
bool CapteursGauche(void);
bool CapteursDroite(void);

// methode utiliser par les operations
void faireCoupureDroite(bool);
void faireCoupureGauche(bool);

// liste des operations 
void suivreLigneSimplement();
void suivreToutesLignes();
void faireCoupure(bool);
void faireCouloir(); // il manque faire couloir
void faireBoucle();  // il manque faire boucle

#endif // !OPERATION_H

