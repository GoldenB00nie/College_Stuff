#include <iostream>
using namespace std;

long long int calculaNum3(long long int num1, long long int num2, long long int res);

int main() {
    int casosTeste;
    cin >> casosTeste;

    for(int i = 0; i < casosTeste; i++) {
        long long int num1, num2, res;
        cin >> num1 >> num2 >> res;
        cout << calculaNum3(num1, num2, res) << endl;
    }
}

long long int calculaNum3(long long int num1, long long num2, long long int res) {
    long long int num3 = res & ~(num1 | num2);
    if(res != (num1 | num2 | num3)) return -1;
    else return num3;
}