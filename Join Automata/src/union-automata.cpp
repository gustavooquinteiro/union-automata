#include "../lib/union-automata.h"

UnionAutomata :: UnionAutomata(DeterministicAutomata A, DeterministicAutomata B){
	cout << "Juntando os automatos" << endl;
    for(set<int>::iterator estadoDeA = A.getEstados().begin(); estadoDeA != A.getEstados().end(); estadoDeA++){
        for(set<int>::iterator estadoDeB = B.getEstados().begin(); estadoDeB != B.getEstados().end(); estadoDeB++){
           	cout << "Formando os pares" << endl;
           	cout << *estadoDeA << " e " << *estadoDeB << endl;
            par from = make_pair(*estadoDeA, *estadoDeB);
            cout << "Inserindo no automato da união" << endl;
            estados.insert(from);

            if (A.getEstadosFinais().find(*estadoDeA) != A.getEstadosFinais().end() || B.getEstadosFinais().find(*estadoDeB) != B.getEstadosFinais().end()){
                cout << "Definindo estados finais" << endl;
                estadoFinal.insert(from);
            }

            if (A.getEstadoInicial() == *estadoDeA && B.getEstadoInicial() == *estadoDeB){
            	cout << "Definindo o estado inicial" << endl;
                estadoInicial = from;
            }
        }
    }
	unirAlfabeto(A.getAlfabeto(), B.getAlfabeto());
	for (set<par>::iterator iterando = estados.begin(); iterando != estados.end(); iterando++){
		for (set<char>::iterator lendo = alfabeto.begin(); lendo != alfabeto.end(); lendo++){
			cout << "Mapeando" << endl;
			int destinoDeA = 0, destinoDeB = 0;
			bool flagA, flagB;

			if (A.getAlfabeto().find(*lendo) != A.getAlfabeto().end()){
				cout << "Pegando de A" << endl;
				destinoDeA = A.getDelta()[(*iterando).first][*lendo];
				flagA = true;
			} 
				

			if (B.getAlfabeto().find(*lendo) != B.getAlfabeto().end()){
				cout << "Pegando de B" << endl;
				destinoDeB = B.getDelta()[(*iterando).second][*lendo];
				flagB = true;
			}
				
			if (flagA && flagB){
				cout << "Juntando os estados" << endl;
				par to = make_pair(destinoDeA, destinoDeB);
				cout << "Inserindo o estado" << endl;
				estados.insert(to);
				cout << "Inserindo no delta da união" << endl;
				delta[*iterando][*lendo] = to;
			} else{
				for(set<par>::iterator estado = estados.begin(); estado != estados.end(); estado++){
					if (!flagA && estado->second == destinoDeB){
						delta[*iterando][*lendo] = *estado;
					}
					if (!flagB && estado->first == destinoDeA){
						delta[*iterando][*lendo] = *estado;
					}
				}
			}
		}
	}
}

void UnionAutomata:: unirAlfabeto(set<char> A, set<char> B){
	cout << "Unindo os alfabetos" << endl;
	for (set<char>::iterator alfabetoA = A.begin(); alfabetoA != A.end(); alfabetoA++){	
		alfabeto.insert(*alfabetoA);
	}

	for(set<char>::iterator alfabetoB = B.begin(); alfabetoB != B.end(); alfabetoB++){
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

	cout << "Arquivo gerado!"<< endl;
}