#include <iostream>
#include <set>
#include <map>
#include <utility>
#include <algorithm>
#include <stdlib.h>
#include "automata.h"
using namespace std;

#ifndef UNION_AUTOMATA_H
#define UNION_AUTOMATA_H

typedef pair<int, int> par; // Declaração de um par ordenado de estados 

class UnionAutomata{
private:
	set< par > estados; // Conjunto de estados, Q
	map <par, map< char, par> > delta; // Função de transição DELTA  
	set <par> estadoFinal; // Conjunto de estados finais, F
	par estadoInicial; // Estado inicial q0 
	set<char> alfabeto; // Alfabeto SIGMA
public:
	UnionAutomata();
    UnionAutomata (Automata A, Automata B);
    ~UnionAutomata();
	void unirAlfabeto(Automata A, Automata B);
    void gerarArquivo();
};

#endif