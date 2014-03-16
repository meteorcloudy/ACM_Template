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
int sumd[MAXN] , d[MAXN] , n , m , low[MAXM] , ori[MAXM];
int S , T  ;

int row[MAXN] , col[MAXM] ;
int map[MAXN][MAXN] ;

int Row[MAXN] , Col[MAXN] ;
int Map[MAXN][MAXN] ;
int mat[MAXN][MAXN] ;
int total , S_ , T_ ;
int M[MAXN] ;


void AddEdge(int x , int y , int flow)
{
     //cout<<"x="<<x<<" y="<<y<<" flow="<<flow<<endl;
    ++tot ;
    next[tot] = g[x] ;
    g[x] = tot ;
    end[tot] = y ;
    c[tot] = flow;
    ++tot ;
    next[tot] = g[y] ;
    g[y] = tot ;
    end[tot] = x ;
    c[tot] = 0 ;
}

void AddLine(int x,int y,int l,int r)
{
    AddEdge(x,y,r-l);
    M[y]+=l;
    M[x]-=l;
}

int Sap()
{
    memset(d,0,sizeof(d));
    memset(sumd,0,sizeof(sumd));
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
                }
                while (u != S);
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

int main()
{
    //freopen("input.txt","r",stdin);
    int pos=0;
    while (scanf("%d%d",&n,&m)==2)
    {

        // -------------------------- Init
        for (int i=1; i<=n; i++)
            for (int j=1; j<=m; j++)
            {
                double fuck;
                scanf("%lf",&fuck);
                mat[i][j]=int(10*fuck);
            }
        for (int i=1; i<=n; i++)
        {
            int sum=0;
            for (int j=1; j<=m; j++)
                sum+=mat[i][j];
            row[i]=sum/10;
        }
        for (int j=1; j<=m; j++)
        {
            int sum=0;
            for (int i=1; i<=n; i++)
                sum+=mat[i][j];
            col[j]=sum/10;
        }
        for (int i=1; i<=n; i++)
            for (int j=1; j<=m; j++)
                map[i][j]=mat[i][j]/10;

        // ---------------------------- MakeGraph
        total = 0;
        S = 0;
        S_= n+m+1;
        T_= n+m+2;
        T = n+m+3;
        // S T ÐÂ½¨Ô´»ã
        for (int i=S; i<=T; i++) g[i]=0;
        tot=0 ;
        for (int i=S; i<=T; i++) M[i]=0;
        for (int i=1; i<=n; i++)
            for (int j=1; j<=m; j++)
                AddLine(i,j+n,map[i][j],map[i][j]+1);

        for (int i=1; i<=n; i++)
            AddLine(S_,i,row[i],row[i]+1);
        for (int j=1; j<=m; j++)
            AddLine(j+n,T_,col[j],col[j]+1);
        for (int i=1; i<=n+m+2; i++)
            if (M[i]>0)
            {
                total += M[i];
                AddEdge(S,i,M[i]);
            }
            else
                AddEdge(i,T,-M[i]);


        AddEdge(T_,S_,INFINITE);
        // ---------------------------- GetAns

        int Ans = Sap();
        bool flag=1;
        if (Ans!=total) flag=0;
        for (int i=1; i<=n; i++)
        {
            for (int mark=g[i]; mark>0; mark=next[mark])
            {
                if (mark%2==1)
                {
                    int j=end[mark];
                    if (j>=n+1&&j<=n+m)
                        Map[i][j-n] = map[i][j-n]+1-c[mark];
                }
            }
        }
        pos++;
        if (flag)
        {
            printf("Case %d: %d %d\n",pos,n,m);
            for (int i=1; i<=n; i++)
            {
                for (int j=1; j<m; j++)
                    printf("%d ",Map[i][j]);
                printf("%d\n",Map[i][m]);
            }
        }
        else
        {
            printf("Case %d: Impossible.\n",pos);
        }
    }
    return 0;
}
