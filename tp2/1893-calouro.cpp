#include <iostream>
#include <string.h>

char strings[100005][11];
char *matriculas[100005];
char *matriculas_aux[100005];
 
using namespace std;

long long conta_inversoes(int s, int e) {
    long long inversoes = 0;
    if (e - s == 1) return 0;
    int meio = s + (e - s)/2;
    long long il = conta_inversoes(s, meio);
    long long ir = conta_inversoes(meio, e);
    int sl = s;
    int sr = meio;
    int idx = s;
    while (sl < meio && sr < e) {
        if (strcmp(matriculas[sl], matriculas[sr]) <= 0) {
            matriculas_aux[idx++] = matriculas[sl];
            sl++;
        } else {
            matriculas_aux[idx++] = matriculas[sr];
            inversoes += meio - sl;
            sr++;
        }
    }
    while (sl < meio) {
        matriculas_aux[idx++] = matriculas[sl];
        sl++;
    }
    while (sr < e) {
        matriculas_aux[idx++] = matriculas[sr];
        sr++;
    }

    for (int i = s; i < idx; i++) {
        matriculas[i] = matriculas_aux[i];
    }

    return il + ir + inversoes;
}

int main() {
    int n;

    while (cin >> n) {
        for (int i = 0; i < n; i++) {
            cin >> strings[i];
            matriculas[i] = strings[i];
        }
        cout << conta_inversoes(0, n) << endl;
    }

    return 0;
}