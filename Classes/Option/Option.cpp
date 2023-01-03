#include "Option.h"

/******************************Constructeur et destructeur***************************/
Option :: Option()
{
    #ifdef DEBUG
    #endif  
    prix = 0;
    code = "";
    intitule = "";

}
Option :: Option(string c, string inti, float p)
{
    #ifdef DEBUG
    #endif 

    setCode(c);
    setIntitule(inti);
    setPrix(p);
}
Option :: Option(const Option &source)
{
    #ifdef DEBUG
    #endif 

    setCode(source.getCode());
    setIntitule(source.getIntitule());
    setPrix(source.getPrix());
}

Option :: ~Option()
{
    #ifdef DEBUG
    #endif
}
/********************************Getters et Setters**********************************/
string Option :: getCode()const
{
    return code;
}
string Option ::getIntitule()const
{
    return intitule;
}
float Option :: getPrix()const
{
    return prix;
}
void Option ::setCode(string c)
{
    if (c == "")
        throw(OptionException("Code vide !"));
    
    if (c.length() > 4)
        throw(OptionException("Code fait plus de 4 carcatères !"));
    code = c;
}
void Option :: setIntitule(string inti)
{
    if (inti == "")
        throw(OptionException("L'intitule est vide !"));
    else
        intitule = inti;
}
void Option :: setPrix(float p)
{
    if (p >= 0)
        prix = p;
    else
        throw(OptionException("Le prix doit être positif !"));
}

Option& Option :: operator=(const Option & o)
{
    code = o.code;
    intitule = o.intitule;
    prix = o.prix;

    return (*this);
}
Option Option :: operator-(int val)
{
    Option opt(*this);

    opt.prix = opt.prix - val;

    return opt;
}
ostream& operator<<(ostream& out, const Option& o)
{   
    out <<"Code : "<<o.getCode()<<endl<<"Intitule : "<<o.getIntitule()<<endl<<"Prix : "<<o.getPrix()<< endl;
    return out;
}
istream& operator>>(istream& in, Option& o)
{
    string c, inti;
    float pr;

    cout<<"Code : ";
    in>>c;
    cout<<"Intitule : ";
    in>>inti;
    cout<<"Prix : ";
    in>>pr;

    o.code = c;
    o.intitule = inti;
    o.prix = pr;

    return in;
}
Option Option :: operator--(int)
{
    Option temp(*this);

   if(prix<50)
        throw OptionException("Le prix de l'option ne peut pas être négatif !");
    else
        prix = prix -50;

    return temp;
}
Option Option :: operator--()
{
    if(prix<50)
        throw OptionException("Le prix de l'option ne peut pas être négatif");
    else
        prix = prix -50;

    return (*this);
}

/********************************Méthodes Publiques**********************************/
void Option :: Affiche()const
{
    cout<<"Code : "<<code<<endl;
    cout<<"Intitule : "<<intitule<<endl;
    cout<<"Prix : "<<prix<<endl;

}
void Option :: Save(ofstream &fichier)const
{
    if(!fichier)
    {
        cout<<"Erreur d'ouverture !"<<endl;
        exit(1);
    }

    int taille1 = code.size();
    fichier.write((char*)&taille1, sizeof(int));
    fichier.write((char*)code.data(), taille1*sizeof(char));

    int taille2 = intitule.size();
    fichier.write((char*)&taille2, sizeof(int));
    fichier.write((char*)intitule.data(), taille2*sizeof(char));

    fichier.write((char*)&prix, sizeof(float));


}
void Option :: Load(ifstream &fichier)
{
    if(!fichier)
    {
        cout<<"Erreur d'ouverture !"<<endl;
        exit(1);
    }
    int taille1, taille2;

    fichier.read((char*)&taille1, sizeof(int));
    code.resize(taille1);
    fichier.read((char*)code.data(), taille1*sizeof(char));

    fichier.read((char*)&taille2, sizeof(int));
    intitule.resize(taille2);
    fichier.read((char*)intitule.data(), taille2*sizeof(char));

    fichier.read((char*)&prix, sizeof(float));

}