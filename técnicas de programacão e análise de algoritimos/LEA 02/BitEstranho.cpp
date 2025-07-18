#include <iostream>
using namespace std;

long long ativarBitNum(long long num, unsigned short posBitAtivar);
int main() {
   int casosTeste;
   unsigned short posBitAtivar;
   
    cin >> casosTeste >> posBitAtivar;

    long long num;
    for(int i = 0; i < casosTeste; i++) {
        cin >> num;
        cout << ativarBitNum(num, posBitAtivar) << endl;
    }
}

long long ativarBitNum(long long num, unsigned short posBitAtivar) {
    return (num & ~(1 << posBitAtivar));
}