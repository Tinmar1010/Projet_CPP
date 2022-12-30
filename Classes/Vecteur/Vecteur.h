#ifndef VECTEUR_H
#define VECTEUR_H

#include <iostream>
#include "Client.h"

using namespace std;

template <class T> class Iterateur;
template <class T> class Vecteur
{
    friend class Iterateur<T>;
    
    protected : 
        T *v;
        int _sizemax;
        int _size;

    public : 

        Vecteur();
        Vecteur(const int);
        Vecteur(const Vecteur&);
        ~Vecteur(void);

        T& operator[](int);
        Vecteur <T>& operator=(const Vecteur&);

        int size();
        int sizeMax();
        void Affiche();
        void insere(const T&);
        T retire(int);

};

#endif