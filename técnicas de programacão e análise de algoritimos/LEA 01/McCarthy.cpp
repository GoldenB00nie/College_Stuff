#include <iostream>

using namespace std;
long long int calculaCarthy (long long int num);
int main() {
    int casosTeste;
    cin >> casosTeste;

    for (int i = 0; i < casosTeste; i++) {
        long long int num;
        cin >> num;

        cout << calculaCarthy(num) << endl;
    }
}

long long int calculaCarthy (long long int num) {
    if (num > 100) return num - 10;
    else return calculaCarthy(calculaCarthy(num + 11));
}