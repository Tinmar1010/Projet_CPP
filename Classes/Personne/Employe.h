#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <iostream>
#include <string>
#include <cctype>
#include "Intervenant.h"
#include "PasswordException.h"

using namespace std;

class Employe : public Intervenant
{
    friend ostream& operator<<(ostream& out, const Employe& e);
    friend istream& operator>>(istream& in, Employe& e);

    protected : 

        string login;
        string * motDePasse;
        string fonction;

    public : 
        static string ADMINISTRATIF;
        static string VENDEUR;

        Employe();
        Employe(string, string, int, string, string);
        Employe(const Employe&);
        ~Employe();

        void setLogin(string);
        void setMotDePasse(string);
        void ResetMotDePasse();
        void setFonction(string);
        string getLogin()const;
        string getMotDePasse()const;
        string getFonction()const;
        string ToString();
        string Tuple();
        
        Employe& operator=(const Employe &);

        void Save(ofstream &);
        void Load(ifstream &);
};


#endif