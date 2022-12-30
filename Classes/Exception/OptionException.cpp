#include "OptionException.h"

OptionException :: OptionException() : Exception()
{
    cout<<"Constructeur par défaut de OptionException"<<endl;
}
OptionException :: OptionException(string message) : Exception(message)
{
    cout<<"Constructeur d'initialisation de OptionException"<<endl;
}
OptionException :: OptionException(const OptionException& source) : Exception(source)
{
    cout<<"Constructeur de copie de OptionException"<<endl;
}
OptionException :: ~OptionException()
{
    cout<<"Deconstructeur de OptionException"<<endl; 
} 