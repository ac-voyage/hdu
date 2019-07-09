/* HDU 2544, by Abreto<m@abreto.net> */
#include <bits/stdc++.h>

using namespace std;

namespace abreto {

const int MAXN = 128, MAXM = 10010;

int N, M;

struct edge
{
    int to, cost;
    edge *next;
    edge(int v = 0, int c = 0, edge *n = NULL) :
        to(v), cost(c), next(n)
    { }
}E[MAXM * 2];
int nEdges;
edge *front[MAXN];
void add_edge(int u, int v, int c)
{
    E[nEdges] = edge(v, c, front[u]);
    front[u] = E + nEdges;
    nEdges++;
}

struct state
{
    int d, u;
    state(int dd = 0, int uu = 0) : d(dd), u(uu) { }
    bool operator<(const state &b) const {
        return d > b.d;
    }
};

priority_queue<state> q;
int d[MAXN], vis[MAXN];
int dijkstra(int s, int t)
{
    while (!q.empty()) q.pop();
    memset(d, 0x3f, sizeof d); memset(vis, 0, sizeof vis);
    d[s] = 0;
    q.push(state(d[s], s));
    while (!q.empty())
    {
        int u = q.top().u; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (edge *e = front[u]; e != NULL; e = e->next)
        {
            int v = e->to;
            int newDistance = d[u] + e->cost;
            if (newDistance < d[v])
            {
                d[v] = newDistance;
                q.push(state(d[v], v));
            }
        }
    }
    return d[t];
}

int answer()
{
    while (M--)
    {
        int A, B, C;
        cin >> A >> B >> C;
        add_edge(A, B, C);
        add_edge(B, A, C);
    }
    return dijkstra(1, N);
}

void clear(void)
{
    nEdges = 0;
    memset(front, 0, (N + 10) * (sizeof(front[0])));
}

void main(void)
{
    while (1)
    {
        cin >> N >> M;
        if (0 == N && 0 == M) break;
        clear();
        cout << answer() << '\n';
    }
}

}

int main(void)
{
    cin.sync_with_stdio(false); cin.tie(0); cout.tie(0);
    abreto::main();
    return 0;
}
