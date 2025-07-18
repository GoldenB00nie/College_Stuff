#include<iostream>
#include<vector>

using namespace std;
int encontraAbandonado (vector<int> numeros);
int main () {
    while (true) {
        int casosTeste;
        cin >> casosTeste;
        if (casosTeste == -1) break;
        
        vector<int> numeros;
        for (int i = 0; i < casosTeste; i++) {
            int num;
            cin >> num;
            numeros.push_back(num);
        }

        cout << encontraAbandonado(numeros) << endl;
    }
}

int encontraAbandonado (vector<int> numeros) {
    int i = 0;
    for (int pos = 0; pos < numeros.size(); pos++) {
        i ^= numeros[i];
    }
    return i;
}