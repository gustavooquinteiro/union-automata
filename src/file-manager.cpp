#include "../lib/file-manager.h"

FileManager::FileManager(string nome){
  name = nome;
  arquivo.open(name, ios::out | ios::app);
}

FileManager::~FileManager(){
    cout << "Fechando arquivo" << endl;
    name.clear();
    arquivo.close();
}

void FileManager::gerarArquivo(const UnionAutomata &automata) {
  try{
    int cont = 0;
    arquivo << "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n<structure>&#13;\n\t<type>fa</type>&#13;\n\t<automaton>&#13;\n\t\t<!--The list of states.-->\n";
    for (auto actualState : automata.getEstados()){
        arquivo << "\t\t<state id=\"" << actualState.first<<""<<actualState.second <<"\" name=\"q"<< cont <<"\">&#13;\n";
        if (cont%2 == 0){
            float resultado = 135 + 50*(cont);
            arquivo << "\t\t\t<x>"<< resultado <<"</x>&#13;\n";
            arquivo << "\t\t\t<y>136.0</y>&#13;\n";
	    } else{
            float resultado = 135 + 50*(cont-1);
            arquivo << "\t\t\t<x>"<< resultado <<"</x>&#13;\n";
            arquivo << "\t\t\t<y>220.0</y>&#13;\n";
	    }

	    if (automata.isBeginState(actualState)){
	      arquivo <<  "\t\t\t<initial/>&#13;\n";
        }
	    
	    if(automata.findFinalState(actualState)){
		  	arquivo <<  "\t\t\t<final/>&#13;\n";
	    }
	    
    	arquivo << "\t\t</state>&#13;\n";
	    cont++;
    }

    arquivo << "\t\t<!-- The list of transitions -->\n";
    
  	for(auto it: automata.getDelta()){
  		par from = it.first;
  		for (auto i : it.second){
            char read = i.first;
            par to = i.second;
            arquivo << "\t\t<transition>&#13;\n";
            stringstream ss; 
  			arquivo << "\t\t\t<from>"<<from.first <<""<<from.second <<"</from>&#13;\n";
  			arquivo << "\t\t\t<to>"<< to.first << ""<<to.second <<"</to>&#13;\n";
  			arquivo << "\t\t\t<read>"<< read <<"</read>&#13;\n";
  			arquivo << "\t\t</transition>&#13;\n";
  		}
  	}
    arquivo << "\t</automaton>&#13;\n";
  	arquivo << "</structure>";
  } catch(exception& e){
    cerr << "Error occurred::" << e.what() << endl;
  }
  
cout << "Arquivo "<< name << " gerado!"<< endl;
}
