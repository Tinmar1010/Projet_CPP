#include "Garage.h"

Garage Garage :: instance = Garage();
Voiture Garage :: ProjetEnCours = Voiture();

Employe* Garage::pE = NULL;

Garage :: Garage()
{   
    modeles = Vecteur <Modele>(50);
    options = Vecteur <Option>(50);
    employes = Vecteur <Employe>(50);

    ajouteEmploye("Emma", "Karen Ah", "Emma", "Administratif");
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
    return modeles[indice];
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
    Moteur mot;

    if (fichier.is_open())
    {
        fichier.getline(temp, sizeof(temp)-1); // Un premier getline pour supprimer le header du fichier .csv
        
        while(fichier.getline(temp, sizeof(temp)-1)){

            champ = strtok(temp, ";");
            m.setNom(champ);
            champ = strtok(NULL, ";");
            m.setPuissance(atoi(champ));
            champ = strtok(NULL, ";");
            if(strcmp(champ, "essence") == 0)
                mot = Essence;           
            else if (strcmp(champ, "diesel") == 0)
                mot = Diesel;
            else if (strcmp(champ, "electrique") == 0)
                mot = Electrique;
            else if(strcmp(champ, "hybride") == 0)
                mot = Hybride;
                
            m.setMoteur(mot);
            champ = strtok(NULL, ";");
            m.setImage(champ);
            champ = strtok(NULL, ";");
            m.setPrixDeBase(atof(champ));
            ajouteModele(m);
            
        }
    }
    


}
void Garage :: importeOptions(string nomfichier)
{
    char temp[128];
    int i = 0;
    char *champ;
    ifstream fichier(nomfichier, ios :: in);
    Option o;

    if (fichier.is_open())
    {
        fichier.getline(temp, sizeof(temp)-1); // Un premier getline pour supprimer le header du fichier .csv
        
        while(fichier.getline(temp, sizeof(temp)-1)){

            champ = strtok(temp, ";");
            o.setCode(champ);
            champ = strtok(NULL, ";");
            o.setIntitule(champ);
            champ = strtok(NULL, ";");
            o.setPrix(atof(champ));
            ajouteOption(o);
        }
    }
    
}

Vecteur<Modele> Garage :: getModeles()
{
    return modeles;
}

Vecteur<Option> Garage :: getOptions()
{
    return options;
}
Vecteur <Employe> Garage :: getEmployes()
{
    return employes;
}