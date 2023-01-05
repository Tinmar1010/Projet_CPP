#include "Iterateur.h"

template <class T>
Iterateur<T> :: Iterateur(const Vecteur<T> &source) : p(source), data(source.v) 
{

}
template <class T>
Iterateur<T> :: ~Iterateur()
{

}
template <class T>
void Iterateur<T> :: reset()
{
    data = p.v;
}
template <class T>
bool Iterateur<T>:: end()const
{
    if(data - p.v >= p._size)
        return true;
    else
        return false;
}
template <class T>
bool Iterateur<T>:: operator++()
{
    if(!end())
    {
        data ++;
        return true;
    }
    else    
        return false;
}
template <class T>
bool Iterateur<T>:: operator++(int)
{
    return operator++();
}

template <class T>
Iterateur<T>::operator T()const
{
    return *data;
}
template class Iterateur <int>;
#include "Client.h"
template class Iterateur <Client>;
#include "Employe.h"
template class Vecteur <Employe>;
#include "Modele.h"
template class Vecteur <Modele>;
#include "Option.h"
template class Vecteur <Option>;
#include "Voiture.h"
template class Vecteur <Voiture>;
#include "Option.h"
template class Iterateur <Option>;
template class Iterateur<Modele>;
template class Iterateur<Employe>;
#include "Contrat.h"
template class Iterateur<Contrat>;