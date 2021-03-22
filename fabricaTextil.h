#include "parser.h"

void fabricaTextil(string cade){
    cadena = cade;
    auto tokens = lexer();
    parser(tokens);
}