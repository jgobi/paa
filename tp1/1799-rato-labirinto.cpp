#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int maxv = 4000;

unordered_map<string, int> vertices;
vector<int> arestas[maxv + 5];
int marca[maxv + 5];
int dist[maxv + 5];

int str2idx(string &str, int &n) { // transforma string em idx usando o unordered_map
    int idx = n;
    auto it = vertices.find(str);
    if (it != vertices.end()) {
        idx = it->second;
    } else {
        vertices[str] = n;
        n++;
    }
    return idx;
}

int bfs_v (int s, int e) {
    memset(&marca, 0, sizeof(marca)); // limpa
    memset(&dist, 0, sizeof(dist)); // limpa

    queue<int> q;
    q.push(s);
    marca[s] = 1;
    dist[s] = 0;

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto it = arestas[v].begin(); it != arestas[v].end(); it++) {
            int w = *it;
            if (!marca[w]) {
                marca[w] = 1;
                dist[w] = dist[v] + 1;
                if (w == e) return dist[w]; // achou o nó final, retorna a distância
                q.push(w);
            }
        }
    }
    return 1 << 30; // não achou o nó final, retorna infinito
}

void recebe_arestas(int n_arestas) {
    int n_vertice = 0;
    for (int i = 0; i < n_arestas; i++) {
        string a, b;
        cin >> a >> b;

        int u = str2idx(a, n_vertice);
        int v = str2idx(b, n_vertice);

        arestas[u].push_back(v);
        arestas[v].push_back(u);
    }
}

int main() {
    int pontos, ligacoes;
    cin >> pontos >> ligacoes;

    recebe_arestas(ligacoes);
    
    int entrada = vertices["Entrada"];
    int saida = vertices["Saida"];
    int queijo = vertices["*"];

    cout << bfs_v(entrada, queijo) + bfs_v(queijo, saida) << endl;

    return 0;
}