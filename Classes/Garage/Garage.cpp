#include "Garage.h"

Garage Garage :: instance = Garage();
Voiture Garage :: ProjetEnCours = Voiture();

Employe* Garage::pE = NULL;

Garage :: Garage()
{   
    modeles = Vecteur <Modele>(50);
    options = Vecteur <Option>(50);
    employes = Vecteur <Employe>(50);
    clients = Vecteur <Client>(50);
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
    if(ind < clients.size()&&Client :: numCourant>0)
    {
        clients.retire(ind);
        Client :: numCourant = (Client :: numCourant - 1);
    }
}
void Garage :: supprimeClientParNumero(int num)
{
    int i = 0;

    while(i<clients.size()&&clients[i].getNumero() != num)
        i++;

    if(i < clients.size() && clients[i].getNumero() == num)
    {
        clients.retire(i);
        if(Client :: numCourant>0)
            Client :: numCourant = (Client :: numCourant - 1);
    }
}    
void Garage :: ajouteContrat(int num, Employe* e, Client* c, string nom)
{
    Contrat cont;

                
    cont.setNomprojet(nom);
    cont.setNumero(num);
    cont.setClient(c);
    cont.setVendeur(e);
    
    contrats.insere(cont);
    Contrat :: numContrat = Contrat :: numContrat + 1;
}
void Garage::afficheContrats()const
{
    
}
void Garage :: supprimeContratParIndice(int num)
{
    if(num < contrats.size()&&Contrat::numContrat>=0)
    {
        contrats.retire(num);
        Contrat :: numContrat = (Contrat::numContrat -1);
    }
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
    if (ind < employes.size())
    {
        if(Employe :: numCourant>0){
            employes.retire(ind);
            Employe :: numCourant = (Employe :: numCourant - 1);
        }
    }
}
void Garage :: supprimeEmployeParNumero(int num)
{
    int i = 0;

    while(i<employes.size()&&employes[i].getNumero() != num)
        i++;

    if (i < employes.size() && employes[i].getNumero() == num)
    {
        employes.retire(i);
        if(Employe :: numCourant>0)
            Employe :: numCourant = (Employe :: numCourant - 1);
    }
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

// TODO : retourner references comme pour employe

Vecteur<Option> Garage :: getOptions()
{
    return options;
}
Vecteur <Employe> &Garage :: getEmployes()
{
    return employes;
}
Vecteur <Client> &Garage :: getClients()
{
    return clients;
}

Vecteur <Contrat> &Garage::getContrat()
{
    return contrats;
}
void Garage ::Save(ofstream &fichier)
{
    int i;
    int tmp;
    int temp_contrat;

    if (!fichier)
    {
        cout<<"Erreur d'ouverture !"<<endl;
        exit(1);
    }
    else
    {
        tmp = employes.size();
        cout<<"Temp d'employé : "<<tmp<<endl;
        fichier.write((char*)&Intervenant::numCourant, sizeof(Intervenant::numCourant)); // Enregistrement de numcourant 1 fois
        fichier.write((char*)&tmp, sizeof(int)); // Enregistement du nombres d'employe
        
        i = 0;
        // Pour chaque employe on le save
        while (tmp>0 && i< employes.size()){
            employes[i++].Save(fichier);
        }

        
        tmp = clients.size();
        cout<<"Temp client : "<<tmp<<endl;
        fichier.write((char*)&tmp, sizeof(int)); // Enregistement du nombre de client
        i = 0;
        
        // Pour chaque client on le save
        while (tmp>0 &&i < clients.size()){
            clients[i++].Save(fichier);
        }
        
        tmp = contrats.size();
        fichier.write((char*)&Contrat::numContrat, sizeof(Contrat::numContrat));
        fichier.write((char*)&tmp, sizeof(tmp));

        i = 0;
        
        while (tmp >0 && i < contrats.size()) {
            temp_contrat = contrats[i].getVendeur()->getNumero();
            fichier.write((char*)&temp_contrat, sizeof(temp_contrat)); // Enregistrement du num unique vendeur 
            temp_contrat = contrats[i].getClient()->getNumero();
            fichier.write((char*)&temp_contrat, sizeof(temp_contrat)); // Enregistrement du num unique client
            contrats[i++].Save(fichier);
        }

    }


}
void Garage ::Load(ifstream & fichier)
{
    int i = 0;
    int tmp;

    Employe tmp_e;
    Client tmp_c;

    fichier.read((char*)&Intervenant::numCourant, sizeof(Intervenant::numCourant));
    fichier.read((char*)&tmp, sizeof(tmp)); // Nombre d'employe

    i = 0;

    while (i < tmp)
    {
        tmp_e.Load(fichier);
        employes.insere(tmp_e);
        i++;
    }

    fichier.read((char*)&tmp, sizeof(tmp)); // Nombre de client

    i = 0;

    while (i < tmp)
    {
        tmp_c.Load(fichier);
        clients.insere(tmp_c);
        i++;
    }

    fichier.read((char*)&tmp, sizeof(int)); // NumCourant de contrat
    Contrat::numContrat = tmp;
    fichier.read((char*)&tmp, sizeof(tmp)); // Nombre de contrats
    
    i = 0;
    int j = 0;
    int num_vendeur;
    int num_client;

    Employe *addr_vendeur;
    Client *addr_client;

    while (i < tmp) // Boucle pour chaque contrat
    {   
        fichier.read((char*)&num_vendeur, sizeof(num_vendeur));
        addr_vendeur = RechercheEmploye(num_vendeur);
        if(addr_vendeur == NULL) 
            i = tmp;
        else
        {
            fichier.read((char*)&num_client, sizeof(num_client));
            addr_client = RechercheClient(num_client);
            if (addr_client == NULL)
                i = tmp;
            else
            {
                
                Contrat tmp_cont(0, addr_vendeur, addr_client, "");
                tmp_cont.Load(fichier);
                contrats.insere(tmp_cont);
                i++;
            }
        }
    }      
}
Employe * Garage :: RechercheEmploye(int num)
{
    int i = 0;
    Iterateur <Employe> it(employes);
    it.reset();
    Employe *pe = NULL;

    while(!it.end())
    {
        if(employes[i].getNumero() == num)
        {
            pe = &employes[i];
            return pe;
        }
            
        else
            i++;
    }

    return pe;
}
Client* Garage::RechercheClient(int num)
{
    int i;
    Iterateur<Client> it(clients);
    it.reset();
    
    i = 0;
    while (!it.end() && clients[i].getNumero() != num)
       i++;
    
    if (clients[i].getNumero() == num)
        return &clients[i];
    
    return NULL;
}