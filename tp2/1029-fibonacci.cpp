#include <iostream>

using namespace std;

int n_rec[40] = {0};
int n_fib[40] = {0};

int fib(int n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (n_fib[n] > 0) return n_fib[n];

    int s = fib(n - 1) + fib(n - 2);
    n_rec[n] = n_rec[n - 1] + n_rec[n - 2] + 2;
    n_fib[n] = s;

    return s;
}

int main()
{
    int nt, n;
    cin >> nt;
    while (nt--) {
        cin >> n;
        int v = fib(n);
        cout << "fib(" << n << ") = " << n_rec[n] << " calls = " << v << endl;
    }
    return 0;
}