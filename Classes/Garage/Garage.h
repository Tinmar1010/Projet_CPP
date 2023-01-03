#ifndef GARAGE_H
#define GARAGE_H

#include<iostream>
#include<string.h>
#include <string>

#include "Modele.h"
#include "Option.h"
#include "Voiture.h"
#include "Personne.h"
#include "Intervenant.h"
#include "Employe.h"
#include "Client.h"
#include "Vecteur.h"
#include "Iterateur.h"



using namespace std;


class Garage
{
    private:
        Vecteur<Employe> employes;
        Vecteur<Client> clients;
        Vecteur<Modele> modeles;
        Vecteur<Option> options;

        static Garage instance;

        Garage();
        Garage(const Garage & g);

        Garage& operator=(const Garage& g);//Empeche d'avoir plusieurs instance de la classe garage


        ~Garage();

        static Voiture ProjetEnCours;

    public:
        
        static Garage& getInstance();
        static Voiture& getProjetEnCours();

        static void resetProjetEnCours();

        void ajouteModele(const Modele &);
        void afficheModelesDisponibles()const;
        Modele getModele(int);

        void ajouteOption(const Option &);
        void afficheOptionsDisponibles()const;
        Option getOption(int);

        void ajouteClient(string, string, string);
        void afficheClients()const;
        void supprimeClientParIndice(int);
        void supprimeClientParNumero(int);
        
        void ajouteEmploye(string, string, string, string);
        void afficheEmployes()const;
        void supprimeEmployeParIndice(int);
        void supprimeEmployeParNumero(int);

        void importeModeles(string);
        void importeOptions(string);

        Vecteur <Modele> getModeles();
        Vecteur <Option> getOptions();
        Vecteur <Employe> getEmployes();

        static Employe* pE;
};

#endif