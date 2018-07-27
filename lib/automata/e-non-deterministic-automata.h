#include <iostream>
#include <set>
#include <map>
using namespace std;

#ifndef E_NFA_H
#define  E_NFA_H

class EpsilonNonDeterministic: public NonDeterministicAutomata{

public:
    EpsilonNonDeterministic();
    ~EpsilonNonDeterministic();
};


#endif
