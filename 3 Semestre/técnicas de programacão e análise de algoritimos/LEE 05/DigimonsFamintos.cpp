#include <bits/stdc++.h>
using namespace std;

struct digimon {
    string nome;
    int qntFome;
    int ordemChegada;
    bool naFila;

    digimon() : nome(""), qntFome(0), ordemChegada(0), naFila(false) {}
    digimon(string nome, int qntFome, int ordemChegada) : nome(nome), qntFome(qntFome), ordemChegada(ordemChegada), naFila(true) {}
};

struct compare
{
    bool operator()(digimon a, digimon b) {
        if(a.qntFome != b.qntFome) {
            return a.qntFome < b.qntFome;
        }
        return a.ordemChegada > b.ordemChegada;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int qntAcoes;
    cin >> qntAcoes;

    priority_queue<digimon, vector<digimon>, compare> filaFamintos;
    unordered_map<string, digimon> status;
    int ordemChegada = 0;
    for(int i = 0; i < qntAcoes; i++) {
        string acao;
        cin >> acao;

        if(acao == "CHEGA") {
            string nome;
            int qntFome;
            cin >> nome >> qntFome;

            ordemChegada++;
            digimon temp(nome, qntFome, ordemChegada);
            filaFamintos.push(temp);
            status[nome] = temp;
        } else if(acao == "FOME") {
            string nome;
            int qntFome;
            cin >> nome >> qntFome;

            if(status.count(nome) && status[nome].naFila) {
                status[nome].qntFome += qntFome;
                filaFamintos.push(digimon(status[nome].nome, status[nome].qntFome, status[nome].ordemChegada));
            }
        } else if(acao == "SAI") {
            string nome;
            cin >> nome;

            if(status.count(nome)) status[nome].naFila = false;
        } else {
            while(!filaFamintos.empty()) {
                digimon servido = filaFamintos.top();
                filaFamintos.pop();

                if(status.count(servido.nome) && status[servido.nome].naFila && status[servido.nome].qntFome == servido.qntFome) {
                    cout << servido.nome << endl;
                    status[servido.nome].naFila = false;
                    break;
                }
            }
        }
    }
}