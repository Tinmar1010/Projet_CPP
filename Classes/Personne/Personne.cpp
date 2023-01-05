#include "Personne.h"

/******************************Constructeur et destructeur***************************/
Personne :: Personne()
{
    nom = "";
    prenom = ""; 
}
Personne :: Personne(string n, string pre)
{
    setNom(n);
    setPrenom(pre);
}
Personne :: Personne(const Personne& source)
{
    setNom(source.getNom());
    setPrenom(source.getPrenom());
}
Personne :: ~Personne()
{
    //cout<<"Destructeur de Personne"<<endl;
}
/********************************Getters et Setters**********************************/
string Personne :: getNom()const
{
    return nom;
}
string Personne :: getPrenom()const
{
    return prenom;
}
void Personne :: setNom(string n)
{
    nom = n;
}
void Personne :: setPrenom(string p)
{
    prenom = p;
}
/********************************Surchage Opérateur**********************************/
Personne& Personne :: operator=(const Personne& p)
{
    nom = p.nom;
    prenom = p.prenom;

    return (*this);
}
ostream& operator<<(ostream& out, const Personne& p)
{
    out<<"Nom : "<<p.nom<<endl<<"Prenom : "<<p.prenom<<endl;

    return out;
}
istream& operator>>(istream& in, Personne& p)
{
    string n, pr;

    cout<<"Nom : ";
    in>>n;
    cout<<"Prenom : ";
    in>>pr;

    p.nom = n;
    p.prenom = pr; 

    return in;
}
void Personne :: Save(ofstream & fichier)
{
    
    int tailleN =nom.size();
    fichier.write((char*)&tailleN, sizeof(int));
    fichier.write((char*)nom.data(), tailleN*(sizeof(char)));

    int tailleP = prenom.size();
    fichier.write((char*)&tailleP, sizeof(int));
    fichier.write((char*)prenom.data(), tailleP*(sizeof(char)));
}
void Personne :: Load(ifstream & fichier)
{
   
    int tailleN, tailleP;

    fichier.read((char*)&tailleN, sizeof(int));
    nom.resize(tailleN);
    fichier.read((char*)nom.data(), tailleN*(sizeof(char)));

    fichier.read((char*)&tailleP, sizeof(int));
    prenom.resize(tailleP);
    fichier.read((char*)prenom.data(), tailleP*(sizeof(char)));
}