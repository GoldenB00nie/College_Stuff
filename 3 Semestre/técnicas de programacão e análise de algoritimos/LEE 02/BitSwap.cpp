#include<iostream>
using namespace std;

unsigned long long trocarBit(unsigned long long numAhModificar, short posInicial, short posFinal);
int main() {
    short casosTeste;
    cin >> casosTeste;

    unsigned long long numAhModificar;
    short posInicial, posFinal;
    for(int i = 0; i < casosTeste; i++) {
        cin >> numAhModificar >> posInicial >> posFinal;
        cout << trocarBit(numAhModificar, posInicial, posFinal) << endl;
    }
}

unsigned long long trocarBit(unsigned long long numAhModificar, short posInicial, short posFinal) {
    short numPosInicial = (numAhModificar >> posInicial) & 1;
    short numPosFinal = (numAhModificar >> posFinal) & 1;
    
    if(numPosInicial != numPosFinal) {
        numAhModificar = numAhModificar ^ ((unsigned long long)(1) << posInicial | (unsigned long long)(1) << posFinal);
    }
    return numAhModificar;
}