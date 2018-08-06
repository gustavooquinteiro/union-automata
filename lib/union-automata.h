#ifndef UNION_AUTOMATA_H
#define UNION_AUTOMATA_H

#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <utility>
#include <algorithm>
#include <stdlib.h>
#include "automata.h"
#include "deterministic-automata.h"
using namespace std;


typedef pair<int, int> par; // Declaração de um par ordenado de estados

class UnionAutomata: public Automata{
private:
	set< par > estados; // Conjunto de estados, Q
	map <par, map< char, par> > delta; // Função de transição DELTA
	set <par> estadoFinal; // Conjunto de estados finais, F
	par estadoInicial; // Estado inicial q0
	set<char> alfabeto; // Alfabeto SIGMA
public:
  UnionAutomata(DeterministicAutomata A, DeterministicAutomata B);
	void unirAlfabeto(set<char> A, set<char> B);
  void gerarArquivo();
};

#endif
