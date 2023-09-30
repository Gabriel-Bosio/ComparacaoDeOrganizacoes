#pragma once
#pragma once

#include "Lista.h";

string capturarRD(string instrucao) {
    string tipo = instrucao.substr(25);
    if (tipo == "0000011")
        return instrucao.substr(20, 5);
    return " ";
}

bool verificarRS(string instrucao, string rd) {
    string opcode = instrucao.substr(25);
    if (opcode == "0110011" || opcode == "1100011" || opcode == "0100011") {
        if (rd == instrucao.substr(12, 16) || rd == instrucao.substr(7, 11))
            return 1;
    }
    else if (opcode == "0000011" || opcode == "0010011") {
        if (rd == instrucao.substr(12, 16))
            return 1;
    }
    return 0;
}

bool verificarJal(no* instNo) {
    string opcode = instNo->instrucao.substr(25);
    if (opcode == "0000011") {
        opcode = instNo->posterior->instrucao.substr(25);
        if (opcode == "1101111" || opcode == "1100111")
            return 1;
    }
    return 0;
}

void implementarNOPs(lista& codigo) {

    string rd;

    no* instNo = codigo.inicio;

    while (instNo != NULL) {
        capturarRD(instNo->instrucao);
        if (rd != " ") {
            if (verificarRS(instNo->posterior->instrucao, rd)) {
                inserirNOP(instNo->posterior);
                inserirNOP(instNo->posterior);
            }
            else if (verificarRS(instNo->posterior->posterior->instrucao, rd)) {
                inserirNOP(instNo->posterior->posterior);
            }
            else if (verificarJal) {
                inserirNOP(instNo->posterior->posterior);
            }
        }
        instNo = instNo->posterior;
    }
}

void reordenarCodigo(lista& codigo) {

}

void calcularNaoReordenando(lista codigo) {
    //organizar codigo, salvar em arquivo e exibir resultado do cálculo de eficiência
}

void calcularReordenando(lista codigo) {
    //organizar codigo, salvar em arquivo e exibir resultado do cálculo de eficiência
}

void calcularComAdiantamento(lista codigo) {
    
    //Chamar cálculos nas condições de sem e com reordenacao
    calcularNaoReordenando(codigo);
    calcularReordenando(codigo);
}