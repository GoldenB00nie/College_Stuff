#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;

    queue<int> baralho;
    for (int i = N; i >= 1; --i) {
        baralho.push(i); // Adiciona as cartas ao baralho em ordem decrescente
    }

    vector<int> descartadas;
    while (baralho.size() > 1) {
        // Descarta a carta do topo
        descartadas.push_back(baralho.front());
        baralho.pop();

        // Move a carta do topo para o final
        int carta = baralho.front();
        baralho.pop();
        baralho.push(carta);
    }

    // Imprime as cartas descartadas
    cout << "Descarte: ";
    for (size_t i = 0; i < descartadas.size(); ++i) {
        cout << descartadas[i];
        if (i < descartadas.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;

    // Imprime a última carta
    cout << "Ultima carta: " << baralho.front() << endl;

    return 0;
}
