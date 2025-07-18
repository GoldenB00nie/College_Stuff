#include <bits/stdc++.h>
using namespace std;



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int qntPreenchido, qntParticipantes;
    cin >> qntPreenchido >> qntParticipantes;
 
    map<string, string[3]> participantes;
    for(int i = 0; i < qntPreenchido; i++) {
        string nome;
        cin >> nome;

        for(int j = 0; j < 3; j++) {
            cin >> participantes[nome][j];
        }
    }

    for(int i = 0; i < qntParticipantes; i++) {
        string nome, recebido;
        cin >> nome >> recebido;

        if(!participantes.count(nome)) {
            cout << nome << " queria ganhar qualquer coisa e ganhou " << recebido << "!" << endl;
        }
        else {
            bool ganhouODesejado = false;
            for(string desejados : participantes[nome]) {
                if(desejados == recebido) {
                    ganhouODesejado = true;
                    break;
                }
            }

            if(ganhouODesejado) cout << nome << " conseguiu ganhar " << recebido << "!" << endl;
            else cout << nome << " infelizmente ganhou " << recebido << "..." << endl;
        }
    }
}