#include <iostream>
#include <cmath>
using namespace std;

bool numEhPrimo (long long int numVerificar);
int main () {
    int qntNums;
    cin >> qntNums;
    for (int i = 0; i < qntNums; i++) {
        long long int numVerificar;
        cin >> numVerificar;

        if (numEhPrimo(numVerificar)) cout << "o numero " << numVerificar << " eh primo" << endl;
        else cout << "o numero " << numVerificar << " nao eh primo" << endl;
    }
}

bool numEhPrimo (long long int numVerificar) {
    if (numVerificar == 1) return false;
    double square = sqrt(numVerificar);
    for (int i = 2; i <= square; i++) {
        if (numVerificar % i == 0) return false;
    }

    return true;   
}