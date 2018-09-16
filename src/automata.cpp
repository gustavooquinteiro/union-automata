#include "../lib/automata.h"

Automata::Automata(){
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

  int estadoDe, estadoPara = 0;
	char palavra;
	int	numeroDeTransicoes = alfabeto.size() * estado.size();;
	cout << "Insira todas as transições do automato: " << endl;
	for(int j =0; j < numeroDeTransicoes; j++){
		cin >> estadoDe >> palavra >> estadoPara;
		delta[estadoDe][palavra] = estadoPara;
	}

 	int numeroEstadosFinais, estadosFinal = 0;
	cout << "Insira a quantidade de estados finais: " << endl;
	cin >> numeroEstadosFinais;
	cout << "Insira os estados finais: " << endl;
	for (int i = 0; i < numeroEstadosFinais; i++){
		cin >> estadosFinal;
		estadoFinal.insert(estadosFinal);
	}
}


set<int> Automata::getEstados() const{
     return estado;
}

int Automata::getTransicao(int de, char lendo) const{
		return delta.at(de).at(lendo);
}

set<int> Automata::getEstadosFinais() const{
    return estadoFinal;
}

int Automata::getEstadoInicial() const{
    return estadoInicial;
}

set<char> Automata::getAlfabeto() const{
    return alfabeto;
}

bool Automata::procuraEstadoFinal(int valor) const{
  if (estadoFinal.find(valor) != estadoFinal.end())
    return true;
  return false;
}

Automata::~Automata(){
    estado.clear();
    estadoFinal.clear();
    alfabeto.clear();
    delta.clear();
}
