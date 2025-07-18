#include <bits/stdc++.h>
using namespace std;

struct compare
{
    bool operator()(pair<string, int> a, pair<string, int> b) {
        if(a.second != b.second) {
            return a.second < b.second;
        }
        else return a.first < b.first;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int qntPokemons;
    cin >> qntPokemons;

    priority_queue<pair<string, int>, vector<pair<string, int>>, compare> listaRinha;
    for(int i = 0; i < qntPokemons; i++) {
        string nome;
        int forca;
        cin >> nome >> forca;

        listaRinha.push({nome, forca});
    }

    while(listaRinha.size() >= 2) {
        pair<string, int> poke1 = listaRinha.top();
        listaRinha.pop();
        pair<string, int> poke2 = listaRinha.top();
        listaRinha.pop();

        if(poke1.second == poke2.second) {
            cout << poke1.first << " (" << poke1.second << ") x (" << poke2.second << ") " << poke2.first << " : " << "empate" << endl;
        } else  if(poke1.second > poke2.second) {
            cout << poke1.first << " (" << poke1.second << ") x (" << poke2.second << ") " << poke2.first << " : " << poke1.first << " venceu" << endl;
            poke1.second -= poke2.second;
            listaRinha.push(poke1);
        }
        else {
            cout << poke1.first << " (" << poke1.second << ") x (" << poke2.second << ") " << poke2.first << " : " << poke2.first << " venceu" << endl;
            poke2.second -= poke1.second;
            listaRinha.push(poke2);
        }
    }

    if(listaRinha.size() == 1) {
        cout << listaRinha.top().first << " venceu com " << listaRinha.top().second << endl;
    } else {
        cout << "nenhum vencedor" << endl;
    }
}