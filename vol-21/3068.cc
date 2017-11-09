/* HDU 3068 - 最长回文, by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;

#define MAXL    110011

char S[MAXL];

char t[MAXL<<1];
int p[MAXL<<1];
int manacher(char *s)
{
    int i;
    int sl = strlen(s);
    int pos = 0, mxr = 0;
    int ret = 0;
    t[0] = '^';
    for(i = 0;i < sl;++i)
    {
        t[i*2+1] = '#';
        t[i*2+2] = s[i];
    }
    t[sl*2+1] = '#';
    t[sl*2+2] = '$';
    sl = sl*2+2;
    for(i = 1;i < sl;++i)
    {
        if(i <= mxr)
        {
            p[i] = min(p[2*pos - i], mxr-i+1);
        } else {
            p[i] = 1;
        }
        while( t[i-p[i]] == t[i+p[i]] ) p[i]++;
        if( i + p[i] - 1 > mxr )
        {
            mxr = i+p[i]-1;
            pos = i;
        }
        ret = max(ret, p[i]-1);
    }
    return ret;
}

int main(void)
{
    while(EOF != scanf("%s", S))
        printf("%d\n", manacher(S));
    return 0;
}
