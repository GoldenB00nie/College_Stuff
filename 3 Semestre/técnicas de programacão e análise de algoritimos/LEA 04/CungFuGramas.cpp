#include <bits/stdc++.h>
using namespace std;



int main() {
    int qntPalavras;
    cin >> qntPalavras;

    for(int i = 0; i < qntPalavras; i++) {
        string palavra;
        cin >> palavra;

        map<char, int> qntCaracteres;
        bool fraco = false;
        for(char c : palavra) {
            if(!qntCaracteres.count(c)) qntCaracteres[c] = 1;
            else {
                qntCaracteres[c]++;
                if(qntCaracteres[c] > 1) {
                    fraco = true;
                    break;
                }
            }
        }

        if(fraco) cout << "WEAKORD" << endl;
        else cout << "STRONGRAMA" << endl;
    }
}