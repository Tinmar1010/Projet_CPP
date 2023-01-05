#include "Contrat.h"

int Contrat::numContrat = 1;

Contrat :: Contrat() 
{
    vendeur = NULL;
    client = NULL;
    numero = 0;
    nomprojet = "";

}

Contrat :: Contrat(int num, Employe* empl, Client* cli, string nom)
{
    setNumero(num);
    setNomprojet(nom);
    vendeur = empl;
    client = cli;
}   
Contrat :: Contrat(const Contrat& source)
{
    setNumero(source.getNumero());
    setNomprojet(source.getNomprojet());
    vendeur = source.vendeur;
    client = source.client;
}
Contrat :: ~Contrat()
{

}

void Contrat :: setNumero(int num)
{
    numero = num;
}
void Contrat :: setNomprojet(string nom)
{
    nomprojet = nom;
}
int Contrat :: getNumero()const
{
    return numero;
}
string Contrat :: getNomprojet()const
{
    return nomprojet;
}

Contrat& Contrat ::operator=(const Contrat& c)
{
    setNumero(c.getNumero());
    setNomprojet(c.getNomprojet());
    setVendeur(c.getVendeur());
    setClient(c.getClient());
    client = c.client;
    return (*this);
}

ostream& operator<<(ostream& out, const Contrat& c)
{
    out << c.getNumero() << endl;
    out << c.getNomprojet() << endl;
    out << c.getVendeur() <<endl;
    out << c.getClient() <<endl;
    return out;
}

Employe* Contrat::getVendeur() const
{
    return vendeur;
}

Client *Contrat::getClient()const
{
    return client;
}

void Contrat::setClient(Client *c)
{
    client = c;
}

void Contrat::setVendeur(Employe *e)
{
    vendeur = e;
}

string Contrat::Tupple()
{
    string chaine;

    chaine = to_string(getNumero()) + ';' + getVendeur()->getNom() + "..." + ';' + getClient()->getNom() +"..."+ ';' + getNomprojet();

    return chaine; 
}
void Contrat :: Save(ofstream & fichier)
{
    fichier.write((char*)&numero, sizeof(int));
    int taille = nomprojet.size();
    fichier.write((char*)&taille, sizeof(int));
    fichier.write((char*)nomprojet.data(), taille*(sizeof(char)));


}
void Contrat :: Load(ifstream & fichier)
{
    int taille;
    fichier.read((char*)&numero, sizeof(int));
    fichier.read((char*)&taille, sizeof(int));
    nomprojet.resize(taille);
    fichier.read((char*)nomprojet.data(), taille*(sizeof(char)));

}