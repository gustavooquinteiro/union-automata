#include "../lib/main.h"

int main(){
    //Automata * automato1 = new Automata();
    //Automata * automato2 = new Automata();
	unique_ptr<Automata> automato1(new Automata);
    unique_ptr<Automata> automato2(new Automata);
    
	unique_ptr<UnionAutomata> uniteAutomaton(new UnionAutomata);
    //UnionAutomata * uniteAutomaton = new UnionAutomata();

	uniteAutomaton->unirAutomatos(*automato1, *automato2);
	string file = "uniao.jff";
	unique_ptr<FileManager>fileManager (new FileManager(file));
	fileManager->gerarArquivo(*uniteAutomaton);

	return(EXIT_SUCCESS);

}
