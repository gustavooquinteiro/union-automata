#include "../../lib/automata/non-deterministic-automata.h"

NonDeterministicAutomata::NonDeterministicAutomata(){

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
	int	numeroDeTransicoes;

    cout << "Insira a quantidade de transições do automato: "<< endl;
    cin >> numeroDeTransicoes;

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

NonDeterministicAutomata::~NonDeterministicAutomata(){

}
