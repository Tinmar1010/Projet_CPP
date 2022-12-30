#include "Garage.h"

Garage Garage :: instance = Garage();
Voiture Garage :: ProjetEnCours = Voiture();
Garage :: Garage()
{   
    
}
Garage :: ~Garage()
{

}
Garage& Garage :: getInstance()
{
    return instance;
}
Voiture& Garage :: getProjetEnCours()
{
    return ProjetEnCours;
}
void Garage :: resetProjetEnCours()
{
    getProjetEnCours() = Voiture();
}
void Garage :: ajouteModele(const Modele & m)
{
    if(modeles.size()<modeles.sizeMax())
        modeles.insere(m);
}
void Garage :: afficheModelesDisponibles()const
{
    Vecteur <Modele> m;

    m = modeles;

    m.Affiche();
    cout<<endl;
}
Modele Garage :: getModele(int indice)
{
    Modele m;
    m = modeles[indice];
    
    return m;
}

void Garage :: ajouteOption(const Option & o)
{
    if(options.size()<options.sizeMax())
        options.insere(o);
}
void Garage :: afficheOptionsDisponibles()const
{
    Vecteur <Option> o;

    o = options;

    o.Affiche();
    cout<<endl;
}
Option Garage :: getOption(int indice)
{
    Option o;
    o = options[indice];
    
    return o;
}

void Garage :: ajouteClient(string nom,string prenom,string gsm)
{
    Client o;

    o.setNumero(o.numCourant);
    o.setGsm(gsm);
    o.setNom(nom);
    o.setPrenom(prenom);

    o.numCourant = o.numCourant + 1;

    if(clients.size()<clients.sizeMax())
        clients.insere(o);
}
void Garage :: afficheClients()const
{
    Vecteur <Client> c;

    c = clients;

    c.Affiche();
    cout<<endl;
}
void Garage :: supprimeClientParIndice(int ind)
{
    clients.retire(ind);
}
void Garage :: supprimeClientParNumero(int num)
{
    int i = 0;

    while(i<clients.size()&&clients[i].getNumero() != num)
        i++;

    clients.retire(i);
}

void Garage :: ajouteEmploye(string nom,string prenom,string login,string fonction)
{
    Employe e;

    e.setNumero(e.numCourant);
    e.setFonction(fonction);
    e.setLogin(login);
    e.setNom(nom);
    e.setPrenom(prenom);

    e.numCourant = e.numCourant + 1;

    if(employes.size()<employes.sizeMax())
        employes.insere(e);
}
void Garage :: afficheEmployes()const
{
    Vecteur <Employe> e;

    e = employes;

    e.Affiche();
    cout<<endl;
}
void Garage :: supprimeEmployeParIndice(int ind)
{
    employes.retire(ind);
}
void Garage :: supprimeEmployeParNumero(int num)
{
    int i = 0;

    while(i<employes.size()&&employes[i].getNumero() != num)
        i++;

    employes.retire(i);
}
void Garage :: importeModeles(string nomfichier)
{
    char temp[128];
    int i = 0;
    char *champ;
    ifstream fichier(nomfichier, ios :: in);
    Modele m;

    if (fichier.is_open())
    {
        while(fichier.getline(temp, sizeof(temp)-1))
        {
            champ = strtok(temp, ";");
            while(champ!=NULL)
            {
                cout<<champ<<endl;
                champ++;
                champ = strtok(NULL, ";");

            }
            m.setNom(champ);
            m.setPuissance(atoi(champ));
            Moteur mot = Essence;
            switch (atoi(champ))
            {
                case 0 : 
                    mot = Essence;
                    break;
                
                case 1 : 
                    mot = Diesel;
                    break;
                
                case 2 : 
                    mot = Electrique;
                    break;

                case 3 : 
                    mot = Hybride;
                    break;
                
            }
            m.setMoteur(mot);
            m.setImage(champ);
            m.setPrixDeBase(atof(champ));
            ajouteModele(m);
        }
    }
}
void Garage :: importeOptions(string nomfichier)
{

}