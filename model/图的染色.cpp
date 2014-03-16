#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std ;

const int MAXM = 200010;
const int MAXN = 10010 ;

int end[MAXM] , next[MAXM] , cnt , g[MAXN] ;
int col[MAXN] ;
int n , m , ans ;
bool used[MAXN] ;
int d[MAXN] ;
int r[MAXN] ;
bool visit[MAXN];

void AddEdge(int u,int v)
{
    cnt++;
    next[cnt]=g[u];
    g[u]=cnt;
    end[cnt]=v;
}
bool cmp(const int &a,const int &b)
{
    return d[a]<d[b];
}
int main()
{
    int t;
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d%d",&n,&m);
        for (int i=1; i<=n; i++) g[i]=d[i]=0;
        cnt=0;
        for (int i=1; i<=m; i++)
        {
            int a,b;
            scanf("%d%d",&a,&b);
            AddEdge(a,b);
            AddEdge(b,a);
            d[a]++ ;
            d[b]++ ;
        }
        ans = 0 ;
        for (int i=1; i<=n; i++)
            ans = max(ans,d[i]);
        for (int i=1; i<=n; i++)
            r[i]=i;
        sort(r+1,r+n+1,cmp);
        for (int i=1;i<=ans+2;i++)
            used[i]=false;

        if (!(ans&1))
        {
            ans++;
            for (int i=1; i<=n; i++) col[i]=0;
            for (int i=1; i<=n; i++) visit[i]=false;
            queue<int> q ;
            q.push(1);visit[1]=true;
            bool fuck=false;
            while (!q.empty())
            {
                int u = q.front();
                q.pop();
                for (int mark = g[u] ; mark > 0 ; mark = next[mark])
                {
                    int v = end[mark];
                    if (!visit[v])
                    {
                        q.push(v);
                        visit[v]=true;
                    }
                    else
                        used[col[v]]=1;
                }
                for (int v = 1 ; v <= ans ; v++)
                    if (!used[v])
                    {
                        col[u]=v;
                        break ;
                    }
                for (int mark = g[u] ; mark > 0 ; mark = next[mark])
                {
                    int v = end[mark];
                    used[col[v]]=0;
                }
            }
        }
        else
        {
            for (int i=1; i<=n; i++) col[i]=0;
            for (int i=1; i<=n; i++) visit[i]=false;
            queue<int> q ;
            q.push(1); visit[1]=true;
            bool fuck=false;

            while (!q.empty())
            {
                int u = q.front();
                q.pop();
                for (int mark = g[u] ; mark > 0 ; mark = next[mark])
                {
                    int v = end[mark];
                    if (!visit[v])
                    {
                        q.push(v);
                        visit[v]=true;
                    }
                    else
                        used[col[v]]=1;
                }
                for (int v = 1 ; v <= ans ; v++)
                    if (!used[v])
                    {
                        col[u]=v;
                        break ;
                    }
                if (col[u]==0)
                {
                    fuck=1;
                    break ;
                }
                for (int mark = g[u] ; mark > 0 ; mark = next[mark])
                {
                    int v = end[mark];
                    used[col[v]]=0;
                }
            }
            if (fuck)
            {
                ans+=2;
                for (int i=1; i<=n; i++) col[i]=0;
                while (!q.empty()) q.pop();
                for (int i=1; i<=n; i++) visit[i]=false;
                q.push(1); visit[1]=true;
                bool fuck=false;
                while (!q.empty())
                {
                    int u = q.front();
                    q.pop();
                    for (int mark = g[u] ; mark > 0 ; mark = next[mark])
                    {
                        int v = end[mark];
                        if (!visit[v])
                        {
                            q.push(v);
                            visit[v]=true;
                        }
                        else
                            used[col[v]]=1;
                    }
                    for (int v = 1 ; v <= ans ; v++)
                        if (!used[v])
                        {
                            col[u]=v;
                            break ;
                        }
                    for (int mark = g[u] ; mark > 0 ; mark = next[mark])
                    {
                        int v = end[mark];
                        used[col[v]]=0;
                    }
                }
            }
        }
        printf("%d\n",ans);
        for (int i=1; i<=n; i++)
            printf("%d\n",col[i]);
    }
    return 0 ;
}
