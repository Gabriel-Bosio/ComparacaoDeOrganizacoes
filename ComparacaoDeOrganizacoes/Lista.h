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

void reordenar(no* inst1, no* inst2) {
    no *tempA, *tempP;

    tempA = inst1->anterior;
    tempP = inst1->posterior;

    inst1->anterior = inst2->anterior;
    inst1->posterior = inst2->posterior;

    inst2->anterior = tempA;
    inst2->posterior = tempP;
}