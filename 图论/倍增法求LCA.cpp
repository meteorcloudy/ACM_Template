const int MaxN=10005;
const int MaxE=MaxN*10;
const int Log=20;

int dp[MaxN][Log],depth[MaxN];//下标从1开始就不用清空

struct Edge
{
	int v,pre;
	Edge(){}
	Edge(int v,int pre) :v(v),pre(pre) {}
}edge[MaxE];

int head[MaxN],nEdge;

void edgeInit()
{
	nEdge=0;
	memset(head,-1,sizeof(head));
}
void addEdge(int u,int v,int head[])
{
	edge[nEdge]=Edge(v,head[u]);
	head[u]=nEdge++;
}
void dfs(int u,int pre)
{
	depth[u]=depth[dp[u][0]]+1;

	for(int i=1;i<Log;i++) dp[u][i]=dp[dp[u][i-1]][i-1];

	for(int i=head[u];i!=-1;i=edge[i].pre)
	{
		int v=edge[i].v;

		if(v==pre) continue;

		dp[v][0]=u;		dfs(v,u);
	}
}
int lca(int u,int v)
{
	if(depth[u]<depth[v]) swap(u,v);

	for(int st=1<<(Log-1),i=Log-1;i>=0;i--,st>>=1)
	{
		if(st<=depth[u]-depth[v])
		{
			u=dp[u][i];
		}
	}
	if(u==v) return u;

	for(int i=Log-1;i>=0;i--)
	{
		if(dp[v][i]!=dp[u][i])
		{
			v=dp[v][i];
			u=dp[u][i];
		}
	}
	return dp[u][0];
}

