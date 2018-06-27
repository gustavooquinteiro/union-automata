#include "../lib/main.h"

int main(){
	
	Automata automato1;
	Automata automato2;
	UnionAutomata uniteAutomaton(automato1,automato2);
	uniteAutomaton.gerarArquivo();
	
}
