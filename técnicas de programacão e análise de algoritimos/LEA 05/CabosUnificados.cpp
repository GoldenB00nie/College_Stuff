#include<bits/stdc++.h>
using namespace std;

int main() {
    int numCabos;
    cin >> numCabos;

    multiset<int> cabos;
    while(numCabos--) {
        int comprimentoCabo;
        cin >> comprimentoCabo;

        cabos.insert(comprimentoCabo);
    }

    int custo = 0;
    while (cabos.size() > 1) {
            int c1 = *cabos.begin();
            cabos.erase(cabos.begin());
            int c2 = *cabos.begin();
            cabos.erase(cabos.begin());
            custo += max(c1, c2);
            int novo_cabo = c1 + c2;
            cabos.insert(novo_cabo);
        }

    cout << custo << endl;
}