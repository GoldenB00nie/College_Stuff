#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int poste1, poste2, peso;

    bool operator<(const Edge& other) const {
        return peso < other.peso;
    }
};

struct DSU {
    vector<int> pai;

    DSU(int n) {
        pai.resize(n + 1);
        iota(pai.begin(), pai.end(), 0);
    }

    int find(int i) {
        if (pai[i] == i)
            return i;
        return pai[i] = find(pai[i]); 
    }

    bool unir(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            pai[root_i] = root_j;
            return true;
        }
        return false;
    }
};

int main() {
    int casosTeste;
    cin >> casosTeste;
    while (casosTeste--) {
        int numPostes, qntParesPostes;
        cin >> numPostes >> qntParesPostes;
        vector<Edge> edges;
        for (int i = 0; i < qntParesPostes; ++i) {
            int par1, par2, distPares;
            cin >> par1 >> par2 >> distPares;
            edges.push_back({par1, par2, distPares});
        }

        sort(edges.begin(), edges.end());
        DSU dsu(numPostes);
        long long minTotalFio = 0;
        int edgesEmMST = 0;
        for (const auto& edge : edges) {
            if (dsu.unir(edge.poste1, edge.poste2)) {
                minTotalFio += edge.peso;
                edgesEmMST++;
                if (edgesEmMST == numPostes - 1) {
                    break; 
                }
            }
        }
        
        cout << minTotalFio << endl;
    }
}