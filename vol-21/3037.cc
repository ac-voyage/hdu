#include <bits/stdc++.h>
using namespace std;

struct __lucas
{
    static const int maxp = 100000;
    typedef long long int ll;
    int p;
    int f[maxp]; // fiv[maxp], inv[maxp];
    inline int mul(const int a, const int b)
    {
        ll z = 1ll * a * b;
        z -= z / p * p;
        return z;
    }
    int qow(int a, int x)
    {
        int ret = 1;
        while (x)
        {
            if (1 & x) ret = mul(ret, a);
            a = mul(a, a);
            x >>= 1;
        }
        return ret;
    }
    void init(int np)
    {
        p = np;
        // return; // uncomment this line if use binom()
        f[0] = f[1] = 1;
        // fiv[0] = fiv[1] = 1;
        // inv[1] = 1;
        for (int i = 2; i < p; i++)
        {
            f[i] = mul(f[i - 1], i);
            // inv[i] = mul(p - p / i, inv[p % i]);
            // fiv[i] = mul(fiv[i - 1], inv[i]);
        }
    }
    int C(int n, int k)
    {
        if (n < k) return 0;
        return mul(f[n], qow(mul(f[k], f[n - k]), p - 2));
    }
    /** use following if get TLE { */
    int binom(int n, int k)
    {
        if (n < k) return 0;
        if (k > n - k) k = n - k;
        int a = 1, b = 1;
        while (k)
        {
            a = mul(a, n);
            b = mul(b, k);
            n--; k--;
        }
        return mul(a, qow(b, p - 2));
    }
    /** } --- */
    int operator()(int n, int k)
    {
        if (0 == k) return 1;
        if (n < p && k < p) return binom(n, k);
        return mul(binom(n % p, k % p), (*this)(n / p, k / p));
    }
}lucas;

void proc(void)
{
    int n, m, p;
    scanf("%d%d%d", &n, &m, &p);
    lucas.init(p);
    printf("%d\n", lucas(n + m, m));
}

int main(void)
{
    int T;
    scanf("%d", &T);
    while (T--) proc();
    return 0;
}
