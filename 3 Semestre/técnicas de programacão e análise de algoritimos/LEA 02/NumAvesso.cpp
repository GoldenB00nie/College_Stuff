#include<iostream>
using namespace std;

unsigned int calculaAvesso(unsigned int numeroAhVerificar);
int main() {
    unsigned int numeroAhVerificar;
    cin >> numeroAhVerificar;
    cout << calculaAvesso(numeroAhVerificar) << endl;
}

unsigned int calculaAvesso(unsigned int numeroAhVerificar) {
    unsigned int numeroDoAvesso = 0;
    int posBit;
    for(posBit = 1; numeroAhVerificar != 0; posBit++) {
        numeroDoAvesso += (numeroAhVerificar & 1);
        numeroAhVerificar >>= 1;
        if(numeroAhVerificar == 0) break;
        numeroDoAvesso <<= 1;
    }
    numeroDoAvesso <<= 32 - (posBit);
    return numeroDoAvesso;
}