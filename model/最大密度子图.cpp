#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

#define OPPOSITE(x) ((((x) - 1) ^ 1) + 1)
#define MIN(a,b)((a)<(b)?(a):(b))
#define MAXM 1000000
#define MAXN 500

using namespace std;
typedef long long ll;

const double INFINITE = 1000000000.0 ;
const double eps = 1e-8;

int g[MAXN] , cur[MAXN] , end[MAXM] , tot = 0 , next[MAXM];
double c[MAXM] ;
double a[MAXN] ;
int pre[MAXN];
int sumd[MAXN] , d[MAXN] ;
bool visit[MAXN] ;
int S , T  ;
int N , M ;
int from[MAXM] , to[MAXM] ;
int degree[MAXN] ;

void AddEdge(int x , int y , double flow)
{
      ++tot ; next[tot] = g[x] ; g[x] = tot ; end[tot] = y ; c[tot] = flow ;
      ++tot ; next[tot] = g[y] ; g[y] = tot ; end[tot] = x ; c[tot] = 0 ;
}

double Sap()
{
    memset(sumd,0,sizeof(sumd));
    int u,now,tmp;
    double flow = 0 , tmp2;
    int v = T + 1 ;
    a[u=S] = INFINITE ;
    for(int i = 0 ; i < v; i++)
        cur[i] = g[i];
    for (int i = S ; i <= T; i++) visit[i]=0;
    queue<int> q;
    d[T]=0; sumd[d[T]]++ ; visit[T]=1; q.push(T);
    while (!q.empty()){
            int u = q.front(); q.pop();
            for (int mark = g[u] ; mark > 0 ; mark = next[mark]){
                  int v = end[mark] ;
                  if (visit[v]) continue ;
                  d[v] = d[u] + 1 ;
                  visit[v] = 1 ;
                  sumd[d[v]]++ ;
                  q.push(v) ;
            }
    }
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
		flow += (tmp2 = a[T]);
		do
		{
		    c[pre[u]] -= tmp2;
		    c[OPPOSITE(pre[u])] += tmp2;
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

void MakeGraph(double Mid)
{
      tot=0;for (int i=S;i<=T;i++) g[i]=0;
      for (int i=1;i<=N;i++){
            AddEdge(S,i,1.0*M);
            AddEdge(i,T,1.0*M+2*Mid-1.0*degree[i]);
      }
      for (int i=1;i<=M;i++){
            AddEdge(from[i],to[i],1.0);
            AddEdge(to[i],from[i],1.0);
      }
}

void Dfs(int u){
      visit[u]=1;
      for (int mark=g[u];mark>0;mark=next[mark]){
            int v=end[mark];
            if (c[mark]>0&&!visit[v])
                  Dfs(v);
      }
}

int main()
{
      //freopen("input.txt","r",stdin);
      while (scanf("%d%d",&N,&M)==2){
            S=0; T=N+1;
            for (int i=1;i<=N;i++) degree[i]=0;
            for (int i=1;i<=M;i++){
                  scanf("%d%d",&from[i],&to[i]);
                  degree[from[i]]++;
                  degree[to[i]]++;
            }
            if (M==0){
                  printf("1\n1\n");
                  continue ;
            }
            double left=0 , right=1.0*M;
            while (right-left>=1.0/N/N){
                  double Mid=(left+right)/2;
                  MakeGraph(Mid);
                  double flow = Sap();
                  flow = (1.0*M*N - flow)/2.0;
                  if (flow > eps)
                        left=Mid;
                  else  right=Mid ;
            }
            MakeGraph(left);
            double fuck=Sap();
            for (int i=S;i<=T;i++) visit[i]=0;
            Dfs(S);
            int res=0;
            for (int i=1;i<=N;i++) if (visit[i]) res++ ;
            printf("%d\n",res);
            for (int i=1;i<=N;i++) if (visit[i]) printf("%d\n",i);
      }
      return 0;
}
