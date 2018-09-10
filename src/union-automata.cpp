#include "../lib/union-automata.h"

UnionAutomata::UnionAutomata(){}

void UnionAutomata::unirAutomatos(const Automata &A, const Automata &B){

    queue <par> fila;
    map <par, bool> marca;

    fila.push(make_pair(A.getEstadoInicial(), B.getEstadoInicial()));
    estadoInicial = fila.front();

    if (A.procuraEstadoFinal(estadoInicial.first) || B.procuraEstadoFinal(estadoInicial.second))
        estadoFinal.insert(estadoInicial);

    unirAlfabeto(A.getAlfabeto(), B.getAlfabeto());

    while (!fila.empty()){

        par from = fila.front();
        fila.pop();

        if (marca[from]) continue;
        marca[from] = true;

        estados.insert(from);

        for (set<char>::iterator lendo = alfabeto.begin(); lendo != alfabeto.end(); lendo++){
            char read = *lendo;
            par to = make_pair(A.getTransicao(from.first, read), B.getTransicao(from.second, read));
            estados.insert(to);
            fila.push(to);

            if (A.procuraEstadoFinal(to.first) || B.procuraEstadoFinal(to.second))
                estadoFinal.insert(to);

            delta[from][read] = to;
        }
    }

    //minimizar();
}

void UnionAutomata::minimizar() const{

}

set<par> UnionAutomata::getEstados() const{
  return estados;
}

bool UnionAutomata::findFinalState(par actualState) const{
  if (estadoFinal.find(actualState) != estadoFinal.end()) return true;
  return false;
}

bool UnionAutomata::isBeginState(par actualState) const{
  if (actualState == estadoInicial) return true;
  return false;
}

map <par, map< char, par> > UnionAutomata::getDelta() const{
  return delta;
}

/**UnionAutomata::~UnionAutomata(){
  delete &estados;
  delete &estadoFinal;
  delete &alfabeto;
  delete &delta;
  delete &estadoInicial;
}**/

void UnionAutomata::unirAlfabeto(const set<char> &A, const set<char> &B){
      if(A == B){
        alfabeto = A;
      } else{
        for (set<char>::iterator alfabetoA = A.begin(); alfabetoA != A.end(); alfabetoA++){
            alfabeto.insert(*alfabetoA);
        }
        for(set<char>::iterator alfabetoB = B.begin(); alfabetoB != B.end(); alfabetoB++){
            alfabeto.insert(*alfabetoB);
        }
    }
}
