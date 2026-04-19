#include "std_lib_facilities.h"
#include "calc.h"

double expression();
double term();
double primary();

TokenStream ts;

TokenStream::TokenStream():full(false),buffer(0){}
void TokenStream::putback(Token t){
    if(full){
        error("putback() buffer full");
    }
    buffer = t;
    full = true;
}

Token TokenStream::get(){
    if(full){
        full = false;
        return buffer;
    }
    char ch;
    cin>>ch;
    switch(ch){
        case '+':
            return Token{'+'};
        case '-':
            return Token{'-'};
        case '*':
            return Token{'*'};
        case '/':
            return Token{'/'};
        case '(':
            return Token{'('};
        case ')':
            return Token{')'};
        case '0':case '1':case '2':case '3':case '4':
        case '5':case '6':case '7':case '8':case '9':
            {
                double number;
                cin.putback(ch);
                cin>>number;
                return Token{'8', number};
            }
        case ';':
            return Token{';'};
        default:
            error("Unexpected token in ts.get()");
    }
}



double expression(){
    double left = term();
    Token t = ts.get();
    while(true){
        switch(t.kind){
            case '+':
                left += term();
                t = ts.get();
                break;
            case '-':
                left -= term();
                t = ts.get();
                break;
            default:
                ts.putback(t);
                return left;
        }
    }
    return left;
}

double term(){
    double left = primary();
    Token t = ts.get();
    while(true){
        switch(t.kind){
            case '*':
                left *= primary();
                t = ts.get();
                break;
            case '/':
                left /= primary();
                t = ts.get();
                break;
            default:
                ts.putback(t);
                return left;
        }
    }
    return left;
}

double primary(){
    Token t = ts.get();
    switch(t.kind){
        case '8':
            return t.val;
        case '(':
            {
                double res = expression();
                t = ts.get();
                if(t.kind!=')')
                    error("No matching closing parentesis')'");
                return res;
            }
        default:
            error("Primary Missing");
    }
}

int main(){
    std::cout << expression();
}