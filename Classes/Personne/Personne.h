#ifndef PERSONNE_H
#define PERSONNE_H


#include<iostream>
#include<string.h>
#include <string>

using namespace std;

class Personne
{
    friend ostream& operator<<(ostream& out, const Personne& p);
    friend istream& operator>>(istream& in, Personne& p);

    protected : 
        string nom;
        string prenom;

    public : 
        Personne();
        Personne(string, string);
        Personne(const Personne&);
        ~Personne();


        string getNom()const;
        string getPrenom()const;

        void setNom(string);
        void setPrenom(string);

        Personne& operator=(const Personne&);

};

#endif