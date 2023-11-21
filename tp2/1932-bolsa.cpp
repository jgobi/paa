#include <iostream>
 
using namespace std;
 
int preco[200005];

int solve_v(int n, int c) {
    int lucro = 0;
    int menor = preco[0];
    
    for (int i = 1; i < n; i++) {
        if (preco[i] <= menor) {
            menor = preco[i];
        } else {
            int l = preco[i] - menor - c;
            if (l > 0) {
                lucro += l;
                menor = preco[i] - c;
            }
        }
    }

    return lucro;
}

int main() {
    int n,c;
    cin >> n >> c;    
    
    for (int i = 0; i < n; i++) {
        cin >> preco[i];
    }
    
    cout << solve_v(n, c) << endl;
    return 0;
}