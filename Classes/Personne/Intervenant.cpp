#include "Intervenant.h"

int Intervenant :: numCourant = 0;

/******************************Constructeur et destructeur***************************/
Intervenant :: Intervenant() : Personne()
{
    numIntervenant = 0;
}
Intervenant :: Intervenant(string nom, string prenom, int num) : Personne(nom, prenom)
{
    numIntervenant = num;
}
Intervenant :: Intervenant(const Intervenant& source) : Personne(source)
{
    setNumero(source.getNumero());
}
Intervenant :: ~Intervenant()
{
    //cout<<"Destructeur de Intervenant"<<endl;
}
/********************************Getters et Setters**********************************/
void Intervenant :: setNumero(int n)
{
    numIntervenant = n;
}
int Intervenant :: getNumero()const
{
    return numIntervenant;
}
/********************************Surchage Opérateur**********************************/
Intervenant& Intervenant :: operator=(const Intervenant& i)
{
    Personne :: operator=(i);

    numIntervenant = i.numIntervenant;

    return(*this);
}
ostream& operator<<(ostream& out, const Intervenant& i)
{
        
    out<<"Nom : "<<i.nom<<endl<<"Prenom : "<<i.prenom<<endl<<"Numéro d'Intervenant : "<<i.numIntervenant<<endl;

    return out;
}
istream& operator>>(istream& in, Intervenant& i)
{
    string nom, prenom;
    int numI;

    cout<<"Nom : ";
    in>>nom;
    cout<<"Prenom : ";
    in>>prenom;
    cout<<"Numéro d'intervenant";
    in>>numI;

    i.nom = nom;
    i.prenom = prenom;
    i.numIntervenant = numI;
    
    return in;
}

void Intervenant :: Save(ofstream &fichier)
{
    
    fichier.write((char*)&numIntervenant, sizeof(int));

    Personne :: Save(fichier);    
}


void Intervenant :: Load(ifstream & fichier)
{
    
    fichier.read((char*)&numIntervenant, sizeof(int));

    Personne :: Load(fichier);
}