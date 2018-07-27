#include <iostream>
#include <set>
#include <map>
using namespace std;
#ifndef DFA_H
#define DFA_H

class DeterministicAutomata: public Automata{

public:
    DeterministicAutomata();
    bool procuraEstadoFinal(int x);
};

#endif
