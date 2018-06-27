#include "../lib/union-automata.h"

UnionAutomata :: UnionAutomata(Automata A, Automata B){

    for(set<int>::iterator estadoDeA = A.getEstados().begin(); estadoDeA != A.getEstados().end(); estadoDeA++){
        for(set<int>::iterator estadoDeB = B.getEstados().begin(); estadoDeB != B.getEstados().end(); estadoDeB++){
            par from = make_pair(*estadoDeA, *estadoDeB);
            estados.insert(from);

            if (A.getEstadosFinais().find(*estadoDeA) != A.getEstadosFinais().end() || B.getEstadosFinais().find(*estadoDeB) != B.getEstadosFinais().end()){
                estadoFinal.insert(from);
            }

            if (A.getEstadoInicial() == *estadoDeA && B.getEstadoInicial() == *estadoDeB){
                estadoInicial = from;
            }
        }
    }
	for (set<par>::iterator iterando = estados.begin(); iterando != estados.end(); iterando++){
		if (A.getAlfabeto() == B.getAlfabeto()){
			alfabeto = A.getAlfabeto();
			for (set<char>::iterator lendo = alfabeto.begin(); lendo != alfabeto.end(); lendo++){
				int destinoDeA = A.getDelta()[(*iterando).first][*lendo];
				int destinoDeB = B.getDelta()[(*iterando).second][*lendo];
				par to = make_pair(destinoDeA, destinoDeB);
				estados.insert(to);
				delta[*iterando][*lendo] = to;
			}
		} else{
			unirAlfabeto(A, B);
			for (set<char>::iterator lendo = alfabeto.begin(); lendo != alfabeto.end(); lendo++){
				if (A.getAlfabeto().find(*lendo) != A.getAlfabeto().end()){
					int destinoDeA = A.getDelta()[(*iterando).first][*lendo];
					for (set<int>::iterator it = B.getEstados().begin(); it != B.getEstados().end(); it++){
						par novo = make_pair(destinoDeA, *it);
						delta[*iterando][*lendo] = novo; 
					}
				}
				if (B.getAlfabeto().find(*lendo) != B.getAlfabeto().end()){
					int destinoDeB = B.getDelta()[(*iterando).second][*lendo];
					for (set<int>::iterator it = A.getEstados().begin(); it != A.getEstados().end(); it++){
						par novo = make_pair(*it, destinoDeB);
						delta[*iterando][*lendo] = novo; 
					}
				}
				
					
			}
		}
	}
	


}

void UnionAutomata:: unirAlfabeto(Automata A, Automata B){
	for (set<char>::iterator alfabetoA = A.getAlfabeto().begin(); alfabetoA != A.getAlfabeto().end(); alfabetoA++){	
		alfabeto.insert(*alfabetoA);
	}

	for(set<char>::iterator alfabetoB = B.getAlfabeto().begin(); alfabetoB != B.getAlfabeto().end(); alfabetoB++){
		alfabeto.insert(*alfabetoB);
	}
}

UnionAutomata :: ~UnionAutomata(){
    delete this;
}

void UnionAutomata:: gerarArquivo(){
    FILE * file = fopen("uniao.jff", "w");
    int cont = 0;  
    fprintf(file,"<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" );
	fprintf(file, "<structure>&#13;\n");	
	fprintf(file, "\t<type>fa</type>&#13;\n");
	fprintf(file, "\t<automaton>&#13;\n		<!--The list of states.-->\n");
    for (set<par>::iterator estado = estados.begin(); estado != estados.end(); estado++){
        fprintf(file, "\t\t<state id=\"%d%d\" name=\"q%d\">&#13;\n", (*estado).first, (*estado).second, cont);
		if (cont%2 == 0){
			fprintf(file, "\t\t\t<x>%0.1f</x>&#13;\n",(float)135 + 50*(cont));
			fprintf(file, "\t\t\t<y>136.0</y>&#13;\n");
		} else{
			fprintf(file, "\t\t\t<x>%0.1f</x>&#13;\n", (float)135 + 60*(cont-1));
			fprintf(file, "\t\t\t<y>226.0</y>&#13;\n");
		}
		
		if ( (*estado) == estadoInicial){
			fprintf(file,  "\t\t\t<initial/>&#13;\n");
		}
		
		if(estadoFinal.find(*estado) != estadoFinal.end()){
			fprintf(file, "\t\t\t<final/>&#13;\n");
		}
		fprintf(file, "\t\t</state>&#13;\n");
		cont++;
    }      

    // Listando as transições do automato
	for(map<par,map<char, par> >::iterator it = delta.begin(); it != delta.end(); it++){
		par from = (*it).first;
		for (map<char,par>::iterator i = (*it).second.begin(); i != (*it).second.end(); i++){
			par to = (*i).second; 
			char read = (*i).first;
			fprintf(file, "\t\t<transition>&#13;\n");
			fprintf(file, "\t\t\t<from>%d%d</from>&#13;\n", from.first, from.second);
			fprintf(file, "\t\t\t<to>%d%d</to>&#13;\n", to.first,to.second);
			fprintf(file, "\t\t\t<read>%c</read>&#13;\n", read);
			fprintf(file, "\t\t</transition>&#13;\n");
		}
	}

	fprintf(file, "\t</automaton>&#13;\n");
	fprintf(file, "</structure>");
	fclose(file);

}