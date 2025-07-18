#include<bits/stdc++.h>
using namespace std;

struct comparador {
    bool operator()(pair<string, int> a, pair<string, int> b) {
        if(a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    }
};

int main() {
    int numDetentos;
    cin >> numDetentos;

    priority_queue<pair<string, int>, vector<pair<string, int>>, comparador> filaTelefone;
    while(numDetentos--) {
        string nomeDetento;
        int tempoTelefone;
        cin >> nomeDetento >> tempoTelefone;

        filaTelefone.push({nomeDetento, tempoTelefone});
    }

    for(int i = 0; filaTelefone.size() != 0; i++) {
        cout << filaTelefone.top().first << " " << filaTelefone.top().second << endl;
        if(filaTelefone.top().second / 2 != 0) filaTelefone.push({filaTelefone.top().first, filaTelefone.top().second / 2});
        filaTelefone.pop();
    }
}