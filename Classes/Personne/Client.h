#ifndef CLIENT_H
#define CLIENT_H

#include<iostream>
#include <string>
#include "Intervenant.h"

using namespace std;
class Client : public Intervenant
{
    
    friend ostream& operator<<(ostream& out, const Client& c);
    friend istream& operator>>(istream& in, Client& c);

    protected : 

        string gsm;
    
    public : 

        Client();
        Client(string, string, int, string);
        Client(const Client&);
        ~Client();

        
        void setGsm(string);
        string getGsm()const;

        string ToString();
        string Tuple();

        Client& operator=(const Client &);

        void Save(ofstream &);
        void Load(ifstream &);

};  

#endif