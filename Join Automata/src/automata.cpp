#include "../lib/automata.h"

Automata ::Automata(){
    
	string caracteres; 

	cout << "Insira o alfabeto na próxima linha: "<< endl;
	getline(cin, caracteres);
	for (int i =0; i < caracteres.size(); i++){
		if (caracteres[i] == ' ' || caracteres[i] == '\n') continue;
		alfabeto.insert(caracteres[i]);
	}

    int numeroDeEstados = 0;
    cout << "Insira a quantidade de estados do automato: " << endl;
	cin >> numeroDeEstados; 
	for (int i = 0; i < numeroDeEstados; i++){
		if (i == 0)
			estadoInicial = i;
		estado.insert(i);
	}

    int estadoDe, estadoPara;
	char palavra;
	int	numeroDeTransicoes = alfabeto.size() * estado.size();;
	cout << "Insira todas as transições do automato: " << endl;
	for(int j =0; j < numeroDeTransicoes; j++){
		cin >> estadoDe >> palavra >> estadoPara;
		delta[estadoDe][palavra] = estadoPara;
	}


   	int numeroEstadosFinais; 	
	int estadosFinal;
	cout << "Insira a quantidade de estados finais: " << endl;
	cin >> numeroEstadosFinais;	
	cout << "Insira os estados finais: " << endl;
	for (int i = 0; i < numeroEstadosFinais; i++){
		cin >> estadosFinal; 
		estadoFinal.insert(estadosFinal); 
	}	


}

Automata :: ~Automata(){
    delete this;
}

set<int> Automata:: getEstados() const{
     return estado;
}

map<int, map<char, int>> Automata :: getDelta() const{
    return delta;
}

set<int> Automata::getEstadosFinais() const{
    return estadoFinal;
}

int Automata ::getEstadoInicial() const{
    return estadoInicial;
}

set<char> Automata::getAlfabeto() const{
    return alfabeto;
}