/* HDU Online Judge. Problem 1532 - Drainage Ditches, by Abreto <m@abreto.net>. */
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

#define MAXN    256

struct edge_t
{
    int id;
    int next;
    int cap;
};
edge_t node[MAXN*MAXN];
int nnodes;
int front[MAXN];
void add_edge(int u, int v, int c)
{
    int newnode = ++nnodes;
    node[newnode].id = v;
    node[newnode].next = front[u];
    node[newnode].cap = c;
    front[u] = newnode;
}
int find_edge(int u, int v)
{
    int w = u[front];
    while(w)
    {
        if(node[w].id == v)
            return w;
        w = node[w].next;
    }
    return 0;
}
void grant_cap(int u, int v, int c)
{
    int e = find_edge(u,v);
    if(e)       node[e].cap += c;
    else if(c)  add_edge(u,v,c);
}

int N, M;

void clear(void)
{
    int i = 0;
    nnodes = 0;
    for(i = 0;i < MAXN;++i)
        front[i] = 0;
}

void readata(void)
{
    int i = 0;
    int si = 0, ei = 0, ci = 0;
    for(i = 0;i < N;++i)
    {
        scanf("%d%d%d", &si, &ei, &ci);
        grant_cap(si, ei, ci);
    }
}

char vis[MAXN];
int path[MAXN];

int dfs(int u, int t)
{
    int v = u[front];
    vis[u] = 1;
    if(u == t) return 1;
    while(v)
    {
        int w = node[v].id;
        if(!vis[w] && node[v].cap && dfs(w,t))
        {
            path[u] = w;
            return 1;
        }
        v = node[v].next;
    }
    return 0;
}

int findpath(int s, int t)
{
    memset(vis, 0, (M+1)*sizeof(char));
    return dfs(s, t);
}

int maxflow(int s, int t)
{
    int flow = 0;
    while(findpath(s,t))
    {
        int i = 0;
        int minf = node[find_edge(s,path[s])].cap;
        for(i = path[s];i != t;i=path[i])
            minf = min(minf, node[find_edge(i,path[i])].cap);
        for(i = s;i != t;i = path[i])
        {
            grant_cap(i, path[i], -minf);
            grant_cap(path[i], i, minf);
        }
        flow += minf;
    }
    return flow;
}

void proccess(void)
{
    readata();
    printf("%d\n", maxflow(1,M));
}

int main(void)
{
    while(EOF != scanf("%d%d", &N, &M))
    {
        clear();
        proccess();
    }
    return 0;
}
