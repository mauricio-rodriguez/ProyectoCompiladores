#include "lexer.h"

using namespace std;

bool isTokensOver = false;
bool estadoAceptacion = true;

vector<token*> lista_de_tokens;
typedef vector<string> lista;

token* next_Token(const int step = 1){
    static int index = 0;
    if (index == lista_de_tokens.size()-1) {
        isTokensOver = true;
        return (lista_de_tokens[index]);
    }
    else{
        if (step ==1) return lista_de_tokens[++index];
        else if (step == -1) return lista_de_tokens[--index]; 
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

lista Rule_C2(){
    lista siguiente = {"C4"};
    return siguiente;
}

lista Rule_C3_C4(){
    lista siguiente = {"A"};
    return siguiente;
}

lista callRule(string noTerminal){
    if (noTerminal == "A") return Rule_A();
    else if (noTerminal == "Sh1" || noTerminal == "Sh3") return Rule_Sh1_Sh3();
    else if (noTerminal == "Sh2") return Rule_Sh2();
    else if (noTerminal == "Sh4") return Rule_Sh4();
    else if (noTerminal == "Sh5") return Rule_Sh5();
    else if (noTerminal == "Sv1" || noTerminal == "Sv2") return Rule_Sv1_Sv2();
    else if (noTerminal == "Sv3" || noTerminal == "S4") return Rule_Sv3_Sv4();
    else if (noTerminal == "Sv5") return Rule_Sv5();
    else if (noTerminal == "N1") return Rule_N1();
    else if (noTerminal == "N2") return Rule_N2();
    else if (noTerminal == "N3" || noTerminal == "N4") return Rule_N3_N4();
    else if (noTerminal == "N5") return Rule_N5();
    else if (noTerminal == "Ac1" || noTerminal == "Ac2" || noTerminal == "Ac3") return Rule_Ac1_Ac2_Ac3();
    else if (noTerminal == "Ac4") return Rule_Ac4();
    else if (noTerminal == "C1") return Rule_C1();
    else if (noTerminal == "C2") return Rule_C2();
    else if (noTerminal == "C3" || noTerminal == "C4") return Rule_C3_C4();
}

string processExpected(const string &token){
    if (token == "A") return "tejido horizontal";
    else if (token[0] == 'S'){
        if (token[1] == 'h') return "Tejido vertical";
        else if (token[1] == 'v') return "Tenhido";
    } 
    else if (token[0] == 'N') return "acabado";
    else if (token[0] == 'A' && token[1] == 'c') return "confeccion";
    else if (token[0] == 'C') return "almacen";
}

void error(const string &token){
        cout<<endl<<"Error, se esperaba un proceso de "<<processExpected(token);
        auto lista = callRule(token);
        for (auto i = 0; i < lista.size(); i++){
            cout<<" "<<lista[i];
        }
        cout<<" luego de "<<token;
}


void parser(vector<token*> lista_Tokens){
    lista_de_tokens = lista_Tokens;
    auto token_inicial = lista_de_tokens[0];
    if(token_inicial->name != "A"){
        estadoAceptacion = false;
    }
    else{
        auto token_siguiente = token_inicial->name;
        while(estadoAceptacion==true and isTokensOver == false){
            if(token_siguiente == "A"){ 
                auto  token_siguiente_temp = next_Token()->name;
                if(isTokensOver == false){
                    auto procesando = is_Correct_Next(Rule_A(),token_siguiente_temp);
                    estadoAceptacion = procesando ? true : false;
                    if (estadoAceptacion == false){
                        error(token_siguiente);
                        break;
                    }
                    token_siguiente = token_siguiente_temp;
                }
                else break;
      
            }
            else if(token_siguiente == "Sh1"){
                auto  token_siguiente_temp = next_Token()->name;
                if(isTokensOver == false){
                    auto procesando = is_Correct_Next(Rule_Sh1_Sh3(),token_siguiente_temp);
                    estadoAceptacion = procesando ? true : false;
                    if (estadoAceptacion == false){
                        error(token_siguiente);
                        break;
                    }
                    token_siguiente = token_siguiente_temp;
                }
                else break;
            }
            else if(token_siguiente == "Sh2"){
                auto  token_siguiente_temp = next_Token()->name;
                if(isTokensOver == false){               
                    auto procesando = is_Correct_Next(Rule_Sh2(),token_siguiente_temp);
                    estadoAceptacion = procesando ? true : false;
                    if (estadoAceptacion == false){
                        error(token_siguiente);
                        break;
                    }
                    token_siguiente = token_siguiente_temp;
                }
                else break;
            }
            else if(token_siguiente == "Sh3"){
                auto  token_siguiente_temp = next_Token()->name;
                if(isTokensOver == false){               
                    auto procesando = is_Correct_Next(Rule_Sh1_Sh3(),token_siguiente_temp);
                    estadoAceptacion = procesando ? true : false;
                    if (estadoAceptacion == false){
                        error(token_siguiente);
                        break;
                    }
                    token_siguiente = token_siguiente_temp;
                }
                else break;
            }
            else if(token_siguiente == "Sh4"){
                auto  token_siguiente_temp = next_Token()->name;
                if(isTokensOver == false){               
                    auto procesando = is_Correct_Next(Rule_Sh4(),token_siguiente_temp);
                    estadoAceptacion = procesando ? true : false;
                    if (estadoAceptacion == false){
                        error(token_siguiente);
                        break;
                    }
                    token_siguiente = token_siguiente_temp;
                }
                else break;
            }
            else if(token_siguiente == "Sh5"){
                auto  token_siguiente_temp = next_Token()->name;
                if(isTokensOver == false){               
                    auto procesando = is_Correct_Next(Rule_Sh5(),token_siguiente_temp);
                    estadoAceptacion = procesando ? true : false;
                    if (estadoAceptacion == false){
                        error(token_siguiente);
                        break;
                    }
                    token_siguiente = token_siguiente_temp;
                }
                else break;                
            }
            else if(token_siguiente == "Sv1"){
                auto  token_siguiente_temp = next_Token()->name;
                if(isTokensOver == false){               
                    auto procesando = is_Correct_Next(Rule_Sv1_Sv2(),token_siguiente_temp);
                    estadoAceptacion = procesando ? true : false;
                    if (estadoAceptacion == false){
                        error(token_siguiente);
                        break;
                    }
                    token_siguiente = token_siguiente_temp;
                }
                else break;  
            }
            else if(token_siguiente == "Sv2"){
                auto  token_siguiente_temp = next_Token()->name;
                if(isTokensOver == false){
                    auto procesando = is_Correct_Next(Rule_Sv1_Sv2(),token_siguiente_temp);
                    estadoAceptacion = procesando ? true : false;
                    if (estadoAceptacion == false){
                        error(token_siguiente);
                        break;
                    }
                    token_siguiente = token_siguiente_temp;
                }
                else break;  
            }
            else if(token_siguiente == "Sv3"){
                auto  token_siguiente_temp = next_Token()->name;
                if(isTokensOver == false){
                    auto procesando = is_Correct_Next(Rule_Sv3_Sv4(),token_siguiente_temp);
                    estadoAceptacion = procesando ? true : false;
                    if (estadoAceptacion == false){
                        error(token_siguiente);
                        break;
                    }
                    token_siguiente = token_siguiente_temp;
                }
                else break; 
            }
            else if(token_siguiente == "Sv4"){
                auto  token_siguiente_temp = next_Token()->name;
                if(isTokensOver == false){
                    auto procesando = is_Correct_Next(Rule_Sv3_Sv4(),token_siguiente_temp);
                    estadoAceptacion = procesando ? true : false;
                    if (estadoAceptacion == false){
                        error(token_siguiente);
                        break;
                    }
                    token_siguiente = token_siguiente_temp;
                }
                else break;
            }
            else if(token_siguiente == "Sv5"){
                auto  token_siguiente_temp = next_Token()->name;
                if(isTokensOver == false){
                    auto procesando = is_Correct_Next(Rule_Sv5(),token_siguiente_temp);
                    estadoAceptacion = procesando ? true : false;
                    if (estadoAceptacion == false){
                        error(token_siguiente);
                        break;
                    }
                    token_siguiente = token_siguiente_temp;
                }
                else break;
            }
            else if(token_siguiente == "N1"){
                auto  token_siguiente_temp = next_Token()->name;
                if(isTokensOver == false){
                    auto procesando = is_Correct_Next(Rule_N1(),token_siguiente_temp);
                    estadoAceptacion = procesando ? true : false;
                    if (estadoAceptacion == false){
                        error(token_siguiente);
                        break;
                    }
                    token_siguiente = token_siguiente_temp;
                }
                else break;
            }
            else if(token_siguiente == "N2"){
                auto  token_siguiente_temp = next_Token()->name;
                if(isTokensOver == false){
                    auto procesando = is_Correct_Next(Rule_N2(),token_siguiente_temp);
                    estadoAceptacion = procesando ? true : false;
                    if (estadoAceptacion == false){
                        error(token_siguiente);
                        break;
                    }
                    token_siguiente = token_siguiente_temp;
                }
                else break;
            }
            else if(token_siguiente == "N3"){
                auto  token_siguiente_temp = next_Token()->name;
                if(isTokensOver == false){
                    auto procesando = is_Correct_Next(Rule_N3_N4(),token_siguiente_temp);
                    estadoAceptacion = procesando ? true : false;
                    if (estadoAceptacion == false){
                        error(token_siguiente);
                        break;
                    }
                    token_siguiente = token_siguiente_temp;
                }
                else break;
            }
            else if(token_siguiente == "N4"){
                auto  token_siguiente_temp = next_Token()->name;
                if(isTokensOver == false){               
                    auto procesando = is_Correct_Next(Rule_N3_N4(),token_siguiente_temp);
                    estadoAceptacion = procesando ? true : false;
                    if (estadoAceptacion == false){
                        error(token_siguiente);
                        break;
                    }
                    token_siguiente = token_siguiente_temp;
                }
                else break;

            }
            else if(token_siguiente == "N5"){
                auto  token_siguiente_temp = next_Token()->name;
                if(isTokensOver == false){               
                    auto procesando = is_Correct_Next(Rule_N5(),token_siguiente_temp);
                    estadoAceptacion = procesando ? true : false;
                    if (estadoAceptacion == false){
                        error(token_siguiente);
                        break;
                    }
                    token_siguiente = token_siguiente_temp;
                }
                else break;
            }
            else if(token_siguiente == "Ac1"){
                auto  token_siguiente_temp = next_Token()->name;
                if(isTokensOver == false){               
                    auto procesando = is_Correct_Next(Rule_Ac1_Ac2_Ac3(),token_siguiente_temp);
                    estadoAceptacion = procesando ? true : false;
                    if (estadoAceptacion == false){
                        error(token_siguiente);
                        break;
                    }
                    token_siguiente = token_siguiente_temp;
                }
                else break;
            }
            else if(token_siguiente == "Ac2"){
                auto  token_siguiente_temp = next_Token()->name;
                if(isTokensOver == false){               
                    auto procesando = is_Correct_Next(Rule_Ac1_Ac2_Ac3(),token_siguiente_temp);
                    estadoAceptacion = procesando ? true : false;
                    if (estadoAceptacion == false){
                        error(token_siguiente);
                        break;
                    }
                    token_siguiente = token_siguiente_temp;
                }
                else break;
            }
            else if(token_siguiente == "Ac3"){
                auto  token_siguiente_temp = next_Token()->name;
                if(isTokensOver == false){               
                    auto procesando = is_Correct_Next(Rule_Ac1_Ac2_Ac3(),token_siguiente_temp);
                    estadoAceptacion = procesando ? true : false;
                    if (estadoAceptacion == false){
                        error(token_siguiente);
                        break;
                    }
                    token_siguiente = token_siguiente_temp;
                }
                else break;
            }
            else if(token_siguiente == "Ac4"){
                auto  token_siguiente_temp = next_Token()->name;
                if(isTokensOver == false){               
                    auto procesando = is_Correct_Next(Rule_Ac4(),token_siguiente_temp);
                    estadoAceptacion = procesando ? true : false;
                    token_siguiente = token_siguiente_temp;
                }
                else break;
            }
            else if(token_siguiente == "C1"){
                auto  token_siguiente_temp = next_Token()->name;
                if(isTokensOver == false){               
                    auto procesando = is_Correct_Next(Rule_C1(),token_siguiente_temp);
                    estadoAceptacion = procesando ? true : false;
                    if (estadoAceptacion == false){
                        error(token_siguiente);
                        break;
                    }
                    token_siguiente = token_siguiente_temp;
                }
                else break;
            }
            else if(token_siguiente == "C2"){
                auto  token_siguiente_temp = next_Token()->name;
                if(isTokensOver == false){               
                    auto procesando = is_Correct_Next(Rule_C2(),token_siguiente_temp);
                    estadoAceptacion = procesando ? true : false;
                    if (estadoAceptacion == false){
                        error(token_siguiente);
                        break;
                    }
                    token_siguiente = token_siguiente_temp;
                }
                else break;
            }
            else if(token_siguiente == "C3"){
                auto  token_siguiente_temp = next_Token()->name;
                if(isTokensOver == false){               
                    auto procesando = is_Correct_Next(Rule_C3_C4(),token_siguiente_temp);
                    estadoAceptacion = procesando ? true : false;
                    if (estadoAceptacion == false){
                        error(token_siguiente);
                        break;
                    }
                    token_siguiente = token_siguiente_temp;
                }
                else break;
            }
            else if(token_siguiente == "C4"){
                auto  token_siguiente_temp = next_Token()->name;
                if(isTokensOver == false){               
                    auto procesando = is_Correct_Next(Rule_C3_C4(),token_siguiente_temp);
                    estadoAceptacion = procesando ? true : false;
                    if (estadoAceptacion == false){
                        error(token_siguiente);
                        break;
                    }
                    token_siguiente = token_siguiente_temp;
                }
                else break;
            }

        }
        if(estadoAceptacion==false){
            
        }
        else if(token_siguiente =="A" ){
            cout<<endl<<"Cadena Aceptada\n";
        }
        else{
            cout<<endl<<"Cadena No Aceptada\n";
        }
    }
}
