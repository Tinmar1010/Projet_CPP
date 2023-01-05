#ifndef __CONTRAT_H__
#define __CONTRAT_H__

#include <iostream>
#include <string>
#include "Employe.h"
#include "Client.h"
#include <fstream>



using namespace std;

class Contrat 
{
    friend ostream& operator<<(ostream& out, const Contrat& c);
    friend istream& operator>>(istream& in, Contrat& c);

    private:
        Employe *vendeur;
        Client *client;
        int numero;
        string nomprojet;

    public : 
        Contrat();
        Contrat(int, Employe*, Client*, string);
        Contrat(const Contrat&);
        ~Contrat();

        void setClient(Client*);
        void setVendeur(Employe *);
        void setNumero(int);
        void setNomprojet(string);

        string Tupple();
        int getNumero()const;
        Employe *getVendeur()const;
        Client *getClient()const;
        string getNomprojet()const;

        Contrat& operator=(const Contrat&);

        static int numContrat;
        
        void Save(ofstream &);
        void Load(ifstream &);
};

#endif