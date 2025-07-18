#include <bits/stdc++.h>
using namespace std;

const int INF = numeric_limits<int>::max();
vector<int> dijkstra(int pontosAcesso, const vector<vector<int>>& prisao, int start_node, const set<int>& posDasCameras, bool ignore_cameras);
int main() {
    int pontosAcesso, qntCorredores, qntCameras;
    cin >> pontosAcesso >> qntCorredores >> qntCameras;

    set<int> posDasCameras;
    for(int i = 0; i < qntCameras; i++) {
        int posCamera;
        cin >> posCamera;

        posDasCameras.insert(posCamera);
    }

    vector<vector<int>> prisao (pontosAcesso +1);
    for(int i = 0; i < qntCorredores; i++) {
        int corredorAcessoA, corredorAcessoB;
        cin >> corredorAcessoA >> corredorAcessoB;

        prisao[corredorAcessoA].push_back(corredorAcessoB);
        prisao[corredorAcessoB].push_back(corredorAcessoA);
    }

    int posPatio, posPortaSaida, posChave;
    cin >> posPatio >> posPortaSaida >> posChave;

    if(posDasCameras.count(posChave) || posDasCameras.count(posPatio)) {
        cout << "impossivel fugir" << endl;
        return 0;
    }

    vector<int> dist_E_to_all_no_cameras = dijkstra(pontosAcesso, prisao, posPatio, posDasCameras, false);
    vector<int> dist_K_to_all_no_cameras = dijkstra(pontosAcesso, prisao, posChave, posDasCameras, false);
    long long your_path_distance = -1;
    if (dist_E_to_all_no_cameras[posChave] != INF && dist_K_to_all_no_cameras[posPatio] != INF) {
        your_path_distance = (long long)dist_E_to_all_no_cameras[posChave] + dist_K_to_all_no_cameras[posPatio];
    }

    vector<int> dist_E_to_all_ignoring_cameras = dijkstra(pontosAcesso, prisao, posPatio, posDasCameras, true);
    int mass_escape_distance = dist_E_to_all_ignoring_cameras[posPortaSaida];
    if (your_path_distance == -1 || mass_escape_distance == INF) {
        cout << "impossivel fugir" << endl;
    } else {
        cout << your_path_distance << " " << mass_escape_distance << endl;
    }
}

vector<int> dijkstra(int pontosAcesso, const vector<vector<int>>& prisao, int start_node, const set<int>& posDasCameras, bool ignore_cameras) {
    vector<int> dist(pontosAcesso + 1, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[start_node] = 0;
    pq.push({0, start_node});
    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (d > dist[u]) {
            continue;
        }

        if (!ignore_cameras && posDasCameras.count(u) && u != start_node) {
            continue;
        }

        for (int v : prisao[u]) {
            if (!ignore_cameras && posDasCameras.count(v)) {
                continue;
            }

            if (dist[u] + 1 < dist[v]) {
                dist[v] = dist[u] + 1;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}