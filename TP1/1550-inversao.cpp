#include <iostream>
#include <cstring>
#include <queue>
 
using namespace std;

const int maxv = 10000;

int marca[maxv + 5];
int dist[maxv + 5];

int invert(int v) {
    int n = v, rev = 0, rem;
    while (n > 0) {
        rem = n % 10;
        rev = rev * 10 + rem;
        n /= 10;
    }
    return rev;
}

int bfs_v(int a, int b) {
    if (a == b) return 0;

    queue<int> q;

    memset(&dist, 0, sizeof(dist));
    memset(&marca, 0, sizeof(marca));
    
    dist[a] = 0;
    marca[a] = 1;
    q.push(a);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        int newdist = dist[v] + 1;
        // para cada vizinho, mas são só 2 vizinhos
        int w1 = v+1;
        int w2 = invert(v);
        if (w1 == b || w2 == b) return newdist; // achou, retorna

        // adiciona na fila
        if (w1 <= maxv && !marca[w1]) {
            dist[w1] = newdist;
            marca[w1] = 1;
            q.push(w1);
        }
        if (w2 <= maxv && !marca[w2]) {
            dist[w2] = newdist;
            marca[w2] = 1;
            q.push(w2);
        }
    }
    return 1<<30; // não achou, infinito
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        cout << bfs_v(a, b) << endl;
    }
    return 0;
}