#include "Employe.h"

/******************************Constructeur et destructeur***************************/
Employe :: Employe() : Intervenant()
{
    login = "";
    fonction = "Sans Fonction";
    motDePasse = NULL;
}
Employe :: Employe(string nom, string prenom, int num, string log, string fonct) : Intervenant(nom, prenom, num)
{
    setLogin(log);
    motDePasse = NULL;
    setFonction(fonct);
}
Employe :: Employe(const Employe& source) : Intervenant(source)
{
    setLogin(source.getLogin());
    motDePasse = NULL;
    setMotDePasse(source.getMotDePasse());
    setFonction(source.getFonction());
}
Employe :: ~Employe()
{
    if(motDePasse)
        delete motDePasse;

    motDePasse = NULL;
}
/********************************Getters et Setters**********************************/
void Employe :: setLogin(string log)
{
    login = log;
}
void Employe :: setMotDePasse(string mdp)
{   
    int compteuralpha, compteurnum;
    compteuralpha = 0;
    compteurnum = 0;

    if (mdp.length() < 6)
        throw(PasswordException("Mot de passe inferieur a 6 cractères", 0));
    
    for (int i = 0; i < mdp.size() && (compteuralpha == 0 || compteurnum == 0); i++)
    {
        if (isalpha(mdp[i]))
            compteuralpha = 1;
        if (isdigit(mdp[i]))
            compteurnum = 1;
    }

    if (compteurnum == 0)
        throw(PasswordException("Mot de passe ne contenant pas de chiffre", 1));
    
    if (compteuralpha == 0)
        throw(PasswordException("Mot de passe ne contenant pas de lettre", 2));

    cout<<"Je passe"<<endl;
    motDePasse = new string;
    *motDePasse = mdp;
    cout<<"Je passe"<<endl;
    
}
void Employe :: ResetMotDePasse()
{
    if(motDePasse!= NULL)
        delete[] motDePasse;
    
    motDePasse = NULL;

}  
void Employe :: setFonction(string fonct)
{
    fonction = fonct;
}
string Employe :: getLogin()const
{
    return login;
}
string Employe :: getMotDePasse()const
{
    if(!motDePasse)
        throw PasswordException("Pas de mot de passe", 3);
    else
        return *motDePasse;
}
string Employe :: getFonction()const
{
    return fonction;
}
string Employe :: ADMINISTRATIF = "Administratif";
string Employe :: VENDEUR = "Vendeur";
/********************************Surchage Opérateur**********************************/
Employe& Employe :: operator=(const Employe &e)
{
    Intervenant :: operator=(e);

    login = e.login;
    fonction = e.fonction;

    return (*this);
}
ostream& operator<<(ostream& out, const Employe& e)
{
    out<<"Nom : "<<e.nom<<endl<<"Prenom : "<<e.prenom<<endl<<"Numéro d'Intervenant : "<<e.numIntervenant<<endl<<"Login : "<<e.login<<endl<<"Fonction : "<<e.fonction<<endl;

    return out;
}
istream& operator>>(istream& in, Employe& e)
{
    string nom, prenom, fonct, mdp, login;
    int numI;

    cout<<"Nom : ";
    in>>nom;
    cout<<"Prenom : ";
    in>>prenom;
    cout<<"Numéro d'intervenant";
    in>>numI;
    cout<<"Login : ";
    in>>login;
    cout<<"Fonction : ";
    in>>fonct;

    e.setNom(nom);
    e.setPrenom(prenom);
    e.setNumero(numI);
    e.setFonction(fonct);
    e.setLogin(login);

    return in;
}
/********************************Méthode Virtuelle**********************************/
string Employe :: ToString()
{
    string chaine;

    if(fonction == "Administratif")
        chaine = "A[" + to_string(getNumero()) + ']' + getNom() + ' ' + getPrenom();
    if(fonction == "Vendeur")
        chaine = "V[" + to_string(getNumero()) + ']' + getNom() + ' ' + getPrenom();

    return chaine;
}
string Employe :: Tuple()
{   
    string chaine;

    chaine = to_string(getNumero()) + ';' + getNom() + ';' + getPrenom() + ';' + getFonction();

    return chaine; 
}
