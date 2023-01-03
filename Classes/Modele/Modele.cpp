#include "Modele.h"


/******************************Constructeur et destructeur***************************/

Modele::Modele()
{
    #ifdef DEBUG
    #endif 

    puissance = 0;
    prix = 0;
    moteur = Essence;

    nom = new char [50];
    image = "";
}

Modele:: Modele(const char *n, int p, Moteur m, float pr, string jpg)
{
    #ifdef DEBUG
    #endif 

    nom = NULL;
    setNom(n);
    setPuissance(p);
    setMoteur(m);
    setPrixDeBase(pr);
    setImage(jpg);
}

Modele::Modele(const Modele &source)
{
    #ifdef DEBUG
    #endif 

    nom = NULL;
    setNom(source.getNom());
    setPuissance(source.getPuissance());
    setMoteur(source.getMoteur());
    setPrixDeBase(source.getPrixDeBase());
    setImage(source.getImage());
}

Modele::~Modele()
{
    #ifdef DEBUG
    #endif
    if(nom)
        delete[]nom;
}

/******************************Getter et Setter***************************/

const char * Modele::getNom()const
{
    return nom;
}
int Modele::getPuissance()const
{
    return puissance;
}

Moteur Modele:: getMoteur()const
{
    return moteur;
}

float Modele::getPrixDeBase()const
{
    return prix;
}
string Modele :: getImage()const
{
    return image;
}
void Modele::setNom(const char *n)
{
    if(nom!=NULL)
        delete[] nom;
    nom = new char [strlen(n)+1];
    strcpy(nom, n);
}

void Modele::setPuissance(int p)
{
    if(p>=0)
        puissance = p;
}

void Modele::setMoteur(Moteur m)
{
    moteur = m;
}

void Modele::setPrixDeBase(float pr)
{
    prix = pr;
}
void Modele :: setImage(string jpg)
{
    image = jpg;
}
/********************************Surchage Opérateur**********************************/
Modele& Modele :: operator=(const Modele& m)
{
    setNom(m.getNom());
    setPrixDeBase(m.getPrixDeBase());
    setPuissance(m.getPuissance());
    setMoteur(m.getMoteur());
    setImage(m.getImage());

    return (*this);
}
ostream& operator<<(ostream& out, const Modele& m)
{
    out<<"Nom : "<<m.getNom()<<endl<<"Puissance : "<<m.getPuissance()<<endl<<"Prix : "<<m.getPrixDeBase()<<endl;

    switch (m.getMoteur())
    {
    case 0 :
        out<<"Moteur : Essence";
        break;
    case 1 :
        out<<"Moteur : Diesel";
        break;
    case 2 :
        out<<"Moteur : Electrique";
        break;
    case 3 :
        out<<"Moteur : Hybride";
        break;
    
    }
    
    return out;
}
istream& operator>>(istream& in, Modele& m)
{
    char *n;
    int puis, mo;
    float pr;
    Moteur mot;

    n = new char [30];
    cout<<"Nom : ";
    in>>n;
    cout<<"Puissance : ";
    in>>puis;
    cout<<"Prix : ";
    in>>pr;
    cout<<"Moteur"<<endl<<"0->Essence"<<endl<<"1->Diesel"<<endl<<"2->Electrique"<<endl<<"3->Hybride"<<endl;
    cout<<"Moteur : "<<endl;
    in>>mo;

    switch(mo)
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

    strcpy(m.nom, n);
    m.puissance = puis;
    m.prix = pr;
    m.moteur = mot;
    return in;
} 

/*********************************Méthode publique***********************************/

void Modele::Affiche()const
{
    cout<<"Nom : "<<nom<<endl;
    cout<<"Puissance : "<<puissance<<endl;
    cout<<"Prix : "<<prix<<endl;
    cout<<"Moteur : ";
    switch (moteur)
    {
    case 0 : 
        cout<<"Essence"<<endl;
        break;
    
    case 1 : 
        cout<<"Diesel"<<endl;
        break;
    
    case 2 : 
        cout<<"Electrique"<<endl;
        break;

    case 3 : 
        cout<<"Hybride"<<endl;
        break;
    
    } 
}
void Modele :: Save(ofstream &fichier)const
{
    if(!fichier)
    {
        cout<<"Erreur d'ouverture !"<<endl;
        exit(1);
    }

    int tailleimage = image.size();
    int taille = strlen(nom);
    fichier.write((char*)&taille, sizeof(int));

    fichier.write((char*)&puissance, sizeof(int));
    fichier.write((char*)&prix, sizeof(float));
    fichier.write((char*)&moteur, sizeof(Moteur));
    fichier.write((char*)nom, taille*sizeof(char));
    fichier.write((char*)&tailleimage, sizeof(int));
    fichier.write((char*)image.data(), tailleimage*sizeof(char));


}
void Modele :: Load(ifstream &fichier)
{
    if(!fichier)
    {
        cout<<"Erreur d'ouverture !"<<endl;
        exit(1);
    }
    int tailleimage;
    int taille = 0;
    fichier.read((char*)&taille, sizeof(int));
    nom = new char[taille + 1];

    fichier.read((char*)&puissance, sizeof(int));
    fichier.read((char*)&prix, sizeof(float));
    fichier.read((char*)&moteur, sizeof(Moteur));
    fichier.read((char*)nom, taille*sizeof(char));
    nom[taille] = 0;
    fichier.read((char*)&tailleimage, sizeof(int));
    image.resize(tailleimage);
    fichier.read((char*)image.data(), tailleimage*sizeof(char));

}