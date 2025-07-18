#include <bits/stdc++.h>
using namespace std;

struct jogador {
    string nick, tempo;
    int tempoSegundos;
};

bool comparaJogadores(const jogador& a, const jogador& b);

int main() {
    int numJogadores;
    cin >> numJogadores;

    vector<jogador> jogadores(numJogadores);
    for(int i = 0; i < numJogadores; i++) {
        cin >> jogadores[i].nick >> jogadores[i].tempo;
        jogadores[i].tempoSegundos = stoi(jogadores[i].tempo.substr(0, 2)) * 60 + stoi(jogadores[i].tempo.substr(3, 2));
    }

    sort(jogadores.begin(), jogadores.end(), comparaJogadores);

    for(int ranking = 1; ranking < jogadores.size() +1; ranking++) {
        cout << ranking << ". " << jogadores[ranking -1].tempo + " - " << jogadores[ranking -1].nick << endl;
    }
}

bool comparaJogadores(const jogador& a, const jogador& b) {
    if(a.tempoSegundos != b.tempoSegundos) return a.tempoSegundos > b.tempoSegundos;
    else return a.nick > b.nick;
}