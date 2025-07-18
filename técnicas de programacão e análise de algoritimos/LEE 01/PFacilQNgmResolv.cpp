#include <iostream>
using namespace std;

long long int calculaProx (long long int num);
int main () {
    long long int num;
    cin >> num;

    while (num != 1) {
        cout << num << " ";
        num = calculaProx(num);
    }
    cout << num << endl;
}

long long int calculaProx (long long int num) {
    if (num % 2 == 0) return num / 2;
    else return 3 * num + 1;
}