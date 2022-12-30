#include "Vecteur.h"


template <class T>
Vecteur <T>::Vecteur()
{
    _sizemax = 20;
    _size = 0;
    v = new T[_sizemax];

    T temp;
    for(int i=0;i<_size;i++)
        v[i] = temp;

    
}
template <class T>
Vecteur <T>::Vecteur(const int n)
{
    _sizemax = n;
    _size = 0;
    v = new T[_sizemax];

    T temp;
    for(int i=0;i<_size;i++)
        v[i] = temp;
}
template <class T>
Vecteur <T> :: Vecteur(const Vecteur& t)
{
    _size = t._size;
    _sizemax = t._sizemax;
    int i = 0;
    v = new T[t._sizemax];
    while(i<_size)
    {
        v[i] = t.v[i];
        i++;
    }
    
}
template <class T>
Vecteur <T>::~Vecteur()
{
    if(v!=NULL)
        delete [] v;
    
}

template <class T>
int Vecteur <T>::size()
{
    return _size;
}

template <class T>
int Vecteur <T>::sizeMax()
{
    return _sizemax;
}

template <class T>
void Vecteur <T>::Affiche()
{
    int i = 0;
    while (i<_size)
    {
        cout<<' '<<v[i]<<' ';  
        i++;
    }
}

template <class T>
void Vecteur <T>::insere(const T& t)
{
    int i = 0;
    i = _size;
    _size = _size + 1;
    v[i] = t;
}
template <class T>
T Vecteur <T> :: retire(int i)
{
    T temp;
    temp = v[i];

    for(int j = i;j<_size;j++)
        v[j] = v[j+1];

    _size = _size - 1;   
    
    return temp;
}
template <class T>
Vecteur <T> & Vecteur<T>::operator=(const Vecteur&t)
{
    _sizemax = t._sizemax;
    _size = t._size;
    for (unsigned int i = 0;i<_size;i++)
    {
        v[i] = t.v[i];
    }

    return(*this);
}
template <class T>
T& Vecteur<T>:: operator[](int i)
{
    return *(v + i);
}

template class Vecteur <int>;
#include "Client.h"
template class Vecteur <Client>;
#include "Employe.h"
template class Vecteur <Employe>;
#include "Modele.h"
template class Vecteur <Modele>;
#include "Option.h"
template class Vecteur <Option>;
#include "Voiture.h"
template class Vecteur <Voiture>;

