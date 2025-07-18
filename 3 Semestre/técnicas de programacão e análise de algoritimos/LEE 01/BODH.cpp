#include <iostream>
using namespace std;

string ConverteBase(long long int num, int base);
int main () {
    long long int num;
    int base;
    string resposta;
    while (true) {
        cin >> num >> base;
        if (num == -1 && base == -1) exit(0);
        if (num < 0 || base < 2 || base > 16) {
            cout << "Número fora do intervalo esperado." << endl;
            exit(1);
        }
        resposta = ConverteBase(num, base);
        cout << resposta << endl;
    }
}

string ConverteBase(long long int num, int base) {
    string byte = "00000000";
    string numero;
    for (int i = 0; i < 8; i++) numero.append(byte);
    int bit;
    switch (base)
    {
        case 2:     for (int pos = numero.length() - 1; pos >= 0; pos--) {
                        bit = num % 2;
                        numero[pos] = bit + '0';
                        num /= 2;
                    }
                    break;
        case 8:     for (int pos = numero.length() - 1; pos >= 0; pos--) {
                        bit = num % 8;
                        numero[pos] = bit + '0';
                        num /= 8;
                    }
                    break;
        case 10:    return to_string(num);
        case 16:    for (int pos = numero.length() - 1; pos >= 0; pos--) {
                        bit = num % 16;
                        if (bit < 10) numero[pos] = bit + '0';
                        else numero[pos] = bit - 10 + 'A';
                        num /= 16;
                    }
                    break;
        default:    cout << "Base inválida.";
                    return "";
    }
    int i = 0;
    while (numero[i] == '0' && i < numero.length() - 1) {
        i++;
    }
    return numero.substr(i); 
}