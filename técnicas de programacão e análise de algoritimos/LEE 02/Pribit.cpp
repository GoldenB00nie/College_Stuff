#include<iostream>
#include<cmath>
using namespace std;

bool EhPribit(long long numAhVerificar);
int main() {
    unsigned int casosTeste;
    cin >> casosTeste;

    long long numAhVerificar;
    for(unsigned int i = 0; i < casosTeste; i++) {
        cin >> numAhVerificar;
        if(EhPribit(numAhVerificar)) cout << numAhVerificar << " eh um pribit" << endl;
        else cout << numAhVerificar << " nao eh um pribit" << endl;
    }
}

bool EhPribit(long long numAhVerificar) {
    short soma = 0;
    while(numAhVerificar != 0) {
        soma += numAhVerificar & 1;
        numAhVerificar >>= 1;
    }

    if(soma == 1) return false;
    for(int i = 2; i < soma; i++) if(soma % i == 0) return false;
    return true;
}