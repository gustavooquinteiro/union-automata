#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <utility>
#include <set>
#include <map>
using namespace std;

// Desenvolvedores: Christian Elster e Gustavo Oliveira Quinteiro
// Compile com g++ joinAutomata.cpp 

typedef pair<int, int> par; // Declaração de um par ordenado de estados 

struct Automato{
	set<int> estado; // Conjunto de estados, Q
	map<int, map<char, int> > delta; // Função de transição DELTA  
	set<int> estadoFinal; // Conjunto de estados finais, F
	int estadoInicial; // Estado inicial q0 
	set<char> alfabeto; // Alfabeto SIGMA
};

struct AutomatoDaUniao{
	set< par > estados; // Conjunto de estados, Q
	map <par, map< char, par> > delta; // Função de transição DELTA  
	set <par> estadoFinal; // Conjunto de estados finais, F
	par estadoInicial; // Estado inicial q0 
	set<char> alfabeto; // Alfabeto SIGMA
};

Automato lerTransicoes(Automato automato){
	int estadoDe, estadoPara, j = 0;
	char palavra;
	int	numeroDeTransicoes = automato.alfabeto.size() * automato.estado.size();;
	cout << "Insira todas as transições do automato: " << endl;
	while(j < numeroDeTransicoes){
		cin >> estadoDe >> palavra >> estadoPara;
		automato.delta[estadoDe][palavra] = estadoPara;
		j++;
	}
 	return automato;
}


Automato lerEstadosFinais(Automato automato){
	int numeroEstadosFinais; 	
	int estadoFinal;
	cout << "Insira a quantidade de estados finais: " << endl;
	cin >> numeroEstadosFinais;	
	cout << "Insira os estados finais: " << endl;
	for (int i = 0; i < numeroEstadosFinais; i++){
		cin >> estadoFinal; 
		automato.estadoFinal.insert(estadoFinal); 
	}	
	
	return automato;
}

Automato iniciarAutomato (Automato automato, set<char> alfabeto){
	int numeroDeEstados;
	
	automato.alfabeto = alfabeto;
	
	// Lê  a quantidade de estados que o automato tem
	cout << "Insira a quantidade de estados do automato: " << endl;
	cin >> numeroDeEstados; 
	// Insere os estados (de 0 a numeroDeEstados -1) no automato 
	for (int i = 0; i < numeroDeEstados; i++){
		// Assumo 0 como estado inicial
		if (i == 0)
			automato.estadoInicial = i;
		automato.estado.insert(i);
	}
	
	// Ler as transicoes do automato
	automato = lerTransicoes(automato);

	// Lê os estados finais que o automato tem
	automato = lerEstadosFinais(automato); 
	
	return automato; 
}

AutomatoDaUniao unirAutomatos(Automato A1, Automato A2){
	AutomatoDaUniao M;
	
	// Iterando sobre todos os estados de A1 e A2 
	for (set<int>::iterator it = A1.estado.begin(); it != A1.estado.end(); it++){
		for (set<int>::iterator i = A2.estado.begin(); i != A2.estado.end(); i++){

			// Cria um novo estado com o par it (estado de A1) e i (estado de A2)
			par from = make_pair(*it, *i); 

			// Adiciona esse novo estado no conjunto de estados do automato da uniao
			M.estados.insert(from);
			
			// Se um desses estados for estado final de seu respectivo automato o estado formado pelo par também será
			if (A1.estadoFinal.find(*it) != A1.estadoFinal.end() || A2.estadoFinal.find(*i) != A2.estadoFinal.end())
				M.estadoFinal.insert(from);
				
			// Se os dois são estados iniciais o estado formado pelo par também o será
			if (*it == 0 && *i == 0)
				M.estadoInicial = from;
			
			// Iterando sobre o alfabeto dos automatos
			for(set<char>::iterator read = A1.alfabeto.begin(); read !=A1.alfabeto.end(); ++read){
				
				// Pegando o estado destino do automato1 do estado it lendo o caracter read 
				int paraA1 = A1.delta[*it][*read];
				
				// Pegando o estado destino do automato2 do estado i lendo o caracter read
				int paraA2 = A2.delta[*i][*read];
				
				// Criando o estado de destino do automato da uniao, o par com os estados destinos dos dois automatos
				par to = make_pair(paraA1, paraA2);
				
				// Insere como novo estado no automato da uniao
				M.estados.insert(to);
				
				// Mapeia a transicao, no automato da uniao, onde o estado from lendo o caractere read vai para o estado to 
				M.delta[from][*read] = to;
			}			
		}
	}
	return M;
}

void gerarArquivoDoJFLAP(AutomatoDaUniao M){
	FILE* file;
	
	file = fopen("uniao.jff", "w");
	int cont = 0;
	fprintf(file,"<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n" );
	fprintf(file, "<structure>&#13;\n");	
	fprintf(file, "\t<type>fa</type>&#13;\n");
	fprintf(file, "\t<automaton>&#13;\n		<!--The list of states.-->\n");
	// Listando os estados do automato 
	for(set<par>::iterator it = M.estados.begin(); it != M.estados.end(); it++){
		fprintf(file, "\t\t<state id=\"%d%d\" name=\"q%d\">&#13;\n", (*it).first, (*it).second, cont);
		if (cont%2 == 0){
			fprintf(file, "\t\t\t<x>%0.1f</x>&#13;\n",(float)135 + 50*(cont));
			fprintf(file, "\t\t\t<y>136.0</y>&#13;\n");
		} else{
			fprintf(file, "\t\t\t<x>%0.1f</x>&#13;\n", (float)135 + 60*(cont-1));
			fprintf(file, "\t\t\t<y>226.0</y>&#13;\n");
		}
		
		if ( (*it) == M.estadoInicial){
			fprintf(file,  "\t\t\t<initial/>&#13;\n");
		}
		
		if(M.estadoFinal.find(*it) != M.estadoFinal.end()){
			fprintf(file, "\t\t\t<final/>&#13;\n");
		}
		fprintf(file, "\t\t</state>&#13;\n");
		cont++;
	}
	// Listando as transições do automato
	for(map<par,map<char, par> >::iterator it = M.delta.begin(); it != M.delta.end(); it++){
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
	cout << "Arquivo uniao.jff gerado" << endl; 
}

set<char> lerAlfabeto(){
	set<char> alfabeto;	
	string caracteres; 

	cout << "Insira o alfabeto na próxima linha: "<< endl;
	getline(cin, caracteres);
	for (int i =0; i < caracteres.size(); i++){
		if (caracteres[i] == ' ' || caracteres[i] == '\n') continue;
		alfabeto.insert(caracteres[i]);
	}
	
	return alfabeto;
}

int main(){
	Automato automato1,  automato2;  	
	
	set<char> alfabeto = lerAlfabeto();

	cout << "Automato 1" << endl;	
	automato1 = iniciarAutomato(automato1, alfabeto); 

	cout << "Automato 2" << endl;
	automato2 = iniciarAutomato(automato2, alfabeto);

	cout << "Unindo os automatos" << endl;
	// Gerar arquivo de saída do automato A1 U A2 
	gerarArquivoDoJFLAP(unirAutomatos(automato1, automato2));
	
}
