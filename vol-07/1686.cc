/* HDU 1686 - Oulipo, by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;

#define MAXL	(1000010)

char W[MAXL], T[MAXL];
int f[MAXL];
int lW, lT;

int count(void)
{
	int cnt = 0;
	int i, j;
	lW = strlen(W); lT = strlen(T);
	// --
	f[0] = j = -1;
	for(i = 1;i < lW;i++)
	{
		while( j >= 0 && W[j+1] != W[i] )
			j = f[j];
		if( W[j+1] == W[i] ) j++;
		f[i] = j;
	}
	// ---
	j = -1;
	for(i = 0;i < lT;i++)
	{
		while( j >= 0 && W[j+1] != T[i] )
			j = f[j];
		if( W[j+1] == T[i] ) j++;
		if( j == lW-1 )
		{
			cnt++;
			j = f[j];
		}
	}
	return cnt;
}

void proc(void)
{
	scanf("%s%s", W, T);
	printf("%d\n", count());
}

int main(void)
{
	int cas;
	scanf("%d", &cas);
	while(cas--) proc();
	return 0;
}
