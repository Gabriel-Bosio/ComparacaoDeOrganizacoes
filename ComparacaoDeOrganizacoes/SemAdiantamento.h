#pragma once

#include "Lista.h";

bool verificarRD(string instrucao, string rs1, string rs2) {
    string tipo = instrucao.substr(25);
    if (tipo == "0000011" || tipo == "0110011" || tipo == "0010011" || tipo == "1101111" || tipo == "0110111")
        if (instrucao.substr(20, 5) == rs1 || instrucao.substr(20, 5) == rs2)
            return 1;
    return 0;
}

bool verificarRD(string instrucao) {
    string tipo = instrucao.substr(25);
    if (tipo == "0000011" || tipo == "0110011" || tipo == "0010011" || tipo == "1101111" || tipo == "0110111")
        return 1;
    return 0;
}

void capturarRS(string instrucao, string& rs1, string& rs2) {
    string opcode = instrucao.substr(25);
    if (opcode == "0110011" || opcode == "1100011" || opcode == "0100011") {
        rs1 = instrucao.substr(12, 16);
        rs2 = instrucao.substr(7, 11);
    }
    else if (opcode == "0000011" || opcode == "0010011") {
        rs1 = instrucao.substr(12, 16);
        rs2 = " ";
    }
    else {
        rs1 = " ";
        rs2 = " ";
    }
}

void implementarNOPs(lista& codigo) {

    string rs1, rs2;

    no* instNo = codigo.fim;

    while (instNo != NULL) {
        capturarRS(instNo->instrucao, rs1, rs2);
        if (!(rs1 == " " && rs2 == " ")) {
            if (verificarRD(instNo->anterior->instrucao, rs1, rs2)) {
                inserirNOP(instNo);
                inserirNOP(instNo);
            }
            else if (verificarRD(instNo->anterior->anterior->instrucao, rs1, rs2)) {
                inserirNOP(instNo);
            }
            else if (instNo->instrucao.substr(25) == "1101111" || instNo->instrucao.substr(25) == "1100111") {
                if (verificarRD(instNo->anterior->instrucao))
                    inserirNOP(instNo);
            }
        }
        instNo = instNo->anterior;
    }
}

void reordenarCodigo(lista& codigo) {

}

void calcularNaoReordenando(lista codigo, int nI) {

    //organizar codigo, salvar em arquivo e exibir resultado do cálculo de eficiência
}

void calcularReordenando(lista codigo, int nI) {
    //organizar codigo, salvar em arquivo e exibir resultado do cálculo de eficiência
}

void calcularSemAdiantamento(lista codigo, int nI) {
    
    //Chamar cálculos nas condições de sem e com reordenacao
    calcularNaoReordenando(codigo, nI);
    calcularReordenando(codigo, nI);
}