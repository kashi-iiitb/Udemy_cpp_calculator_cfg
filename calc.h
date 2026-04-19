#include "std_lib_facilities.h"

class Token{
    public:
        Token(){}
        Token(char ch): kind(ch){}
        Token(char ch, double value): kind(ch), val(value){}
        char kind;
        double val;

};

class TokenStream{
    public:
        TokenStream();
        Token get();
        void putback(Token t);
    private:
        bool full;
        Token buffer;

};