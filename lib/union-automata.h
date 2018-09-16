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
using namespace std;


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
  ~UnionAutomata();
	void unirAutomatos(const Automata &A, const Automata &B);
	void unirAlfabeto(const set<char> &A, const set<char> &B);
  void gerarArquivo();
	set<par> getEstados() const;
	bool findFinalState(par actualState) const;
	bool isBeginState(par actualState) const;
	map <par, map< char, par> > getDelta() const;
	void minimizar() const;
};

#endif
