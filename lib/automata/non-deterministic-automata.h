#include <iostream>
#include <set>
#include <map>
using namespace std;
#ifndef NFA_H
#define NFA_H

class NonDeterministicAutomata: public Automata{

public:
    NonDeterministicAutomata();
    ~NonDeterministicAutomata();
};


#endif
