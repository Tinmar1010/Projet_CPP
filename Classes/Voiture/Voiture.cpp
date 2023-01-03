#include "Voiture.h"



/******************************Constructeur et destructeur***************************/

Voiture::Voiture()
{
    #ifdef DEBUG
    #endif 

    nom = "VoitureSansNom";

}
Voiture :: Voiture(string n, Modele m)
{
    #ifdef DEBUG
    #endif 

    setNom(n);
    setModele(m);
}
Voiture :: Voiture(const Voiture &source)
{
    #ifdef DEBUG
    #endif 

    
    setNom(source.getNom());
    setModele(source.getModele());

    for (unsigned int i = 0; i < (sizeof(options)/sizeof(options[0])); i++)
    {
        if (source.options[i] != NULL)
            AjouteOption(*source.options[i]);
    }
}
Voiture::~Voiture()
{
    #ifdef DEBUG
    #endif

    for (unsigned long i = 0; i < (sizeof(options)/sizeof(options[0])); i++)
        if (options[i] != NULL)
            delete options[i];
}
/********************************Getters et Setters**********************************/
string Voiture :: getNom()const
{
    return nom;
}

Modele Voiture :: getModele()const
{
    return modele;
}

void Voiture :: setNom(string n)
{
    nom = n;
}

void Voiture :: setModele(Modele m)
{
    modele.setPuissance(m.getPuissance());
    modele.setPrixDeBase(m.getPrixDeBase());
    modele.setMoteur(m.getMoteur());
    modele.setNom(m.getNom());
    modele.setImage(m.getImage());
}
/********************************Surchage Opérateur**********************************/
Voiture& Voiture :: operator=(const Voiture& v)
{
    int i = 0;

    nom = v.getNom();
    modele = v.modele;
    while(i<sizeof(options)/sizeof(options[0]))
    {
        if(v.options[i]!=NULL)
        {
            if(options[i]!=NULL)
                delete options[i];

            options[i] = new Option (*v.options[i]);
        }
        else
        {
            if(options[i]!=NULL)
            {
                delete options[i];
                options[i] = NULL;
            }
                
        }
        i++;
    }
    return (*this);
}
Voiture Voiture :: operator+(const Option&o)
{
    Voiture v(*this);
    v.AjouteOption(o);
    return v;
}
Voiture operator+(const Option& o,Voiture vo)
{
    return vo + o;
}
Voiture Voiture :: operator-(const Option&o)
{
    Voiture v(*this);
    v.RetireOption(o.getCode());
    return v;
}
Voiture Voiture :: operator-(const string& code)
{
    Voiture v(*this);
    v.RetireOption(code);
    return v;
}
int Voiture :: compV(const Voiture& v)const
{
    int i = 0;

    if(getPrix()<v.getPrix())
        return -1;
    if(getPrix()>v.getPrix())
        return 1;
    
    return 0;
}
int Voiture :: operator<(const Voiture& v)
{
    return compV(v) ==-1;
}
int Voiture :: operator>(const Voiture& v)
{   
    return compV(v) == 1;
}
int Voiture :: operator==(const Voiture& v)
{
    return compV(v) == 0;
}
ostream& operator<<(ostream& out, const Voiture& v)
{
    out<<"Nom : "<<v.getNom()<<endl<<"Modele : "<<endl<<v.getModele()<<endl;   
    for (unsigned long i = 0; i < 5; i++)
        if (v.options[i] != NULL)
            v.options[i]->Affiche();
    return out;
}
Option* Voiture :: operator[](int i)
{
    switch(i)
    {
        case 0 : return options[0];
        case 1 : return options[1];
        case 2 : return options[2];
        case 3 : return options[3];
        case 4 : return options[4];
        default : return options[0];
    }
}
/********************************Méthodes Publiques**********************************/
void Voiture::Affiche()
{
    int nb_options = 0;

    cout << "Nom de voiture :" << nom << endl;
    modele.Affiche();

    for (int i = 0;i < (sizeof(options)/sizeof(options[0])); i++)
    {
        if(options[i] != NULL)
            nb_options++;
    }

    cout << "Nombre total d'options : " << nb_options << endl;

    for (unsigned long i = 0; i < 5; i++)
        if (options[i] != NULL)
            options[i]->Affiche();
}


void Voiture::AjouteOption(const Option & opt)
{
    unsigned long i = 0;

    while (i < (sizeof(options)/sizeof(options[0])) && options[i] != NULL)
    {
        if (opt.getCode() == options[i]->getCode())
            throw(OptionException("L'option existe déja !"));
        i++;
    }
    if (i == (sizeof(options)/sizeof(options[0])))
        throw(OptionException("Impossible d'ajouter plus de 5 options !"));

    if (i < (sizeof(options)/sizeof(options[0])) && options[i] == NULL){
        options[i] = new Option(opt);
    }
}

void Voiture::RetireOption(string code)
{
    unsigned long i = 0;
    while (i < (sizeof(options)/sizeof(options[0])) && options[i] != NULL && options[i]->getCode() != code)
        i++;

    if (i < (sizeof(options)/sizeof(options[0])) && options[i] != NULL && options[i]->getCode() == code)
    {
        delete options[i];
        options[i] = NULL;
    }
    else
        throw(OptionException("L'option n'existe pas !"));
}

float Voiture::getPrix()const
{
    float prix_total = modele.getPrixDeBase();
    
    for (unsigned long i = 0; i < (sizeof(options)/sizeof(options[0])); i++)
    {
        if (options[i] != NULL)
            prix_total += options[i]->getPrix();
    }

    return prix_total;
}
void Voiture :: Save()
{
    string nf = nom + ".car";
    ofstream fichier(nf, ios :: out);
    int tailleOption = 0;

    int taille1 = nf.size();
    fichier.write((char*)&taille1, sizeof(int));
    fichier.write((char*)nf.data(), taille1*sizeof(char));
    modele.Save(fichier);

    for (int i = 0; i < (sizeof(options)/sizeof(options[0])); i++)
    {
        if (options[i] != NULL)
            tailleOption ++;
    }

    fichier.write((char*)&tailleOption, sizeof(int));

    for (int i = 0; i < (sizeof(options)/sizeof(options[0])); i++)
    {
        if (options[i] != NULL)
        {
            cout<<"J'ecris l'options "<<i<<endl;
            options[i]->Save(fichier);

        }
    }

    fichier.close();  
}
void Voiture :: Load(string nomfichier)
{
    ifstream fichier(nomfichier, ios :: in);

    int taille1, tailleOption;


    fichier.read((char*)&taille1, sizeof(int));
    nom.resize(taille1);
    fichier.read((char*)nom.data(), taille1*sizeof(char));

    
    modele.Load(fichier);

    fichier.read((char*)&tailleOption, sizeof(int));
    for (int i = 0; i < (sizeof(options)/sizeof(options[0])); i++)
    {
        if (options[i] != NULL)
            delete options[i];
    }

    for (int i = 0; i < tailleOption; i++)
    {
        options[i] =new Option();
        options[i]->Load(fichier);
    }

    fichier.close();
}