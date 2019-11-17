#include "Emission.h"
#include <fstream>

#include <iostream>


// Constructeur

Emission::Emission() : titre(""), animateur("")

{

    this->chaine = new Chaine();

}


Emission::Emission (string titre,

                  string animateur,

                  string chaineName,

                  string chaineCodePostal,

                  string chaineAddress) {

    // Emission information

    this->titre = titre;

    this->animateur = animateur;


    this->chaine = new Chaine(chaineName, chaineCodePostal, chaineAddress);

    

    /* 

    // Chaine information

    this->chaineName = chaineName;

    this->chaineCodePostal = chaineCodePostal;

    this->chaineAddress = chaineAddress;

    */


}


// Setters

void Emission::setTitre(string titre) {

    this->titre = titre;

}

void Emission::setAnimateur(string animateur) {

    this->animateur = animateur;

}


// Associer un chaine à l'Emission

void Emission::associerChaine (Chaine* chaine) {

    /*this->chaineName = chaineName;

    this->chaineCodePostal = chaineCodePostal;

    this->chaineAddress = chaineAddress;

    */

    this->chaine = chaine; 

}



// Getters

string Emission::getTitre() {

    return this->titre;

}

string Emission::getAnimateur() {

    return this->animateur;

}


Chaine* Emission::getChaine() {

   // return this->chaine.chaineAddress;

   return this->chaine;

}


// Enregistrer l'Emission dans un fichier

void Emission::saveEmission (string fileName) {


    ofstream outfile (fileName.c_str(), std::ofstream::binary | std::fstream::app);

    // write to outfile

    outfile<<this->titre <<","

                   <<this->animateur << endl;

            outfile.close();

}


string Emission::lectureAttribut(int &it, string line)

{

    string attribut = "";

    for (it = it + 1; it < line.length() ; it++) {

                    if (line[it] != ',') {

                        attribut += line[it];

                    } else {

                        return attribut;

                    }

                }

}

// Trouver un Emission avec son nom dans la base de données DB

Emission* Emission::trouverEmission (string DB, string titre) {

    

    ifstream fichier(DB.c_str(), ios::in); // Ouvrir le fichier "DB.txt"

        

    if(fichier)

    {

        string line;

        // Lire les Emissions, un Emission par ligne dans la base de données (DB.txt)

        while (getline(fichier, line)) {

            // Récupérer le nom de l'Emission

            int i = -1;

            string titreDB = lectureAttribut(i, line);

            if (titreDB == titre) {

                

                // Récupérer le nom de l'animateur

                string animateurDB = lectureAttribut(i, line);

                

                //  Récupérer le nom de l'éditeur

                string chaineNameDB = lectureAttribut(i, line);

                

                // Récupérer le code postale de l'éditeur

                string chaineCodePostalDB = lectureAttribut(i, line);

                

                // Récupérer l'addresse de l'éditeur

                string chaineAddressDB = lectureAttribut(i, line);
                // Créer un objet de type Emission avec les informations récupérées

                Emission *a = new Emission(titreDB, animateurDB, chaineNameDB, 
chaineCodePostalDB, chaineAddressDB);


                // Fermer la base de données

                fichier.close();

                // Retourner l'Emission sélectionné

                return a;


                /*

                On pourrait mettre le code de la ligne 98 a 111
 dans une methode "lectureEmission", mais comme on ne le reutilise plus

                dans ce programme, ce n'est pas necessaire.

                */

            }

          

            

        }

        // Fermer la base de données

        fichier.close();

    }

    // Si l'Emission est innexistant, on retourne NULL

    // return NULL;

    return NULL;


}


// Afficher l'Emission

void Emission::afficher() {

    std::cout << "Titre : " << this->titre << std::endl;

    std::cout << "Animateur : " << this->animateur << std::endl;

    this->chaine->afficher();

}





