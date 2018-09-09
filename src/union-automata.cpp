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

void UnionAutomata::gerarArquivo() {
  try{
    FILE * file = fopen("uniao.jff", "w");
    int cont = 0;
    char str[] = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n";
  	fputs(str, file);
    fputs("<structure>&#13;\n", file);
	  fputs("\t<type>fa</type>&#13;\n", file);
	  fputs("\t<automaton>&#13;\n		<!--The list of states.-->\n", file);
    for (set<par>::iterator estado = estados.begin(); estado != estados.end(); estado++){
      par actualState = (*estado);
    	fprintf(file, "\t\t<state id=\"%d%d\" name=\"q%d\">&#13;\n", actualState.first, actualState.second, cont);
	    if (cont%2 == 0){
        float resultado = (float)135 + 50*(cont);
        fprintf(file, "\t\t\t<x>%0.1f</x>&#13;\n",resultado);
        fprintf(file, "\t\t\t<y>136.0</y>&#13;\n");
	    } else{
        float resultado = (float)135 + 50*(cont-1);
        fprintf(file, "\t\t\t<x>%0.1f</x>&#13;\n", resultado);
        fprintf(file, "\t\t\t<y>220.0</y>&#13;\n");
	    }

	    if ( actualState == estadoInicial){
	      fprintf(file,  "\t\t\t<initial/>&#13;\n");
      }
	    if(estadoFinal.find(actualState) != estadoFinal.end()){
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
  } catch(exception& e){
    cerr << "Error occurred::" << e.what() << endl;
  }
cout << "Arquivo uniao.jff gerado!"<< endl;
}
