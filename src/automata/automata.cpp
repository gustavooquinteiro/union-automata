#include "../../lib/automata/automata.h"

Automata:: Automata(){

}

set<int> Automata:: getEstados() const{
     return estado;
}

map<int, map<char, int>> Automata:: getDelta() const{
    return delta;
}

set<int> Automata::getEstadosFinais() const{
    return estadoFinal;
}

int Automata ::getEstadoInicial() const{
    return estadoInicial;
}

set<char> Automata::getAlfabeto() const{
    return alfabeto;
}
