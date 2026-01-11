#include <bits/stdc++.h>

using namespace std;
void leBotao(int* botao) {
    while(true) {
        cout << "Digite 1 ou 0: ";
        cin >> *botao;
        if(*botao == 0 || *botao == 1) break;
        else cout << "Erro na leitura. digite novamente. \n" << endl;
    }
}

int main() {
    int botaoA, botaoB;

    cout << "Ligacao AND:\n" << endl;
    leBotao(&botaoA);
    leBotao(&botaoB);
    if(botaoA && botaoB) cout << "Led ligado" << endl;
    else cout << "Led desligado\n" << endl;

    cout << "Ligacao OR:\n" << endl;
    leBotao(&botaoA);
    leBotao(&botaoB);
    if(botaoA || botaoB) cout << "Led ligado" << endl;
    else cout << "Led desligado\n" << endl;

    cout << "Ligacao NOT:\n" << endl;
    leBotao(&botaoA);
    leBotao(&botaoB);
    if(!botaoA && !botaoB) cout << "Led ligado" << endl;
    else cout << "Led desligado\n" << endl;
}