#include <bits/stdc++.h>
using namespace std;

int main() {
    int qntEnderecos, qntChaves;
    cin >> qntEnderecos >> qntChaves;

    unordered_map<int, vector<int>> todasChaves;
    for(int i = 0; i < qntChaves; i++) {
        int numChave;
        cin >> numChave;

        int pos = numChave % qntEnderecos;
        todasChaves[pos].push_back(numChave);
    }

    for(int i = 0; i < qntEnderecos; i++) {
        cout << i << " -> ";
        if(todasChaves.count(i)) for(int j : todasChaves[i]) {
            cout << j << " -> ";
        }
        cout << "\\" << endl;
    }
}