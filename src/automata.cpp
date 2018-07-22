#include "../lib/automata.h"

DeterministicAutomata::DeterministicAutomata(){
    
	int quantidadeLetras = 0;
	cout << "Insira a quantidade de letras do alfabeto: " << endl;
	cin >> quantidadeLetras;
	cout << "Insira as letras do alfabeto: " << endl;
	for (int i = 0; i < quantidadeLetras; i++){
		char letra;
		cin >> letra; 
		alfabeto.insert(letra);
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


bool DeterministicAutomata:: procuraEstadoFinal(int x){
    if (estadoFinal.find(x) != estadoFinal.end())
        return true;
    return false;
}

set<int> DeterministicAutomata:: getEstados() const{
     return estado;
}

map<int, map<char, int>> DeterministicAutomata :: getDelta() const{
    return delta;
}

set<int> DeterministicAutomata::getEstadosFinais() const{
    return estadoFinal;
}

int DeterministicAutomata ::getEstadoInicial() const{
    return estadoInicial;
}

set<char> DeterministicAutomata::getAlfabeto() const{
    return alfabeto;
}



NonDeterministicAutomata::NonDeterministicAutomata(){

}
NonDeterministicAutomata::~NonDeterministicAutomata(){

}

set<int> NonDeterministicAutomata:: getEstados() const{
     return estados;
}

map<int, map<char, set<int>>> NonDeterministicAutomata :: getDelta() const{
    return delta;
}

set<int> NonDeterministicAutomata::getEstadosFinais() const{
    return estadosFinais;
}

int NonDeterministicAutomata ::getEstadoInicial() const{
    return estadoInicial;
}

set<char> NonDeterministicAutomata::getAlfabeto() const{
    return alfabeto;
}
