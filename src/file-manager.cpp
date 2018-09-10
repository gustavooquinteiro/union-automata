#include "../lib/file-manager.h"

FileManager::FileManager(char* nome, char* mode){
  name = nome;
  arquivo = fopen(nome, mode);
}

FileManager::~FileManager(){
  fclose(arquivo);
}

void FileManager::gerarArquivo(const UnionAutomata &automata) {
  try{
    int cont = 0;
    char str[] = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n<structure>&#13;\n\t<type>fa</type>&#13;\n\t<automaton>&#13;\n\t\t<!--The list of states.-->\n";
  	fputs(str, arquivo);  
    for (set<par>::iterator estado = automata.getEstados().begin(); estado != automata.getEstados().end(); estado++){
      par actualState = (*estado);
    	fprintf(arquivo, "\t\t<state id=\"%d%d\" name=\"q%d\">&#13;\n", actualState.first, actualState.second, cont);
	    if (cont%2 == 0){
        float resultado = (float)135 + 50*(cont);
        fprintf(arquivo, "\t\t\t<x>%0.1f</x>&#13;\n",resultado);
        fprintf(arquivo, "\t\t\t<y>136.0</y>&#13;\n");
	    } else{
        float resultado = (float)135 + 50*(cont-1);
        fprintf(arquivo, "\t\t\t<x>%0.1f</x>&#13;\n", resultado);
        fprintf(arquivo, "\t\t\t<y>220.0</y>&#13;\n");
	    }

	    if (automata.isBeginState(actualState)){
	      fprintf(arquivo,  "\t\t\t<initial/>&#13;\n");
      }
	    if(automata.findFinalState(actualState)){
		  	fprintf(arquivo, "\t\t\t<final/>&#13;\n");
	    }
    	fprintf(arquivo, "\t\t</state>&#13;\n");
	    cont++;
    }

    fprintf(arquivo, "\t\t<!-- The list of transitions -->\n");
  	for(map<par,map<char, par> >::iterator it = automata.getDelta().begin(); it != automata.getDelta().end(); it++){
  		par from = (*it).first;
  		for (map<char,par>::iterator i = (*it).second.begin(); i != (*it).second.end(); i++){
        char read = (*i).first;
        par to = (*i).second;
        fprintf(arquivo, "\t\t<transition>&#13;\n");
  			fprintf(arquivo, "\t\t\t<from>%d%d</from>&#13;\n", from.first, from.second);
  			fprintf(arquivo, "\t\t\t<to>%d%d</to>&#13;\n", to.first,to.second);
  			fprintf(arquivo, "\t\t\t<read>%c</read>&#13;\n", read);
  			fprintf(arquivo, "\t\t</transition>&#13;\n");
  		}
  	}
    fprintf(arquivo, "\t</automaton>&#13;\n");
  	fprintf(arquivo, "</structure>");
  } catch(exception& e){
    cerr << "Error occurred::" << e.what() << endl;
  }
cout << "Arquivo "<< name << " gerado!"<< endl;
}
