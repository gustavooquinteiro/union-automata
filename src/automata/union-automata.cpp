#include "../../lib/automata/union-automata.h"

UnionAutomata :: UnionAutomata(DeterministicAutomata A, DeterministicAutomata B){

    queue <par> fila;
    map <par, bool> marca;

    fila.push(make_pair(A.getEstadoInicial(), B.getEstadoInicial()));
    estadoInicial = fila.front();

    if (A.procuraEstadoFinal(estadoInicial.first) || B.procuraEstadoFinal(estadoInicial.second))
        estadoFinal.insert(estadoInicial);

    unirAlfabeto(A.getAlfabeto(), B.getAlfabeto());

    while (!fila.empty()){

        par front = fila.front();
        fila.pop();

        if (marca[front]) continue;
        marca[front] = true;

        estados.insert(front);

        for (set<char>::iterator lendo = alfabeto.begin(); lendo != alfabeto.end(); lendo++){
            par proximo = make_pair(A.getDelta()[front.first][*lendo], B.getDelta()[front.second][*lendo]);

            estados.insert(proximo);
            fila.push(proximo);


            if (A.procuraEstadoFinal(proximo.first) || B.procuraEstadoFinal(proximo.second))
                estadoFinal.insert(proximo);

            delta[front][*lendo] = proximo;
        }
    }
}

void UnionAutomata:: unirAlfabeto(set<char> A, set<char> B){
    if (A == B){
        alfabeto = A;
    }else{
        for (set<char>::iterator alfabetoA = A.begin(); alfabetoA != A.end(); alfabetoA++){
            alfabeto.insert(*alfabetoA);
        }

        for(set<char>::iterator alfabetoB = B.begin(); alfabetoB != B.end(); alfabetoB++){
            alfabeto.insert(*alfabetoB);
        }
    }
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
    fprintf(file, "<!-- The list of transitions -->\n");
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

	cout << "Arquivo uniao.jff gerado!"<< endl;
}
