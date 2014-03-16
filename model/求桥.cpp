#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std ;

const int MAXN = 5010 ;
const int MAXM = 20010 ;

int id[MAXN] , end[MAXM] , cnt , g[MAXN] , next[MAXM] ;
bool deleted[MAXM] ;
int visit[MAXN];
int n , m , low[MAXN] , dfn[MAXN] , root;
int Belong[MAXN] ;
int step ;
int Cnt ;
int fu[MAXM] , fv[MAXM] , sz , ind[MAXN];

void AddEdge(int u , int v)
{
      cnt++ ; next[cnt]=g[u];g[u]=cnt;end[cnt]=v;
}

void tarjan(int u,int fa)
{
	low[u]=dfn[u]=++step;
	bool flag=true; visit[u]=1;
	for (int mark = g[u] ; mark > 0 ; mark = next[mark]){
		int v = end[mark];
		if (v==fa&&flag){
			flag=false;
			continue ;
		}
		if (!visit[v]){
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
			if (dfn[u]<low[v])
			{
				deleted[mark]=true;
				if (mark&1)
					deleted[mark+1]=true;
				else
					deleted[mark-1]=true;
			}
		}else if (visit[v]==1)
			low[u]=min(low[u],dfn[v]);
	}
	visit[u]=2;
}

void dfs(int u)
{
	Belong[u]=Cnt;
	for (int mark = g[u] ; mark > 0 ; mark = next[mark]){
		if (deleted[mark]) continue ;
		int v = end[mark];
		if (Belong[v]) continue ;
		dfs(v);
	}
}

int main()
{
	while (scanf("%d%d",&n,&m)==2){

		for (int i = 1 ; i <= n ; i++) g[i] = 0 ; cnt = 0 ;
		for (int i = 1 ; i <= 2*m ; i++) deleted[i] = false ;
		for (int i = 1 ; i <= n ; i++) dfn[i] = 0 ;
		for (int i = 1 ; i <= n ; i++) visit[i] = false ;
		for (int i = 1 ; i <= n ; i++) Belong[i] = 0 ;
		step = 0 ;

		for (int i = 1 ; i <= m ; i++)
		{
		      int A , B ; scanf("%d%d",&A,&B);
		      AddEdge(A,B);
		      AddEdge(B,A);
		}


            sz = 0 ;
		tarjan(1,0);


		Cnt = 0 ;
		for (int i = 1 ; i <= n ; i++)
			if (!Belong[i])
			{
				Cnt++ ;
				dfs(i);
			}
            for (int i = 1 ; i <= Cnt ; i++)
                  ind[i]=0;

            for (int i = 1 ; i <= n ; i++)
            {
                  for (int mark = g[i] ; mark > 0 ; mark = next[mark])
                  {
                        if (!deleted[mark])continue ;
                        int v = end[mark];
                        ind[Belong[v]]++ ;
                  }
            }

            int leaf = 0 ;
            for (int i = 1 ; i <= Cnt ; i++)
                  if (ind[i]==1) leaf++ ;
            printf("%d\n",(leaf+1)/2);
	}
	return 0 ;
}
