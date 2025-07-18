#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   

    int qntCasosTestes;
    cin >> qntCasosTestes;

    for(int i = 0; i < qntCasosTestes; i++) {
        string palavra1, palavra2;
        cin >> palavra1 >> palavra2;

        unordered_map<char, int> qntLetras1, qntLetras2;
        for(char c : palavra1) qntLetras1[c]++;
        for(char c : palavra2) qntLetras2[c]++;

        if(qntLetras1 == qntLetras2) cout << "ANAGRAMAS" << endl;
        else cout << "DIFERENTES" << endl;
    }
}