#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*
struct non_Terminal{
    string name;
    int numero;
};
*/
//token definition
struct token{
    string name;
    string accion;
    void printToken(){
        cout << '<' << name << ">,<" << accion << '>' << endl;
    }
};
//global variables
string cadena;
vector<token*> lista_tokens;
bool isCadenaOver = false;

//general functions
char nextChar(const int step = 1){
    static int index = 0;
    if (index == cadena.length()) isCadenaOver = true;
    else{
        if (step ==1) return cadena[++index];
        else if (step == -1) return cadena[--index]; 
    }
}

void add_listatokens(token *Token){
    lista_tokens.push_back(Token);
}

void checkDigit(const int upper_bound,const int lower_bound,const string action, char character, token *&Token, string &cadena_acumulada){
    if (isdigit(character)){
            cadena_acumulada+=character;
            Token->name = cadena_acumulada;
            if (int(character)<upper_bound && int(character)>lower_bound) {
                Token->accion = action; 
            }
            else {
                Token->accion = "Error";
            }
    }
    else{
        if(!(character == 'A' or character == 'C' or character == 'S' or character == 'N')){
            cadena_acumulada+= character;
        }
        Token->name = cadena_acumulada;
        Token->accion = "Error";
    }
    add_listatokens(Token);
    cadena_acumulada = " ";
}

void caseA(string &cadena_acumulada){
    cadena_acumulada+= 'A';
    auto next_char = nextChar();
    token *token;
    switch(next_char){
    case 'c':
        cadena_acumulada += next_char;
        next_char = nextChar();
        checkDigit(5,0,"Acabado",next_char,token,cadena_acumulada);
        break;
    default:
        token->name = cadena_acumulada;
        token->accion = "Almacen";
        add_listatokens(token);
        cadena_acumulada = " ";
        break;
    }
}

void caseS(string &cadena_acumulada){
    cadena_acumulada+='S';
    char next_char = nextChar();
    switch(next_char){
    token *Token;
    case 'h':
        cadena_acumulada+=next_char;
        next_char = nextChar();
        checkDigit(6,0,"Tejido Horizontal",next_char,Token,cadena_acumulada);
    case 'v': 
        cadena_acumulada+=next_char;
        next_char = nextChar();
        checkDigit(6,0,"Tejido Vertical",next_char,Token,cadena_acumulada);
    default:
        char next_char2 = nextChar();
        while(!(next_char2 == 'A' or next_char2 == 'C' or next_char2 == 'S' or next_char2 == 'N')) 
            cadena_acumulada+= next_char2;
        token* NoAceptado;
        NoAceptado->name = cadena_acumulada;
        NoAceptado->accion = "Error";
        add_listatokens(NoAceptado);
        cadena_acumulada = " ";
        nextChar(-1);
    }
}


void caseN(string &cadena_acumulada){
    cadena_acumulada+= 'N';
    auto next_char = nextChar();
    token *token;
    checkDigit(6,0,"Tenhido",next_char,token,cadena_acumulada);
}

void caseC(string &cadena_acumulada){
    cadena_acumulada+= 'C';
    auto next_char = nextChar();
    token *token;
    checkDigit(5,0,"Confeccion",next_char,token,cadena_acumulada);
}

void lexer(){
    string cadena_acumulada = " ";
    while(isCadenaOver == false){
        char next_char = nextChar();
        switch(next_char){
        case 'A':
            caseA(cadena_acumulada);
        case 'S':
            caseS(cadena_acumulada);
        case 'N':
            caseN(cadena_acumulada);
        case 'C':
            caseC(cadena_acumulada);
        default:
            auto next_char = nextChar();
            while(!(next_char == 'A' or next_char == 'C' or next_char == 'S' or next_char == 'N'))
                cadena_acumulada+= next_char;
            token *NoAceptado ;
            NoAceptado->name = cadena_acumulada;
            NoAceptado->accion = "Error";
            add_listatokens(NoAceptado);
            cadena_acumulada = " ";
            nextChar(-1);
        }
    }
}

/*
bool Is_NonTerminal_with_Number(non_Terminal elemento){
    
    if(elemento.name !=  'Ac' || elemento.name !== 'C' ){
        if(elemento.numero is in (1,2,3,4,5))
            return true;
        else
            return false;
    }
    else{
        if(elemento.numero is in (1,2,3,4))
        else
            return false;

    }

}
*/