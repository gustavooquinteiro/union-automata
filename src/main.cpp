#include "../lib/main.h"

int main(){
	
	ios_base::sync_with_stdio(false);

	DeterministicAutomata automato1;
	DeterministicAutomata automato2;
	UnionAutomata uniteAutomaton(automato1, automato2);
	uniteAutomaton.gerarArquivo();
    return(EXIT_SUCCESS);

}
