#ifndef PASSWORDEXCEPTION_H
#define PASSWORDEXCEPTION_H

#include <iostream>
#include <string>
#include "Exception.h"

using namespace std;

class PasswordException : public Exception
{

    private : 
        int code;

    public : 
        PasswordException();
        PasswordException(string, const int);
        PasswordException(const PasswordException&);
        ~PasswordException();

        void setCode(int);
        int getcode()const;


        static const int INVALID_LENTH;
        static const int ALPHA_MISSING;
        static const int DIGIT_MISSING;
        static const int NO_PASSWORD;

};

#endif