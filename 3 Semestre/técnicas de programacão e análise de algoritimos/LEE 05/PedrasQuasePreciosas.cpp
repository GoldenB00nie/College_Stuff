#include <bits/stdc++.h>
using namespace std;

int main() {
    int casosTeste;
    cin >> casosTeste;

    for(int i = 0; i < casosTeste; i++) {
        string pedras, negociaveis;
        cin >> pedras >> negociaveis;

        map<char, int> contagem;
        for(char c : pedras) {
            if(!contagem.count(c)) contagem[c] = 0;
            contagem[c] += 1;
        }

        int qntContada = 0;
        set<char> explorados;
        for(char c : negociaveis) {
            if(!explorados.count(c))  {
                qntContada += contagem[c];
                explorados.insert(c);
            }
        }

        cout << "Contem " << qntContada << " pedras negociaveis" << endl;
    }
}