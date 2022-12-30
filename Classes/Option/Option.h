#ifndef OPTION_H
#define OPTION_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Option
{
    friend ostream& operator<<(ostream& out, const Option& o);
    friend istream& operator>>(istream& in, Option& o);
    
    private : 

        string code;
        string intitule;
        float prix;
        

    public : 

        Option();
        Option(string, string, float);
        Option(const Option &);
        ~Option();

        string getCode()const;
        string getIntitule()const;
        float getPrix()const;

        void setCode(string);
        void setIntitule(string);
        void setPrix(float);

        Option& operator=(const Option&);
        Option operator-(int);
        Option operator--();
        Option operator--(int);

        void Affiche()const;
        void Save(ofstream &)const;//Ecrire sur le flux de fichier en paramètre
        void Load(ifstream &);//Lire sur le flux de fichier en paramètre
};

#endif