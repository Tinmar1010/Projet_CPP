#ifndef VECTEURTRIE_H
#define VECTEURTRIE_H

#include <iostream>
#include "Vecteur.h"

using namespace std;

template <class T> class Iterateur;
template <class T> class VecteurTrie : public Vecteur <T>
{
    friend class Iterateur<T>;
    
    public : 

        VecteurTrie();
        VecteurTrie(const int);
        VecteurTrie(const VecteurTrie&);
        ~VecteurTrie(void);

        void insere(const T&);

};






#endif