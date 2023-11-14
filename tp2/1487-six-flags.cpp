#include <iostream>
#include <cstring>
 
using namespace std;

int dur[105];
int pts[105];

int OPT[105][605];

void recebe_atracoes(int n) {
    memset(dur, 0, sizeof(dur));
    memset(pts, 0, sizeof(pts));

    int d, p;
    for (int i = 0; i < n; i++) {
        cin >> d >> p;
        dur[i] = d;
        pts[i] = p;
    }
}

int solve_v(int atracoes, int tempo) {
    for (int i = 1; i <= atracoes; i++) {
        for (int t = 0; t <= tempo; t++) {
            if (dur[i - 1] > t) OPT[i][t] = OPT[i - 1][t];
            else OPT[i][t] = max(OPT[i - 1][t], pts[i - 1] + OPT[i][t - dur[i - 1]]);
        }
    }
    return OPT[atracoes][tempo];
}

int main() {
    int atracoes, tempo;
    
    memset(OPT[0], 0, sizeof(OPT[0])); // init memoization

    for (int instancia = 1; 1; instancia++) {
        cin >> atracoes >> tempo;
        if (atracoes == 0) break;

        cout << "Instancia " << instancia << endl;
        recebe_atracoes(atracoes);

        cout << solve_v(atracoes, tempo) << endl << endl;
    }
    
    return 0;
}
