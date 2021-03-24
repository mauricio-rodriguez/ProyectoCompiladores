#include "parser.h"

string aMayuscula(string cadena) {
  for (int i = 0; i < cadena.length(); i++) cadena[i] = toupper(cadena[i]);
  return cadena;
}

vector<string> No_terminales = {"A","Sh1","Sh2","Sh3","Sh4","Sh5","Sv1","Sv2","Sv3","Sv4","Sv5","N1","N2","N3","N4","N5","Ac1","Ac2","Ac3","Ac4","C1","C2","C3","C4"};

bool In_No_terminales(string &no_terminal){
    for(auto i = 0 ; i < No_terminales.size() ; i++){
        if(no_terminal == aMayuscula(No_terminales[i])){
            no_terminal = No_terminales[i];
            return true;
        }
    }
    return false;
}

void fabricaTextil(string cade){
    cadena = cade;
    auto tokens = lexer();

    for(auto i = tokens.begin() ; i != tokens.end(); i++){
        cout<<(*i)->name<<endl;
        if((*i)->accion == "Error"){
            (*i)->name=aMayuscula((*i)->name);
            if(In_No_terminales((*i)->name)==true){
                cout<<"Corrigiendo el estado "<<(*i)->name<< " a un estado aceptable "<<endl;
            }
        }
    }

    parser(tokens);
}