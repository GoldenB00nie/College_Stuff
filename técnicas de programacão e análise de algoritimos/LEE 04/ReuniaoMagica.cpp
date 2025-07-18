#include <bits/stdc++.h>
using namespace std;



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int casosTeste;
    cin >> casosTeste;

    for(int i = 0; i < casosTeste; i++) {
        string cartas1, cartas2;
        cin >> cartas1 >> cartas2;
        
        map<char, int> contagemChars;
        for(char c : cartas1) {
            if(!contagemChars.count(c)) contagemChars[c] = 0;
            contagemChars[c]++;
        }

        set<char> cartasIguais;
        for(string::iterator it = cartas2.begin(); it != cartas2.end(); it++)
            if(contagemChars.count(*it) && !cartasIguais.count(*it)) cartasIguais.insert(*it);

        if(cartasIguais.empty()) cout << "Baralhos prontos para o duelo" << endl;
        else {
            for(char c : cartasIguais) {
                cout << c;
            }
            cout << endl;
        }
    }
}