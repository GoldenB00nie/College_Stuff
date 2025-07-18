#include <bits/stdc++.h>
using namespace std;

int main() {
    int blocosPedra; // casos teste
    cin >> blocosPedra;

    string pedras;
    for(int i = 0; i < blocosPedra; i++) {
        cin >> pedras;

        int countPreciosas = 0;
        stack<char> preciosas;
        for(int pos = 0; pos < pedras.length(); pos++) {
            if(pedras[pos] != '<' && pedras[pos] != '>') continue;
            if(pedras[pos] == '<') preciosas.push('<');
            else if(!preciosas.empty()) {
                preciosas.pop();
                countPreciosas++;
            }
        }

        cout << countPreciosas << endl;
    }
}