#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct organizacao {

    string descricao;

    double tClock, cIL = 5, cR = 4, cIA = 4, cS = 4, cB = 3, cJ = 3, cU = 2;

    double ciclosCPU = 0, nI = 0, cpi = 0;

    double tExeceucao, desempenho;
};

double clocksOp(organizacao& org, string tipo) {

    if (tipo == "0000011") { // Formato I load
        return org.cIL;
    }
    else if (tipo == "0110011") { // Formato R
        return org.cR;
    }
    else if (tipo == "0100011") { // Formato S
        return org.cS;
    }
    else if (tipo == "0010011") { // Formato I aritimetica
        return org.cIA;
    }
    else if (tipo == "1100011") { //Formato B
        return org.cB;
    }
    else if (tipo == "1101111") { //Formato J
        return org.cJ;
    }
    else if (tipo == "0110111") { // Formato U;
        return org.cU;
    }
    return 0;
}

void buscarInstrucoes(organizacao& org) {

    ifstream codigo;

    codigo.open("Instrucoes.txt");

    string instrucao;

    while (getline(codigo, instrucao)) {

        org.ciclosCPU += clocksOp(org, instrucao.substr(25));
        org.nI++;
    }

    codigo.close();

    org.cpi = org.ciclosCPU / org.nI;

    org.tExeceucao = org.ciclosCPU * org.tClock;

    org.desempenho = 1 / org.tExeceucao;
}

organizacao requirirOrganizacao() {

    organizacao org;
    double nano;

    cout << "\n\nDigite o nome da nova organizacao: ";
    cin.ignore();
    getline(cin, org.descricao);

    cout << "\n\nDigite o tempo de clock em nanosegundos: ";
    cin >> org.tClock;


    cout << "\n\nCiclos para o formato I artitmetico: ";
    cin >> org.cIA;

    cout << "\n\nCiclos para o formato I load: ";
    cin >> org.cIL;

    cout << "\n\nCiclos para o formato S: ";
    cin >> org.cS;

    cout << "\n\nCiclos para o formato R: ";
    cin >> org.cR;

    cout << "\n\nCiclos para o formato J: ";
    cin >> org.cJ;

    cout << "\n\nCiclos para o formato B: ";
    cin >> org.cB;

    cout << "\n\nCiclos para o formato U: ";
    cin >> org.cU;

    buscarInstrucoes(org);

    return org;
}

void realizarComparacao(organizacao org1, organizacao org2) {

    system("cls");

    cout << "||Comparacao de desempenho baseado no codigo lido||";

    cout << "\n\n---" << org1.descricao << "---";

    cout << "\n\nTempo de clock: " << org1.tClock << " nanosegundos";

    cout << "\n\nCiclos da CPU: " << org1.ciclosCPU;

    cout << "\n\nCPI medio: " << org1.cpi;

    cout << "\n\nTempo de excucao: " << org1.tExeceucao << " nanosegundos";

    cout << "\n\nDesempenho: " << org1.desempenho;




    cout << "\n\n\n\n---" << org2.descricao << "---";

    cout << "\n\nTempo de clock: " << org2.tClock << " nanosegundos";

    cout << "\n\nCiclos da CPU: " << org2.ciclosCPU;

    cout << "\n\nCPI medio: " << org2.cpi;

    cout << "\n\nTempo de excucao: " <<  org2.tExeceucao << " nanosegundos";

    cout << "\n\nDesempenho: " << org2.desempenho;

    cout << "\n\n-----------------------------------";

    double comparacao;

    if (org1.desempenho > org2.desempenho) {
        comparacao = org1.desempenho / org2.desempenho;

        cout << "\n\n" << org1.descricao << " tem " << (comparacao - 1) * 100 << "% de melhor desempenho";
    }
    else {
        comparacao = org2.desempenho / org1.desempenho;

        cout << "\n\n" << org2.descricao << " tem " << (comparacao - 1) * 100 << "% de melhor desempenho";
    }

}

int main()
{
    cout << "||Digite as especificacoes||";

    cout << "\n\n|Organizacao 1| ";
    organizacao org1 = requirirOrganizacao();

    cout << "\n\n|Organizacao 2| ";
    organizacao org2 = requirirOrganizacao();

    realizarComparacao(org1, org2);

    return 0;
}