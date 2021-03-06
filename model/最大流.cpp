#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define INFINITE 1000000000
#define OPPOSITE(x) ((((x) - 1) ^ 1) + 1)
#define MIN(a,b)((a)<(b)?(a):(b))
#define MAXM 1000000
#define MAXN 500

using namespace std;
typedef long long ll;

int g[MAXN] , cur[MAXN] , end[MAXM] , c[MAXM] , tot = 0 , next[MAXM];
int a[MAXN];
int pre[MAXN];
int sumd[MAXN] , d[MAXN] ;
int S , T  ;

void AddEdge(int x , int y , int flow)
{
      ++tot ; next[tot] = g[x] ; g[x] = tot ; end[tot] = y ; c[tot] = flow ;
      ++tot ; next[tot] = g[y] ; g[y] = tot ; end[tot] = x ; c[tot] = 0 ;
}

int Sap()
{
    memset(sumd,0,sizeof(sumd));
    memset(d,0,sizeof(d));
    int u,now,tmp,flow = 0;
    int v = T + 1 ;
    a[u=S] = INFINITE, sumd[0] = v;
    for(int i = 0 ; i < v; i++)
        cur[i] = g[i];
    while (d[S] < v)
    {
	for (now = cur[u]; now; now = next[now])
	    if (c[now] && d[u] == d[end[now]] + 1)
		break;
	if (now)
	{
	    tmp = end[now];
	    a[tmp] = MIN(a[u], c[now]);
	    cur[u] = pre[tmp] = now;
	    if ((u = tmp) == T)
	    {
		flow += (tmp = a[T]);
		do
		{
		    c[pre[u]] -= tmp;
		    c[OPPOSITE(pre[u])] += tmp;
		    u = end[OPPOSITE(pre[u])];
		} while (u != S);
		a[S] = INFINITE;
	    }
	}
	else
	{
	    if ((-- sumd[d[u]]) == 0)
		break;
	    d[u] = v;
	    cur[u] = g[u];
	    for (now = g[u]; now; now = next[now])
		if (c[now] && d[u] > d[end[now]] + 1)
		    d[u] = d[end[now]] + 1, cur[u] = now;
	    sumd[d[u]] ++;
	    if (u != S)
		u = end[OPPOSITE(pre[u])];
	}
    }
    return flow;
}
