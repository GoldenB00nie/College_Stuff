    #include <bits/stdc++.h>
    using namespace std;
     
    int main() {
        int numDigitos = 0;
        while(true) {
            cin >> numDigitos;
            if(numDigitos == -1) break;
            
            long long somaPositivo = 0, somaNegativo = 0;
            bool sinal = true;
            vector<char> numero;
            for(int i = 0; i < numDigitos; i++) {
                char num;
                cin >> num;

                numero.push_back(num);
                if(sinal) somaPositivo += num -'0';
                else somaNegativo += num -'0';
                sinal = !sinal;
            }

            int res = somaPositivo - somaNegativo;

            for(char c : numero) cout << c;
            cout << ": " << somaPositivo << " - " << somaNegativo << " = " << res << " - ";
    
            if(res % 11 == 0) cout << "sim" << endl;
            else cout << "nao" << endl;
        }
    }