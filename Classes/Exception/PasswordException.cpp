#include "PasswordException.h"

const int PasswordException :: INVALID_LENTH = 0;
const int PasswordException :: ALPHA_MISSING = 1;
const int PasswordException :: DIGIT_MISSING = 2;
const int PasswordException :: NO_PASSWORD = 3;

PasswordException :: PasswordException() : Exception()
{
    cout<<"Constructeur par défaut de PasswordException"<<endl;
}
PasswordException :: PasswordException(string message, const int code) : Exception(message)
{
    cout<<"Constructeur d'initialisation de PasswordException"<<endl;
    setCode(code);
}
PasswordException :: PasswordException(const PasswordException& source) : Exception(source)
{
    cout<<"Constructeur de copie de PasswordException"<<endl;
    
    setCode(source.getcode());
}
PasswordException :: ~PasswordException()
{
    cout<<"Deconstructeur de PasswordException"<<endl; 
} 

void PasswordException :: setCode(const int c)
{
    code = c;
}
int PasswordException :: getcode()const
{
    return code;
}