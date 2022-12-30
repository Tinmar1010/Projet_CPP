#ifndef OPTIONEXCEPTION_H
#define OPTIONEXCEPTION_H

#include <iostream>
#include <string>
#include "Exception.h"

using namespace std;

class OptionException : public Exception
{

    public : 
        OptionException();
        OptionException(string);
        OptionException(const OptionException&);
        ~OptionException();


};

#endif