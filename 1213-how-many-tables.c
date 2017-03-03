/* HDU Online Judge. Problem 1213 - How Many Tables, by Abreto <m@abreto.net>. */
#include <stdio.h>

#define MAXN 1024

int pnt[MAXN] = {0};

void clear(int n)
{
    int i = 0;
    for(i = 0;i <= n;++i)
        pnt[i] = i;
}
int find(int x)
{
    return (pnt[x] == x) ? x : (pnt[x] = find(pnt[x]));
}
int uni(int x, int y)
{
    if( (x = find(x)) == (y = find(y)) )
        return 0; /* x and y have been seated at the same table. */
    pnt[y] = x;
    return 1;   /* one table is canceled. */
}

void process()
{
    int N = 0, M = 0;
    scanf("%d %d", &N, &M);
    clear(N);
    while(M--)
    {
        int a = 0, b = 0;
        scanf("%d %d", &a, &b);
        N -= uni(a, b);
    }
    printf("%d\n", N);
}

int main(void)
{
    int T = 0;
    scanf("%d", &T);
    while(T--)
        process();
    return 0;
}
