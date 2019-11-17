#ifndef Emission_H
#define Emission_H


#include "Chaine.h"
#include <string>


using namespace std;

        

// Cette classe représente un Emission
class Emission {
public:
    // Constructeurs
    Emission();
    Emission(string, string, string, string, string);

    // Setters
    void setTitre(string);

    void setAnimateur(string);

    void associerChaine(Chaine*);

    

    // Getters

    string getTitre();

    string getAnimateur();

    

    //Ajout de la classe getChaine, qui retourne la chaine en attribut

    Chaine* getChaine();

    

    // Enregistrer l'Emission

    void saveEmission(string);

    // Afficher l'Emission

    void afficher();


    //lectureAttribut 

    string lectureAttribut(int &i, string line);

    // Chercher un Emission dans une base de données par titre

    Emission* trouverEmission(string, string);

    

private:

    // Information sur l'emission

    string titre;

    string animateur;


    //Ajout de cet attribut: Relation de composition entre l'emission et la chaine.

    //(On ne peut pas avoir d'emission sans chaine)

        Chaine* chaine;

};


#endif 

