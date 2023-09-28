// Trabalho feito por:
// - Gabriel Bosio
// - Eduardo da Rocha Weber

#include <iostream>
#include "SemAdiantamento.h"
#include "ComAdiantamento.h"



int inserirCodigo(lista &codigo, string txt) {
   inicializar(codigo);

   ifstream arquivo;

   arquivo.open(txt + ".txt");

   string instrucao;
   int nInstrucao = 0;

   while (getline(arquivo, instrucao)) {
       inserirFinal(codigo, instrucao);
       nInstrucao++;
   }

   arquivo.close();

   return nInstrucao;
}

void inserirDados(double& tClock, string& arquivo) {

    cout << "\n\nDigite o tempo de clock em nanosegundos: ";
	cin >> tClock;

	cout << "\n\nDigite o nome do arquivo: ";
	cin >> arquivo;
}

void calcularEficiencias(lista codigo, int nI) {

    //Chamar cálculos nas condições com e sem adiantamento
    calcularSemAdiantamento(codigo, nI);
    calcularComAdiantamento(codigo, nI);
}

int main()
{
	double tClock;
    string arquivo;
    lista codigo;

    cout << "||Digite as especificacoes||";

    //cout << "\n\n|Organizacao 1| ";
    inserirDados(tClock, arquivo);

    inserirCodigo(codigo, arquivo);

    //cin.ignore();

    cout << endl << endl << endl;

    return 0;

	// org.cpi = org.ciclosCPU / org.nI;

	// org.tExecucao = org.ciclosCPU * org.tClock;

	// org.desempenho = 1 / org.tExecucao;
}