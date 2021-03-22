

char nextChar(const int step = 1){
    static int index = 0;
    if (index == cadena.length()) isCadenaOver = true;
    else{
        if (step ==1) return cadena[index++];
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
            int char_to_int = character-48;
            if (char_to_int<upper_bound && char_to_int>lower_bound) {
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
    cadena_acumulada = "";
}

void caseA(string &cadena_acumulada){
    cadena_acumulada+= 'A';
    auto next_char = nextChar();
    token *Token = new token();
    switch(next_char){
        case 'c':
            cadena_acumulada += next_char;
            next_char = nextChar();
            checkDigit(5,0,"Acabado",next_char,Token,cadena_acumulada);
            break;
        default:
            nextChar(-1);
            Token->name = cadena_acumulada;
            Token->accion = "Almacen";
            add_listatokens(Token);
            cadena_acumulada = "";
            break;
    }
}

void caseS(string &cadena_acumulada){
    cadena_acumulada+='S';
    char next_char = nextChar();
    token *Token = new token();
    switch(next_char){
        case 'h':
            cadena_acumulada+=next_char;
            next_char = nextChar();
            checkDigit(6,0,"Tejido Horizontal",next_char,Token,cadena_acumulada);
            break;
        case 'v': 
            cadena_acumulada+=next_char;
            next_char = nextChar();
            checkDigit(6,0,"Tejido Vertical",next_char,Token,cadena_acumulada);
            break;
        default:
            next_char = nextChar();
            while(!(next_char == 'A' or next_char == 'C' or next_char == 'S' or next_char == 'N' or isCadenaOver==true)){
                cadena_acumulada+= next_char;
                next_char =  nextChar();
            }
            Token->name = cadena_acumulada;
            Token->accion = "Error";
            add_listatokens(Token);
            cadena_acumulada = "";
            nextChar(-1);
            break;
    }
}


void caseN(string &cadena_acumulada){
    cadena_acumulada+= 'N';
    auto next_char = nextChar();
    token *Token = new token();
    checkDigit(6,0,"Tenhido",next_char,Token,cadena_acumulada);
}

void caseC(string &cadena_acumulada){
    cadena_acumulada+= 'C';
    auto next_char = nextChar();
    token *Token = new token();
    checkDigit(5,0,"Confeccion",next_char,Token,cadena_acumulada);
    
}

void lexer(){
    string cadena_acumulada = "";
    while(isCadenaOver == false){
        char next_char = nextChar();
        switch(next_char){
        case 'A':
            caseA(cadena_acumulada);
            break;
        case 'S':
            caseS(cadena_acumulada);
            break;
        case 'N':
            caseN(cadena_acumulada);
            break;
        case 'C':
            caseC(cadena_acumulada);
            break;
        default:
            while(!(next_char == 'A' or next_char == 'C' or next_char == 'S' or next_char == 'N' or isCadenaOver==true)){
                cadena_acumulada+= next_char;
                next_char =  nextChar();
            }
            if(isCadenaOver==true){
                break;
            }
            else{
                token *NoAceptado = new token();
                NoAceptado->name = cadena_acumulada;
                NoAceptado->accion = "Error";
                add_listatokens(NoAceptado);
                cadena_acumulada = "";
                nextChar();
                break;
            }
        }
    }
    cout<<"Lectura de : "<<cadena<<endl;
    cout<<"{";
    for(int i = 0 ; i <  lista_tokens.size() ; i++){
        lista_tokens[i]->printToken();
        cout<<" ; ";
    }
    cout<<"}";
}