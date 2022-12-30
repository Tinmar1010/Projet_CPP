#ifndef ITERATEUR_H
#define ITERATEUR_H

#include "Vecteur.h"

using namespace std;

template <class T> class Iterateur
{

    private : 

        T *data;
        const Vecteur<T> &p;

    public : 

        Iterateur(const Vecteur<T> &);
        ~Iterateur();
        void reset();
        bool end()const;

        bool operator++();
        bool operator++(int);

        operator T()const;
};


#endif