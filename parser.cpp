#include "lexer.h"

vector<token*> get_lista_tokens(){
    return lista_tokens;
}

bool next_nonTerminal = true;

auto lista_token = get_lista_tokens();

auto token_inicial = lista_tokens[0];

bool isTokensOver = false;

bool EstadoAceptacion = true;

typedef vector<string> lista;

token* next_Token(const int step = 1){
    static int index = 0;
    if (index == lista_token.size()) isTokensOver = true;
    else{
        if (step ==1) return lista_tokens[++index];
        else if (step == -1) return lista_tokens[--index]; 
    }
}

bool is_Correct_Next(vector<string> lista_tokens_siguientes,string current_token){
    for(auto i = 0 ; i < lista_tokens_siguientes.size() ; i++){
        if(current_token == lista_tokens_siguientes[i]){
            return true;
        }
    }
    return false;
}

lista Rule_A(){
    lista siguientes = {"Sh1","Sh2","Sh3","Sh4","Sh5"};
    return siguientes;
}

lista Rule_Sh1_Sh3(){
    lista siguientes = {"Sv1","Sv2","Sv3"};
    return siguientes;
}

lista Rule_Sh2(){
    lista siguientes = {"Sv1","Sv2"};
    return siguientes;
}

lista Rule_Sh4(){
    lista siguientes = {"Sv3","Sv4","Sv5"};
    return siguientes;
}

lista Rule_Sh5(){
    lista siguientes = {"Sv3","Sv5"};
    return siguientes;
}

lista Rule_Sv1_Sv2(){
    lista siguientes = {"N1","N2","N3"};
    return siguientes;
}

lista Rule_Sv3_Sv4(){
    lista siguientes = {"N4","N5"};
    return siguientes;
}

lista Rule_Sv5(){
    lista siguientes = {"N5"};
    return siguientes;
}

lista Rule_N1(){
    lista siguientes = {"Ac1","Ac2"};
    return siguientes;
}

lista Rule_N2(){
    lista siguientes = {"Ac1","Ac2","Ac3"};
    return siguientes;
}

lista Rule_N3_N4(){
    lista siguientes = {"Ac2","Ac3","Ac4"};
    return siguientes;
}

lista Rule_N5(){
    lista siguientes = {"Ac4"};
    return siguientes;
}

lista Rule_Ac1_Ac2_Ac3(){
    lista siguientes = {"C1","C2","C3"};
    return siguientes;
}

lista Rule_Ac4(){
    lista siguientes = {"C4"};
    return siguientes;
}

lista Rule_C1(){
    lista siguiente = {"C2"};
    return siguiente;
}

lista RuleC2(){
    lista siguiente = {"C4"};
    return siguiente;
}

lista RuleC3_C4(){
    lista siguiente = {"A"};
    return siguiente;
}


void parser(){
    if(token_inicial->name != "A"){
        cout<<"Cadena No aceptada";
        EstadoAceptacion = false;
    }
    else{
        while(EstadoAceptacion==true){
            auto token_siguiente = next_Token()->name;
            if(token_siguiente == "A"){
                cout<<"Cadena No aceptada";
                EstadoAceptacion = false;
            }
            else if(token_siguiente == "Sh1"){
                auto procesando = is_Correct_Next(Rule_Sh1_Sh3(),next_Token()->name);
                EstadoAceptacion = procesando ? true : false;
                /*if(procesando){
                    continue;
                }
                else{
                    EstadoAceptacion=false;
                }*/
                next_Token(-1);
            }
            else if(token_siguiente == "Sh2"){
                auto procesando = is_Correct_Next(Rule_Sh2(),next_Token()->name);
                EstadoAceptacion = procesando ? true : false;
                next_Token(-1);
            }
            else if(token_siguiente == "Sh3"){
                auto procesando = is_Correct_Next(Rule_Sh1_Sh3(),next_Token()->name);
                EstadoAceptacion = procesando ? true : false;
                next_Token(-1);
            }
            else if(token_siguiente == "Sh4"){
                auto procesando = is_Correct_Next(Rule_Sh4(),next_Token()->name);
                EstadoAceptacion = procesando ? true : false;
                next_Token(-1);
            }
            else if(token_siguiente == "Sh5"){
                auto procesando = is_Correct_Next(Rule_Sh5(),next_Token()->name);
                EstadoAceptacion = procesando ? true : false;
                next_Token(-1);
            }
            else if(token_siguiente == "Sv1"){
                
            }
            else if(token_siguiente == "Sv2"){
                
            }
            else if(token_siguiente == "Sv3"){
                
            }
            else if(token_siguiente == "Sv4"){
                
            }
            else if(token_siguiente == "Sv5"){
                
            }
            else if(token_siguiente == "N1"){
                
            }
            else if(token_siguiente == "N2"){
                
            }
            else if(token_siguiente == "N3"){
                
            }
            else if(token_siguiente == "N4"){
                
            }
            else if(token_siguiente == "N5"){
                
            }
            else if(token_siguiente == "Ac1"){
                
            }
            else if(token_siguiente == "Ac2"){
                
            }
            else if(token_siguiente == "Ac3"){
                
            }
            else if(token_siguiente == "Ac4"){
                
            }
            else if(token_siguiente == "C1"){
                
            }
            else if(token_siguiente == "C2"){
                
            }
            else if(token_siguiente == "C3"){
                
            }
            else if(token_siguiente == "C4"){
                
            }

        }
    }
}