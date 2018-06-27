#include <iostream>
#include <set>
#include <map>
using namespace std;
#ifndef AUTOMATA_H
#define AUTOMATA_H

class Automata{

private:
    set<int> estado; // Conjunto de estados, Q
	map<int, map<char, int> > delta; // Função de transição DELTA  
	set<int> estadoFinal; // Conjunto de estados finais, F
	int estadoInicial; // Estado inicial q0 
	set<char> alfabeto; // Alfabeto SIGMA
public:
    Automata();
    ~Automata();
    set<int> getEstados() const;
    map<int, map<char, int>> getDelta() const;
    set<int> getEstadosFinais() const;
    int getEstadoInicial() const;
    set<char> getAlfabeto() const;


};

#endif