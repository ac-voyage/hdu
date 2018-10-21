/* HDU 6153 - A Secret, by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;

namespace exkmp
{

const int maxn = 1000100, maxm = 1000100;

int n, m;
char S[maxn], T[maxm];

/* the length of longest prefix between T[i..m-1] and T[0..m-1] */
int nxt[maxm];
/* the length of longest prefix between S[i..n-1] and T[0..m-1] */
int ex[maxn];

void getsize()
{
    n = strlen(S);
    m = strlen(T);
}

void self(void)
{
    int q = 1, p = 0;
    nxt[0] = m;
    while (1 + p < m && T[1 + p] == T[p]) p++; nxt[1] = p;
    for (int i = 2; i < m; i++)
    {
        int l = nxt[i - q];
        if (i + l - 1 < p)
        {
            nxt[i] = l;
        } else {
            int j = max(0, p - i + 1);
            while (i + j < m && T[i + j] == T[j]) j++;
            nxt[i] = j;
            p = i + j - 1;
            q = i;
        }
    }
}

void run(void)
{
    int q = 0, p = 0;
    self();
    while (p < n && p < m && S[p] == T[p]) p++;
    ex[0] = p; p--;
    for (int i = 1; i < n; i++)
    {
        int l = nxt[i - q];
        if (i + l - 1 < p)
        {
            ex[i] = l;
        } else {
            int j = max(0, p - i + 1);
            while (i + j < n && S[i + j] == T[j]) j++;
            ex[i] = j;
            p = i + j - 1;
            q = i;
        }
    }
}

void inspect(void)
{
    printf("S: ");
    for (int i = 0; i < n; i++) putchar(S[i]);
    puts("");
    printf("T: ");
    for (int i = 0; i < m; i++) putchar(T[i]);
    puts("");
    printf("next:");
    for (int i = 0; i < m; i++) printf(" %d", nxt[i]);
    puts("");
    printf("extend:");
    for (int i = 0; i < n; i++) printf(" %d", ex[i]);
    puts("");
}

} // exkmp


namespace jspace {

typedef long long int ll;
const int p = 1e9 + 7;
inline int add(const int a, const int b)
{
    ll z = 0ll + a + b;
    if (z >= p) z -= p;
    return z;
}
inline int mul(const int a, const int b)
{
    ll z = 1ll * a * b;
    z -= z / p * p;
    return z;
}

void main(void)
{
    int ans = 0;
    scanf("%s", exkmp::S);
    scanf("%s", exkmp::T);
    exkmp::getsize();
    reverse(exkmp::S, exkmp::S + exkmp::n);
    reverse(exkmp::T, exkmp::T + exkmp::m);
    exkmp::run();
    for (int i = 0; i < exkmp::n; i++)
    {
        ll len = exkmp::ex[i];
        ans = add(ans, 1ll * len * (len + 1ll) / 2ll % p);
    }
    printf("%d\n", ans);
}

}

int main(void)
{
    int T;
    scanf("%d", &T);
    while (T--) jspace::main();
}
