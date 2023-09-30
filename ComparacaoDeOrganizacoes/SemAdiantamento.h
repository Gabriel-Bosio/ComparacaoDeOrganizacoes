#pragma once

#include "Lista.h";

string capturarRD(string instrucao) {
    string tipo = instrucao.substr(25);
    if (tipo == "0000011" || tipo == "0110011" || tipo == "0010011" || tipo == "1101111" || tipo == "0110111")
        return instrucao.substr(20,5);
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
    if (opcode == "0000011" || opcode == "0110011" || opcode == "0010011" || opcode == "1101111" || opcode == "0110111") {
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
            else if (verificarJal(instNo)){
                inserirNOP(instNo->posterior->posterior);
            }
        }
        instNo = instNo->posterior;
    }
}

bool verificarRD(string instrucao, string rs1, string rs2) {
    
    string opcode = instrucao.substr(25);
    string rd = instrucao.substr(50, 5);

    if (opcode != "0100011") {
        if (rd == rs1 || rd == rs2)
            return 1;
    }
    return 0;
}

bool verificarRD(string instrucao, string rs1) {

    string opcode = instrucao.substr(25);
    string rd = instrucao.substr(50, 5);

    if (opcode != "0100011") {
        if (rd == rs1)
            return 1;
    }
    return 0;
}

bool validarReordenacao(no* hazard, no* escolhido) {

    string opcode = escolhido->instrucao.substr(25);
    string rd = escolhido->instrucao.substr(20, 5);
    string rs1 = escolhido->instrucao.substr(12, 16);
    string rs2 = escolhido->instrucao.substr(7, 11);

    no* temp = hazard;

    while (temp != escolhido) {
        if (opcode != "0100011" && verificarRS(temp->instrucao, rd)) {
            return 0;
        }
        if (opcode == "0110011" || opcode == "1100011" || opcode == "0100011") {
            if (!verificarRD(temp->instrucao, rs1, rs2))
                return 0;
        }
        else if (opcode == "0000011" || opcode == "0010011") {
            if (!verificarRD(temp->instrucao, rs1))
                return 0;
        }
    }
    return 1;
}

no* procurarInstrucao(no* hazard, string rd) {
    
    no* temp = hazard->posterior;
        string opcode;
    
    while (temp != NULL) {
        
        opcode = temp->instrucao.substr(25);
        if (opcode == "1101111" || opcode == "1100111" || opcode == "1100011")
            return NULL;
        if (!verificarRS(temp->instrucao, temp->instrucao.substr(20,5))) {
            if (validarReordenacao(hazard, temp))
                return temp;
        }
    }
    return NULL
}

void reordenarCodigo(lista& codigo) {
    
    string rd;

    
    no* instNo = codigo.inicio, *escolhido;

    while (instNo != NULL) {
        capturarRD(instNo->instrucao);
        if (rd != " ") {
            if (verificarRS(instNo->posterior->instrucao, rd)) {
                escolhido = procurarInstrucao(instNo, rd);
                if (escolhido != NULL)
                    reordenar(instNo, escolhido);
                escolhido = procurarInstrucao(instNo->posterior, rd);
                if (escolhido != NULL)
                    reordenar(instNo->posterior, escolhido);
            }
            else if (verificarRS(instNo->posterior->posterior->instrucao, rd)) {
                escolhido = procurarInstrucao(instNo->posterior, rd);
                if (escolhido != NULL)
                    reordenar(instNo->posterior, escolhido);
            }
        }
        instNo = instNo->posterior;
    }

}

void calcularNaoReordenando(lista codigo, double tClock, string nome_arquivo) {
    implementarNOPs(codigo);
    string arquivo = nome_arquivo + " Sem Adiantamenento não Reordenado";
    salvarCodigo(codigo, arquivo);

    int nI = contarInstrucao(codigo);

    double CicloCPU = 5 + 1 * (nI - 1);
    double tExecucao = CicloCPU * tClock;
    double desempenho = 1 / tExecucao;

    // reordenarCodigo, implementarNOPs, salvarArquivo, calcular CPI

    //organizar codigo, salvar em arquivo e exibir resultado do cálculo de eficiência
}

void calcularReordenando(lista codigo, double tClock, string nome_arquivo) {
    //organizar codigo, salvar em arquivo e exibir resultado do cálculo de eficiência
}

void calcularSemAdiantamento(lista codigo, double tClock, string nome_arquivo) {
    
    //Chamar cálculos nas condições de sem e com reordenacao
    calcularNaoReordenando(codigo, tClock, nome_arquivo);
    calcularReordenando(codigo, tClock, nome_arquivo);
}