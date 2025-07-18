#include <iostream>
using namespace std;

int SomaDivisao(string numero);
int main()
{
    int d;
    string numero;
    while(true)
    {
        cin >> d;
        if (d == -1)    break;

        cin >> numero;
        int somaFinal = SomaDivisao(numero);
        cout << somaFinal;
        if (somaFinal % 3 == 0)
            cout << " sim" << endl;
        else
            cout << " nao" << endl;
    }
}

int SomaDivisao(string numero) {
    int soma = 0;
    for (char c : numero) {
        soma += c - '0';  // Converte caractere numérico para inteiro e soma
    }
    return soma;
}