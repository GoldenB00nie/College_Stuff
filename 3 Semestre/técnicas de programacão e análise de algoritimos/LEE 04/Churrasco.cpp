#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int qntAlunos;
    cin >> qntAlunos;

    set<string> churrasco;
    for(int i = 0; i < qntAlunos; i++) {
        int qntItens;
        cin >> qntItens;

        for(int j = 0; j < qntItens; j++) {
            string item;
            cin >> item;

            if(!churrasco.count(item)) {
                cout << "adicionando " << item << endl;
                churrasco.insert(item);
            }
            else {
                cout << item << " ja tem" << endl;
            }
        }
        cin.ignore();
    }

    cout << "Itens do churrasco:" << endl;
    for(string item : churrasco) {
        cout << item << endl;
    }
}