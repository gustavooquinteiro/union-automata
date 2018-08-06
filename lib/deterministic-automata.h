#ifndef DFA_H
#define DFA_H

#include <iostream>
#include <set>
#include <map>
#include "automata.h"
using namespace std;

class DeterministicAutomata: public Automata{

public:
    DeterministicAutomata();
    bool procuraEstadoFinal(int x);
};

#endif
