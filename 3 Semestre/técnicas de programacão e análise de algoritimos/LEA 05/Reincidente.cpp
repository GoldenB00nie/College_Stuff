#include<bits/stdc++.h>
using namespace std;

int main() {
    string nomeDetido = "";
    int numArtigo = 2;
    unordered_map<string, int> detidos;
    while(nomeDetido != "fim" && numArtigo != 0) {
        cin >> nomeDetido >> numArtigo;
        if(nomeDetido == "fim" && numArtigo == 0) break;

        detidos[nomeDetido]+= 1;
        if(detidos[nomeDetido] == 1) cout << nomeDetido << " eh reu primario" << endl;
        else cout << nomeDetido << " eh reincidente com " << detidos[nomeDetido] -1 << " crime(s)" << endl;
    }
}