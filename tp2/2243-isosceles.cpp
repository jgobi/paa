#include <iostream>

using namespace std;

int colunas[50005];

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> colunas[i];
    }

    int s = 0;
    for (int i = 0; i < n; i++) {
        s = min(s + 1, colunas[i]);
        colunas[i] = s;
    }

    s = 0;
    int max_v = 1;
    for (int i = n - 1; i >= 0; i--) {
        s = min(s + 1, colunas[i]);
        colunas[i] = s;
        if (s > max_v) max_v = s;
    }

    cout << max_v << endl;

    return 0;
}