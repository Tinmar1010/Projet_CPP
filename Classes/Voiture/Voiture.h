#ifndef VOITURE_H
#define VOITURE_H


#include "Modele.h"
#include "Option.h"

#include<string.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Voiture
{
    friend Voiture operator+(const Option&, Voiture);
    friend ostream& operator<<(ostream& out, const Voiture& v);


    private : 

        string nom;
        Modele modele;
        Option * options[5] = {NULL};
        int compV(const Voiture&) const;

    public : 

        Voiture();
        Voiture(string, Modele);
        Voiture(const Voiture &);
        ~Voiture();
        string getNom()const;
        Modele getModele()const;

        void setNom(string);
        void setModele(Modele);

        void AjouteOption(const Option &);
        void RetireOption(string);
        float getPrix()const;

        Voiture& operator=(const Voiture&);
        Voiture operator+(const Option&);
        Voiture operator-(const Option&);
        Voiture operator-(const string&);
        int operator<(const Voiture&);
        int operator>(const Voiture&);
        int operator==(const Voiture&);
        Option* operator[](int);


        void Affiche();
        void Save();//Ecrire sur le flux de fichier en paramètre
        void Load(string);//Lire sur le flux de fichier en paramètre

};


#endif