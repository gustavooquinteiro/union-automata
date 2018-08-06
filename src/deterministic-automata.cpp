#include "../lib/deterministic-automata.h"

DeterministicAutomata::DeterministicAutomata(){
  Automata();
}

bool DeterministicAutomata::procuraEstadoFinal(int valor){
  if (estadoFinal.find(valor) != estadoFinal.end())
    return true;
  return false;
}
