#include <iostream>
#include <set>
#include <map>
using namespace std;
#ifndef AUTOMATA_H
#define AUTOMATA_H

class DeterministicAutomata{

private:
    set<int> estado; // Conjunto de estados, Q
	map<int, map<char, int> > delta; // Função de transição DELTA  
	set<int> estadoFinal; // Conjunto de estados finais, F
	int estadoInicial; // Estado inicial q0 
	set<char> alfabeto; // Alfabeto SIGMA
public:
    DeterministicAutomata();
    ~DeterministicAutomata();
    set<int> getEstados() const;
    map<int, map<char, int>> getDelta() const;
    set<int> getEstadosFinais() const;
    int getEstadoInicial() const;
    set<char> getAlfabeto() const;


};

class NonDeterministicAutomata{
private:
    set <int> estados;
    map <int, map<char, set<int>>> delta;
    set<int> estadosFinais;
    int estadoInicial;
    set <char> alfabeto;
public:
    NonDeterministicAutomata();
    ~NonDeterministicAutomata();
    set<int> getEstados() const;
    map<int, map<char, set<int>>> getDelta() const;
    set<int> getEstadosFinais() const;
    int getEstadoInicial() const;
    set<char> getAlfabeto() const;
};

#endif