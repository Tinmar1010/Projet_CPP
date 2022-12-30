#ifndef INTERVENANT_H
#define INTERVENANT_H

using namespace std;

#include<iostream>
#include<string.h>
#include <string>
#include "Personne.h"

using namespace std;

class Intervenant : public Personne
{
    friend ostream& operator<<(ostream& out, const Intervenant& i);
    friend istream& operator>>(istream& in, Intervenant& i);

    protected : 
        int numIntervenant;

    public : 
        static int numCourant;
        Intervenant();
        Intervenant(string, string, int);
        Intervenant(const Intervenant&);
        virtual ~Intervenant();

        void setNumero(int);
        int getNumero()const;

        virtual string ToString()= 0; //N'apparait pas dans le .cpp
        virtual string Tuple()= 0;
        Intervenant& operator=(const Intervenant&);
};


#endif