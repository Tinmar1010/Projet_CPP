#include "VecteurTrie.h"


template <class T>
VecteurTrie <T>::VecteurTrie() : Vecteur<T>()
{

}
template <class T>
VecteurTrie <T>::VecteurTrie(const int n) : Vecteur<T>(n)
{

}
template <class T>
VecteurTrie <T> :: VecteurTrie(const VecteurTrie& t) : Vecteur<T>(t)
{
    
}
template <class T>
VecteurTrie <T>::~VecteurTrie()
{
    
}


template <class T>
void VecteurTrie <T>::insere(const T& t)
{
    //on doit passer par this pour les templates
    int i = 0;
    i = this->_size;
    this->_size = this->_size + 1;
    this->v[i] = t;

}


template class VecteurTrie <int>;
#include "Client.h"
template class VecteurTrie <Client>;