#include "Client.h"


/******************************Constructeur et destructeur***************************/
Client :: Client() : Intervenant()
{
    gsm = "";
}
Client :: Client(string nom, string prenom, int num, string numgsm) : Intervenant(nom, prenom, num)
{
    gsm = numgsm;
}   
Client :: Client(const Client& source) : Intervenant(source)
{
    setGsm(source.getGsm());
}
Client :: ~Client() 
{
    //cout<<"Destructeur de Client"<<endl;
}
/********************************Getters et Setters**********************************/
void Client :: setGsm(string numgsm)
{
    gsm = numgsm;
}
string Client :: getGsm()const
{
    return gsm;
}
/********************************Surchage Opérateur**********************************/
Client& Client :: operator=(const Client& c)
{
    Intervenant :: operator=(c);
    gsm = c.gsm;

    return (*this);
}
ostream& operator<<(ostream& out, const Client& c)
{
    out<<"Nom : "<<c.nom<<endl<<"Prenom : "<<c.prenom<<endl<<"Numéro d'Intervenant : "<<c.numIntervenant<<endl<<"Numero de GSM : "<<c.gsm<<endl;

    return out;
}
istream& operator>>(istream& in, Client& c)
{
    string num, nom, prenom;
    int numI;
    //getline (in, var) 
    cout<<"Nom : ";
    in>>nom;
    cout<<"Prenom : ";
    in>>prenom;
    cout<<"Numéro d'intervenant";
    in>>numI;
    cout<<"Numero de GSM : ";
    in>>num;

    c.nom = nom;
    c.prenom = prenom;
    c.numIntervenant = numI;
    c.gsm = num;

    return in;
}

/********************************Méthode Virtuelle**********************************/
string Client :: ToString()
{
    string chaine;
    
    chaine = "C[" + to_string(getNumero()) + "] " + getNom() + ' ' + getPrenom();
    return chaine; 
}
string Client :: Tuple()
{
    string chaine;

    chaine = to_string(getNumero()) + ';' + getNom() + ';' + getPrenom() + ';' + getGsm();
    return chaine;
}