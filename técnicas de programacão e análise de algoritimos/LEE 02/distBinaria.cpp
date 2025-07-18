#include <iostream>
using namespace std;

int distHamming(long long int num1, long long int num2);
int main() {
    int casosTeste;
    long long int num1, num2;
    cin >> casosTeste;

    for(int i = 0; i < casosTeste; i++) {
        cin >> num1 >> num2;
        cout << distHamming(num1, num2) << endl;
    }
}

int distHamming(long long int num1, long long int num2) {
    long long int x = num1 ^ num2;
    int distHamming = 0;

    while(x > 0) {
        distHamming += x & 1;
        x >>= 1;
    }

    return distHamming;
}