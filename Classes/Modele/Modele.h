#ifndef MODELE_H
#define MODELE_H

#include<iostream>
#include <fstream>
#include<string.h>
#include <string>

using namespace std;
enum Moteur { Essence, Diesel, Electrique, Hybride };

class Modele   
{
    friend ostream& operator<<(ostream& out, const Modele& m);
    friend istream& operator>>(istream& in, Modele& m);

    private : 
        char * nom;
        int puissance;
        Moteur moteur;
        float prix;
        string image;
        

    public : 
        Modele();
        Modele(const char *, int, Moteur, float, string);
        Modele(const Modele &);
        ~Modele();

        const char * getNom()const;//"return de la variable"
        int getPuissance()const;
        Moteur getMoteur()const;
        float getPrixDeBase()const;
        string getImage()const;

        void setNom(const char *);
        void setPuissance(int);
        void setMoteur(Moteur);
        void setPrixDeBase(float);
        void setImage(string);

        Modele& operator=(const Modele&);

        void Affiche()const;//Ne modfifie pas les variables membres
        void Save(ofstream &)const;//Ecrire sur le flux de fichier en paramètre
        void Load(ifstream &);//Lire sur le flux de fichier en paramètre
};





#endif