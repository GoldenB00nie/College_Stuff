#include <bits/stdc++.h>
using namespace std;

//double verificaExpressao(string expressaoMatematica);
bool verificaExpressao(string expressaoMatematica);

int main() {
    string expressaoMatematica;
    cin >> expressaoMatematica;

    if(verificaExpressao(expressaoMatematica)) cout << "OK" << endl;
    else cout << "SyntaxError" << endl;
}

bool verificaExpressao(string expressaoMatematica) {
    vector<char> pilhaParenteses;
    for(int i = 0; i < expressaoMatematica.size(); i++) {
        if(expressaoMatematica[i] == '(' || expressaoMatematica[i] == '[' || expressaoMatematica[i] == '{') {
            pilhaParenteses.insert(pilhaParenteses.begin(), expressaoMatematica[i]);
        }
        else if(expressaoMatematica[i] == ')' || expressaoMatematica[i] == ']' || expressaoMatematica[i] == '}') {
            if(pilhaParenteses.empty()) return false;
            char entradaCorrespondente;
            switch(expressaoMatematica[i]) {
                case ')': entradaCorrespondente = '('; break;
                case ']': entradaCorrespondente = '['; break;
                case '}': entradaCorrespondente = '{'; break;
            }
            if(pilhaParenteses[0] == entradaCorrespondente) pilhaParenteses.erase(pilhaParenteses.begin());
            else return false;
        }
    }
    if(pilhaParenteses.empty()) return true;
    else return false;
}

/*double verificaExpressao(string expressaoMatematica) {
    vector<double> listaNumeros;
    vector<char> listaOperadores;
    for(int i = 0; i < expressaoMatematica.size(); i++) {
        char caractere = expressaoMatematica[i];
        if(caractere >= '0' && caractere <= '9') {
            if(i != 0 && (expressaoMatematica[i-1] >= '0' && expressaoMatematica[i-1] <= '9')) {
                if(!listaNumeros.empty()) listaNumeros[0] = listaNumeros[0] * 10 + (caractere - '0');
            }
            else listaNumeros.insert(listaNumeros.begin(), caractere - '0');
            continue;
        }

        else if(caractere == '*' || caractere == '/' || caractere == '+' || caractere == '-') {
            char proxCaractere = expressaoMatematica[i+1];
            if(i +1 < expressaoMatematica.size() && (proxCaractere == '*' || proxCaractere == '/' || proxCaractere == '+' || proxCaractere == '-')) return NAN;
            listaOperadores.insert(listaOperadores.begin(), caractere);
            continue;
        }

        else if(caractere == '(' || caractere == '[' || caractere == '{') {
            char parentesesSaida;
            switch(caractere) {
                case '(': parentesesSaida = ')'; break;
                case '[': parentesesSaida = ']'; break;
                case '{': parentesesSaida = '}'; break;
            }

            auto it = find(expressaoMatematica.begin() + i, expressaoMatematica.end(), parentesesSaida);
            if(it == expressaoMatematica.end()) return NAN;

            int distParaProximaSaida = distance(expressaoMatematica.begin() + i, it);
            double resultadoParenteses;
            try {
                resultadoParenteses = verificaExpressao(expressaoMatematica.substr(i +1, distParaProximaSaida -1));
            } catch(exception err) {
                return NAN;
            }

            i += distParaProximaSaida;
            if (isnan(resultadoParenteses)) return NAN;
            else {
                listaNumeros.insert(listaNumeros.begin(), resultadoParenteses);
                continue;
            }
        }

        return NAN;
    }

    while(listaNumeros.size() > 1) {
        switch(listaOperadores[0]) {
            case '+': listaNumeros[0] += listaNumeros[1]; break;
            case '-': listaNumeros[0] -= listaNumeros[1]; break;
            case '*': listaNumeros[0] *= listaNumeros[1]; break;
            case '/': if(listaNumeros[1] == 0) return NAN;
                      else {
                        listaNumeros[0] /= listaNumeros[1]; break;
                      }
            default: return NAN;
        }

        listaNumeros.erase(listaNumeros.begin() +1);
        listaOperadores.erase(listaOperadores.begin());
    }

    if(listaNumeros.empty()) return NAN;
    else return listaNumeros[0];
}*/

/*
* Itera sobre todos os elementos,
*   Se o elemento for um numero, 
*       Se ha um numero antes deste,
*           multiplique o primeiro elemento da lista de listaNumeros por 10
*           some o primeiro elemento da lista de listaNumeros pelo numero
*           va para a proxima iteracao
*       senao, 
*           adicione ele ao inicio de uma lista de listaNumeros
*           va para a proxima iteracao
*   Senao, Se o elemento for um operador,
*       Se o proximo elemento for um operador
*           retorne nulo
*       senao, 
*           adicione ele ao inicio de uma lista de listaOperadores
*           va para a proxima iteracao
*   Senao, Se o elemento for um '(' ou '[' ou '{', 
*       pule todos os elementos até o fim do parenteses ')' ou ']' ou '}'
*       Se nao encontrar,
*           retorne nulo
*       cria uma substring contento todos os elementos dentro do parenteses
*       verifica a expressao dessa substring
*       se a substring der um erro, retorne nulo
*       senao, insira o valor encontrado na lista de listaNumeros
*   Senao,
*       Retorne nulo
* 
* Quando terminar de iterar todos os elementos,
*   Enquanto houver mais do que um numero na lista de listaNumeros
*       pegue o primeiro e o segundo elemento da lista e faca a operacao dele
*       iguale esse valor ao primeiro elemento,
*       remova o segundo elemento da lista de listaNumeros
*       remova o primeiro elemento da lista de listaOperadores
*  
* Retorne o primeiro elemento da lista
* (1*[2+2])
* 1*[2+2]
* 2+2
* nums3: 4
* oper3: 
* nums2: 4
* oper2: 
* nums: 4
* oper: 
*
* */