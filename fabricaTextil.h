#include "parser.h"

string aMayuscula(string cadena) {
  for (int i = 0; i < cadena.length(); i++) cadena[i] = toupper(cadena[i]);
  return cadena;
}

string No_terminales[24][2] = {{"A","Almacen"},
{"Sh1","Tejido horizontal"},{"Sh2","Tejido horizontal"},{"Sh3","Tejido horizontal"},{"Sh4","Tejido horizontal"},{"Sh5","Tejido horizontal"},
{"Sv1","Tejido vertical"},{"Sv2","Tejido vertical"},{"Sv3","Tejido vertical"},{"Sv4","Tejido vertical"},{"Sv5","Tejido vertical"},
{"N1","Tenhido"},{"N2","Tenhido"},{"N3","Tenhido"},{"N4","Tenhido"},{"N5","Tenhido"},
{"Ac1","Acabado"},{"Ac2","Acabado"},{"Ac3","Acabado"},{"Ac4","Acabado"},
{"C1","confeccion"},{"C2","confeccion"},{"C3","confeccion"},{"C4","confeccion"}};

bool In_No_terminales(string &no_terminal,string &accion){
    for(auto i = 0 ; i < 24 ; i++){
        if(no_terminal == aMayuscula(No_terminales[i][0])){ 
            no_terminal = No_terminales[i][0];
            accion = No_terminales[i][1];
            return true;
        }
    }
    return false;
}

void fabricaTextil(string cade){
    cadena = cade;
    auto tokens = lexer();
    cout<<endl<<"Haciendo correciones"<<endl;
    for(auto i = tokens.begin() ; i != tokens.end(); i++){
        cout<<(*i)->name<<endl;
        if((*i)->accion == "Error"){
            (*i)->name=aMayuscula((*i)->name); 
            if(In_No_terminales((*i)->name,(*i)->accion)==true){
                cout<<"Corrigiendo el estado "<<(*i)->name<< " a un estado aceptable "<<endl;
            }
        }
    }
    cout<<"\nCorrigiendo la cadena :  "<<cadena<<endl;
    cout<<"{";
    for(int i = 0 ; i <  tokens.size() ; i++){
        tokens[i]->printToken();
        cout<<" ; ";
        if((i+1)%2 == 0){
            cout<<endl;
        }
    }
    cout<<"}"<<endl;
    parser(tokens);
}