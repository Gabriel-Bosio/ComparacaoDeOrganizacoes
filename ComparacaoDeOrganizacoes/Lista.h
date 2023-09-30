#pragma once

#include <string>
#include <fstream>

using namespace std;

struct no {
    string instrucao;
    no* anterior;
    no* posterior;
};

struct lista {
    no* inicio;
    no* fim;
};

void inicializar(lista& codigo) {
    codigo.inicio = NULL;
    codigo.fim = NULL;
}

void inserirFinal(lista& codigo, string instrucao) {

    no* novo = new no;
    novo->instrucao = instrucao;
    novo->anterior = NULL;
    novo->posterior = NULL;


    if (codigo.inicio == NULL) {
        codigo.inicio = novo;
    }
    else {
        codigo.fim->posterior = novo;
        novo->anterior = codigo.fim;
        codigo.fim = novo;
    }
}

void inserirNOP(no* instrucao) {
    no* novo = new no;
    novo->instrucao = "00000000000000000000000000010011";
    novo->anterior = instrucao->anterior;
    novo->posterior = instrucao;
    instrucao->anterior = novo;
}

void reordenar(no* hazard, no* escolhido) {

    escolhido->posterior->anterior = escolhido->anterior;
    escolhido->anterior->posterior = escolhido->posterior;

    escolhido->posterior = hazard->posterior;
    escolhido->posterior->anterior = escolhido;

    hazard->posterior = escolhido;
    escolhido->anterior = hazard;
}

void salvarCodigo(lista& codigo, string nome_arquivo) {
	no* instNo = codigo.inicio;

    ofstream arquivo;

	arquivo.open(nome_arquivo + ".txt");
    arquivo.clear();

    while (instNo != NULL) {
        arquivo << instNo->instrucao;
		instNo = instNo->posterior;
    }

    arquivo.close();
}

int contarInstrucao(lista& codigo) {
	no* instNo = codigo.inicio;
    int nI = 0;

	while (instNo != NULL) {
        nI++;
		instNo = instNo->posterior;
	}
    return nI;
}