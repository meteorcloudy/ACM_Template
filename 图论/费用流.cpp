/*cf147div2E*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;

const int MaxM=200001;
const int INF=0x3f3f3f3f;

const int N=105;

struct Edge
{
	int u,v,pre,cap,cost;
	Edge(){}
	Edge(int u,int v,int pre,int cap,int cost) :
		u(u),v(v),pre(pre),cap(cap),cost(cost) {}
}edge[MaxM];

int head[MaxM],nEdge,re_flow;

void edgeInit()
{
	nEdge=0;
	memset(head,-1,sizeof(head));
}
void addEdge(int u,int v,int cap,int cost)
{
	edge[nEdge]=Edge(u,v,head[u],cap,cost);
	head[u]=nEdge++;
	edge[nEdge]=Edge(v,u,head[v],0,-cost);
	head[v]=nEdge++;
}
struct MinCostFlow
{
	queue<int> que;
	int vis[MaxM],pre[MaxM],dis[MaxM],pos[MaxM];
	int spfa(int s,int t,int n)
	{
		for(int i=0;i<=n;i++)
		{
			pre[i]=-1; vis[i]=0; dis[i]=INF;
		}

		que.push(s); pre[s]=s; dis[s]=0; vis[s]=1;
		while(!que.empty())
		{
			int u=que.front();

			que.pop(); vis[u]=0;

			for(int i=head[u];i!=-1;i=edge[i].pre)
			{
				int v=edge[i].v,cost=edge[i].cost;
				if(edge[i].cap>0&&dis[u]+cost<dis[v])
				{
					dis[v]=dis[u]+cost;

					pre[v]=u; pos[v]=i;

					if(!vis[v])
					{
						vis[v]=1;
						que.push(v);
					}
				}
			}
		}
		if(pre[t]!=-1&&dis[t]<INF) return 1;
		return 0;
	}
	void solve(int s,int t,int n,int &flow,int &cost)
	{
		flow=0,cost=0;
		while(spfa(s,t,n))
		{
			int mi=INF;
			for(int u=t;u!=s;u=pre[u]) mi=min(mi,edge[pos[u]].cap);
			flow+=mi;
			cost+=mi*dis[t];
			for(int u=t;u!=s;u=pre[u])
			{
				edge[ pos[u] ].cap-=mi;
				edge[ pos[u]^1 ].cap+=mi;
			}
		}
	}
}flow;


void input(int &st,int &ed)
{
    int n,len,limit[N],cnt[30]={0};
    char str_t[N],str[N][N];

    scanf("%s %d",str_t,&n);

    st=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%s %d",str[i],&limit[i]);

        addEdge(st,i,limit[i],0);

        len=(int)strlen(str[i]);
        for(int j=0;j<len;j++)
        {
            addEdge(i,n+str[i][j]-'a'+1,1,i);
        }
    }

    re_flow=len=(int)strlen(str_t);

    for(int i=0;i<len;i++)
    {
        cnt[str_t[i]-'a']++;
    }
    ed=n+31;

    for(int i=0;i<30;i++)
    {
        if(cnt[i]) addEdge(n+i+1,ed,cnt[i],0);
    }
}
int main()
{
    edgeInit();
    int st,ed,mx_flow,cost;
    input(st,ed);
    flow.solve(st,ed,ed-st+1,mx_flow,cost);
    if(mx_flow!=re_flow) cout<<-1<<endl;
    else cout<<cost<<endl;
    return 0;
}

