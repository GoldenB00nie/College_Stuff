#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Função a ser resolvida: f(x) = Ax + B*sin(x) - C
double f(double x, double A, double B, double C) {
    return A * x + B * sin(x) - C;
}

// Derivada da função: f'(x) = A + B*cos(x)
double f_linha(double x, double A, double B) {
    return A + B * cos(x);
}

int main() {
    double A, B, C;
    cin >> A >> B >> C;

    // Inicialização do valor de x (chute inicial)
    double x0 = C / A; // Uma boa estimativa inicial

    // Precisão desejada
    double epsilon = 1e-5; // 0.00001

    // Número máximo de iterações para evitar loops infinitos
    int max_iteracoes = 100;

    double x = x0;
    for (int i = 0; i < max_iteracoes; ++i) {
        double fx = f(x, A, B, C);
        double f_linha_x = f_linha(x, A, B);

        // Verificando se a derivada é zero para evitar divisão por zero
        if (fabs(f_linha_x) < epsilon) {
            break; // Se a derivada for muito próxima de zero, interrompe
        }

        // Método de Newton-Raphson: x_{n+1} = x_n - f(x_n) / f'(x_n)
        double x_novo = x - fx / f_linha_x;

        // Critério de parada: quando a diferença entre x_novo e x é menor que epsilon
        if (fabs(x_novo - x) < epsilon) {
            x = x_novo;
            break;
        }

        x = x_novo;
    }

    // Imprime o resultado com 4 casas decimais
    cout << fixed << setprecision(4) << x << endl;

    return 0;
}
