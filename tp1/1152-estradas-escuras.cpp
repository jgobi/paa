#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
 
using namespace std;

const int maxv = 200000;

vector<int> arestas[maxv + 5];
vector<int> pesos[maxv + 5];
int dist[maxv + 5];
int marca[maxv + 5];

void limpa_grafo(int n_vertices) {
    memset(marca, 0, sizeof(marca[0]) * n_vertices);
    for (int i = 0; i < n_vertices; i++) {
        arestas[i].clear();
        pesos[i].clear();
        dist[i] = -1; // infinito
    }
}

// retorna soma do peso de todas as arestas do grafo
int recebe_arestas(int n_arestas) {
    int soma_p = 0;

    for (int i = 0; i < n_arestas; i++) {
        int u, v, p;
        cin >> u >> v >> p;

        arestas[u].push_back(v);
        pesos[u].push_back(p);
        arestas[v].push_back(u);
        pesos[v].push_back(p);

        soma_p += p;
    }

    return soma_p;
}

// retorna soma do peso de todas as arestas de uma AGM do grafo
int prim_v(int n_vertices) {
    int soma_pesos = 0;

    priority_queue<pair<int, int>> q; // -distancia, n_vertice
    q.push(make_pair(0, 0)); // coloca o primeiro vértice na fila

    while (!q.empty()) {
        int d_v, v;

        do {
            pair<int, int> q_top = q.top();
            d_v = -q_top.first;
            v = q_top.second;
            q.pop();
        } while (marca[v] && !q.empty());

        // não encontrou desmarcado, fila vazia, fim do algoritmo.
        if (marca[v]) break;

        soma_pesos += d_v;
        marca[v] = 1;

        for (int i = 0; i < arestas[v].size(); i++) {
            int w = arestas[v][i];
            int p_vw = pesos[v][i];
            if (!marca[w] && (dist[w] == -1 || dist[w] > p_vw)) {
                dist[w] = p_vw;
                q.push(make_pair(-dist[w], w));
            }
        }
    }

    return soma_pesos;
}

int main() {
    int n_vertices;
    int n_arestas;
    while(1) {
        cin >> n_vertices >> n_arestas;
        if (n_vertices == 0 && n_arestas == 0) {
            return 0;
        }

        limpa_grafo(n_vertices);
        int custo_inicial = recebe_arestas(n_arestas);
        int custo_minimo = prim_v(n_vertices);


        cout << custo_inicial - custo_minimo << endl;
    }
}
