#include <iostream>
#include <cstring>

using namespace std;

const int maxv = 26;

int arestas[maxv + 1][maxv + 1];
int marca[maxv + 1];
int componente[maxv + 1];

void recebe_arestas(int e) {
    memset(&arestas, 0, sizeof(arestas)); // limpa
    char uc, vc;
    int u, v;
    while (e--) {
        cin >> uc >> vc;
        u = ((int) uc) - 97;
        v = ((int) vc) - 97;
        arestas[u][v] = 1;
        arestas[v][u] = 1;
    }
}

void dfs(int v, int s) {
    marca[s] = 1;
    componente[s] = 1;
    for (int i = 0; i < v; i++) {
        if (arestas[s][i]) { // para cada vizinho
            if (!marca[i]) dfs(v, i);
        }
    }
}

int calcula_componentes(int v) {
    memset(&marca, 0, sizeof(marca)); // limpa
    
    int n = 0;
    for (int i = 0; i < v; i++) {
        if (marca[i] == 0) { // encontrado novo componente conexo
            memset(&componente, 0, sizeof(componente)); // limpa anterior
            n++;
            dfs(v, i);

            // imprime componente conexo
            for (int j = 0; j < v; j++) {
                if (componente[j]) {
                    cout << (char) (j+97) << ",";
                }
            }
            cout << endl;
        }
    }
    return n;
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int v,e;
        cin >> v >> e;
        recebe_arestas(e);
        cout << "Case #" << i << ":" << endl << calcula_componentes(v) << " connected components" << endl << endl;
    }

    return 0;
}