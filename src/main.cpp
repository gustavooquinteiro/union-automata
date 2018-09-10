#include "../lib/main.h"

int main(){

	Automata automato1;
	Automata automato2;
	UnionAutomata uniteAutomaton;

	uniteAutomaton.unirAutomatos(automato1, automato2);
	char mode[] = "w";
	char file[] = "uniao.jff";
	FileManager fileManager(file, mode);
	fileManager.gerarArquivo(uniteAutomaton);


	return(EXIT_SUCCESS);

}

void removeMemoryHeap(Automata * automata){
	delete automata;
}
