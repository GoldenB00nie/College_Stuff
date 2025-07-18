#include <bits/stdc++.h>
using namespace std;

int main() {
    queue<string> voosNorte, voosSul, voosLeste, voosOeste;
    queue<string>* filaSelecionada;
    string entrada;
    while(true) {
        cin >> entrada;
        switch(entrada[0]) {
            case 'N': filaSelecionada = &voosNorte; break;
            case 'S': filaSelecionada = &voosSul; break;
            case 'L': filaSelecionada = &voosLeste; break;
            case 'O': filaSelecionada = &voosOeste; break;
            case 'B': filaSelecionada->push(entrada); break;
            case '0': goto Processamento;
        }
    }

    Processamento: 
    vector<queue<string>*> filasVoos = {&voosNorte, &voosSul, &voosLeste, &voosOeste};
    bool primeiro = true;
    while(!voosNorte.empty() || !voosSul.empty() || !voosLeste.empty() || !voosOeste.empty()) {
        for(auto* fila : filasVoos) {
            if(!fila->empty()) {
                if(!primeiro) cout << " ";
                cout << fila->front();
                fila->pop();
                primeiro = false;
            }
        }
    }
}