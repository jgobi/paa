// TODO: fazer funcionar para o caso do exemplo 1447.test (udebug)

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
 
using namespace std;

const int maxv = 100;

vector<int> arestas[maxv + 5];
vector<int> preco[maxv + 5];

int cadeiras[maxv + 5][maxv + 5];

int marca[maxv + 5];
int dist[maxv + 5]; // preço total da viagem de s para cada vértice
int pai[maxv + 5];

void limpa_grafo_instancia() {
    // limpeza das cadeiras feita implicitamente na inicialização de cadeitas.
    for (int i = 0; i < maxv + 5; i++) {
        arestas[i].clear();
        preco[i].clear();
    }
}

void limpa_grafo_caminho() {
    memset(marca, 0, sizeof(marca));
    memset(pai, 0, sizeof(pai));
    for (int i = 0; i < maxv + 5; i++) {
        dist[i] = -1; // infinito
    }
}

void recebe_arestas(int n_arestas) {
    while(n_arestas--) {
        int u, v, p;
        cin >> u >> v >> p;

        arestas[u].push_back(v);
        preco[u].push_back(p);

        arestas[v].push_back(u);
        preco[v].push_back(p);
    }
}

void inicializa_cadeiras(int n_vertices, int n_cadeiras) {
    for (int i = 1; i <= n_vertices; i++) {
        for (int j = 0; j < arestas[i].size(); j++) {
            cadeiras[i][arestas[i][j]] = n_cadeiras;
        }
    }
}

int conta_viagens(int s, int e, int max_viagens) {
    int n_viagens = max_viagens;
    int p = e;
    do {
        int pp = pai[p];
        n_viagens = min(n_viagens, cadeiras[pp][p]);
        p = pp;
    } while (p != s && p != 0 && n_viagens != 0);

    return n_viagens;
}

void atualiza_cadeiras(int s, int e, int decremento) {
    int p = e;
    do {
        int pp = pai[p];
        cadeiras[pp][p] -= decremento;
        cadeiras[p][pp] -= decremento;
        p = pp;
    } while (p != s && p != 0);
}

int dijkstra_v(int s, int e) {
    priority_queue<pair<int, int>> q; // -peso, n_vertice

    dist[s] = 0;
    q.push(make_pair(-dist[s], s));

    while (!q.empty()) {
        int p_v, v;

        do {
            pair<int, int> q_top = q.top();
            p_v = -q_top.first;
            v = q_top.second;
            q.pop();
        } while (marca[v] && !q.empty());

        // não encontrou desmarcado, fila vazia, fim do algoritmo.
        if (marca[v]) break;

        for (int i = 0; i < arestas[v].size(); i++) {
            int w = arestas[v][i];
            int p_vw = preco[v][i];
            if (cadeiras[v][w] > 0 && (dist[w] == -1 || dist[w] > dist[v] + p_vw)) {
                dist[w] = dist[v] + p_vw;
                q.push(make_pair(-dist[w], w));
                pai[w] = v;
            }
        }
    }

    return dist[e];
}

int main() {
    int n_vertices, n_arestas, n_amigos, n_cadeiras;

    int n_instancia = 1;
    while (cin >> n_vertices) {
        cin >> n_arestas;

        limpa_grafo_instancia();
        recebe_arestas(n_arestas);

        cin >> n_amigos >> n_cadeiras;
        inicializa_cadeiras(n_vertices, n_cadeiras);

        cout << "Instancia " << n_instancia << endl;

        int amigos_restantes = n_amigos;
        int valor = 0;
        while (amigos_restantes > 0) {
            limpa_grafo_caminho();
            int custo_viagem = dijkstra_v(1, n_vertices);
            int n_viagens = conta_viagens(1, n_vertices, amigos_restantes);
            if (n_viagens == 0) break; // impossível
            atualiza_cadeiras(1, n_vertices, n_viagens);
            valor += n_viagens * custo_viagem;
            amigos_restantes -= n_viagens;

            cout << "> " << n_viagens << " * $" << custo_viagem << ": (+)$" << n_viagens * custo_viagem << " (=$" << valor << ")" << endl << flush;
        }

        if (amigos_restantes > 0) {
            cout << "impossivel" << endl << endl;
        } else {
            cout << valor << endl << endl;
        }

        n_instancia++;
    }
    return 0;
}
