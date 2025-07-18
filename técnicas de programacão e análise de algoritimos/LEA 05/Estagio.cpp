#include<bits/stdc++.h>
using namespace std;

int main() {
    string strOriginal;
    cin >> strOriginal;

    set<char> letras;
    for(char c : strOriginal) letras.insert(c);

    for(char c : letras) cout << c;
    cout << endl;
}