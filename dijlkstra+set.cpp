#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <string.h>
#define maxn 100005
#define maxm 100005
#define clearAll(a) memset(a,0,sizeof(a))
#define INF 2000000000
using namespace std;

typedef long long ll;

ll oo = 10*(ll) INF;

int first[maxn];
int next[maxn*2];
int v[maxn*2];
ll c[maxn*2];
ll d[maxn];
int cnt;
int n,m;
map<int,int> h[maxn];
bool vis[maxn];
int tt[maxn];



struct cmp
{
        bool operator() (const int &a,const int &b) const
        {
                return d[a]<d[b]||(d[a]==d[b]&&a<b);
        }
};

set<int,cmp> g;

ll dijkstra()
{
    clearAll(vis);
    for (int i=1;i<=n;i++) d[i]=oo;
    d[1]=0;
    vis[1]=true;
    g.clear();
    g.insert(1);
    int st;
    while (!g.empty())
    {
        st=*g.begin();
        if (st==n) return d[n];
        g.erase(st);
        vis[st]=true;
        for (int i=first[st];i;i=next[i])
        {
            if (!vis[v[i]]&&(d[v[i]]>d[st]+c[i]))
            {
                g.erase(v[i]);
                d[v[i]]=d[st]+c[i];
                g.insert(v[i]);
            }
        }
    }
    return -1;
}

int main()
{
    clearAll(first);
    scanf("%d%d",&n,&m);
    int x,y,w;
    for (int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&w);
        next[i]=first[x]; first[x]=i;
        v[i]=y; c[i]=w;
        next[i+m]=first[y]; first[y]=i+m;
        v[i+m]=x; c[i+m]=w;
    }

    cout << dijkstra() <<endl;

    return 0;
}













