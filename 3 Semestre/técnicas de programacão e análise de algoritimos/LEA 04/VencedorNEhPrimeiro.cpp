#include <bits/stdc++.h>
using namespace std;



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int qntPessoas, rankingSorteado;
    cin >> qntPessoas >> rankingSorteado;

    set<int> cadeiras;
    for(int i = 0; i < qntPessoas; i++) {
        int temp;
        cin >> temp;
        cadeiras.insert(temp);
        
        set<int>::iterator it = cadeiras.begin();
        if(cadeiras.size() < rankingSorteado) {
            advance(it, cadeiras.size() -1);
            cout << *it << endl;
        }
        else {
            advance(it, rankingSorteado -1);
            cout << *it << endl;
        }
    }
}