#include <iostream>
#include <unordered_map>
#include <queue>
#include <cstring>
 
using namespace std;

const int maxv = 105;
const int maxa = 5005;
const int maxv_d = maxv + maxa;

// v[i]:  map<dest, <preco,  capacidade>>
unordered_map<int, pair<int, int>> arestas[maxv_d];
unordered_map<int, pair<int, int>> arestas_r[maxv_d];

int preco[maxv_d];
int marca[maxv_d];
int pai[maxv_d];

void limpa_caminho() {
    memset(preco, -1, sizeof(preco)); // infinito
    memset(marca, 0, sizeof(marca));
    memset(pai, 0, sizeof(pai));
}

void limpa_grafo() {
    for(int i = 0; i < maxv_d; i++) {
        arestas[i].clear();
        arestas_r[i].clear();
    }
}

void recebe_arestas(int n_arestas) {
    for (int i = 1; i <= n_arestas; i++) {
        int u, v, p;
        cin >> u >> v >> p;

        // converte em direcionado
        arestas[u].insert(make_pair(v, make_pair(p, 0)));
        arestas[v].insert(make_pair(maxv + i, make_pair(p, 0)));
        arestas[maxv + i].insert(make_pair(u, make_pair(0, 0)));
    }
}

void init_capacidades(int n_vertices, int n_arestas, int cap) {
    for (int u = 1; u <= n_vertices; u++) {
        for (auto it = arestas[u].begin(); it != arestas[u].end(); it++) {
            int v = it->first;
            int p = it->second.first;
            it->second.second = cap;

            // residual
            arestas_r[u].insert(make_pair(v, make_pair(p, cap)));
            arestas_r[v].insert(make_pair(u, make_pair(p, 0)));
        }
    }

    for (int u = maxv + 1; u <= maxv + n_arestas; u++) {
        for (auto it = arestas[u].begin(); it != arestas[u].end(); it++) {
            int v = it->first;
            int p = it->second.first;
            it->second.second = cap;

            // residual
            arestas_r[u].insert(make_pair(v, make_pair(p, cap)));
            arestas_r[v].insert(make_pair(u, make_pair(p, 0)));
        }
    }
}

int djikstra(int s, int t) {
    priority_queue<pair<int, int>> q; // -peso, n_vertice

    preco[s] = 0;
    q.push(make_pair(-preco[s], s));

    while (!q.empty()) {
        int v, p_v;
        do {
            pair<int, int> q_top = q.top();
            p_v = -q_top.first;
            v = q_top.second;
            q.pop();
        } while (marca[v] && !q.empty());

        // não encontrou desmarcado, fila vazia, fim do algoritmo.
        if (marca[v]) break;

        marca[v] = 1;

        for (auto it = arestas_r[v].begin(); it != arestas_r[v].end(); it++) {
            int w = it->first;
            int p_vw = it->second.first;
            int c_vw = it->second.second;
            if (c_vw > 0 && (preco[w] == -1 || preco[w] > preco[v] + p_vw)) {
                preco[w] = preco[v] + p_vw;
                q.push(make_pair(-preco[w], w));
                pai[w] = v;
            }
        }
    }

    return preco[t] != -1; // se preço de t < infinito, achou caminho.
}

int capacidade_caminho(int s, int t, int max_v) {
    int capacidade = max_v;
    for (int f = t, p = pai[f]; p > 0; f = p, p = pai[f]) {
        int c_pf = arestas_r[p][f].second;
        if (c_pf < capacidade) {
            capacidade = c_pf;
        }
    }

    return capacidade;
}

int atualiza_capacidades(int s, int t, int cap) {
    int inc_custo = 0;

    for (int f = t, p = pai[f]; p > 0; f = p, p = pai[f]) {
        auto e_pf = arestas_r[p].find(f);
        auto e_fp = arestas_r[f].find(p);
        int p_pf = e_pf->second.first;
        if (arestas[p].find(f) != arestas[p].end()) { // aresta real
            inc_custo += p_pf * cap;
        } else { // aresta residual
            inc_custo -= p_pf * cap;
        }
        
        // atualiza grafo residual
        e_pf->second.second -= cap;
        e_fp->second.second += cap;
    }

    return inc_custo;
}

int main() {
    int n_vertices, n_arestas, qtd_fluxo, capacidade;

    for (int n_instancia = 1; cin >> n_vertices; n_instancia++) {
        cin >> n_arestas;
        
        limpa_grafo();
        recebe_arestas(n_arestas);

        cin >> qtd_fluxo >> capacidade;

        init_capacidades(n_vertices, n_arestas, capacidade);
        
        cout << "Instancia " << n_instancia << endl;

        int custo_total = 0;
        int fluxo_atual = 0;
        while (fluxo_atual < qtd_fluxo) {
            limpa_caminho();
            int achou = djikstra(1, n_vertices);
            if (!achou) break;

            int cap_caminho = capacidade_caminho(1, n_vertices, qtd_fluxo - fluxo_atual);
            fluxo_atual += cap_caminho;
            int custo_atual = atualiza_capacidades(1, n_vertices, cap_caminho);
            custo_total += custo_atual;
        }

        if (fluxo_atual < qtd_fluxo) {
            cout << "impossivel" << endl << endl;
        } else {
            cout << custo_total << endl << endl;
        }
    }
    return 0;
}
