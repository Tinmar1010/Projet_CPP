#include "Exception.h"

Exception :: Exception()
{
    message = "";
}
Exception :: Exception(string m)
{
    setMessage(m);
}
Exception :: Exception(const Exception& source)
{
   setMessage(source.getMessage()); 
}
Exception :: ~Exception()
{   
    cout<<"Destructeur d'Exception"<<endl;
}

void Exception :: setMessage(string m)
{
    message = m;
}
string Exception :: getMessage()const
{
    return message;
}