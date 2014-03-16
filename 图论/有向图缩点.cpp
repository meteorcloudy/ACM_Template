const int MaxN=11005;
const int MaxE=51005;

struct Edge
{
	int u,v,pre;
	Edge(){}
	Edge(int u,int v,int pre) : u(u),v(v),pre(pre) {}
}edge[MaxE];

int head[MaxN],nEdge;

void edgeInit()
{
	nEdge=0;
	memset(head,-1,sizeof(head));
}
void addEdge(int u,int v)
{
	edge[nEdge]=Edge(u,v,head[u]);
	head[u]=nEdge++;
}

struct Tarjan_directed
{
	bool insta[MaxN];
	int lab[MaxN],nLab;
	int sta[MaxN],top;
	int dfn[MaxN],low[MaxN],idx;

	void tarInit()
	{
		nLab=top=idx=0;
		memset(lab,-1,sizeof(lab));
		memset(dfn,0,sizeof(dfn));
		memset(low,0,sizeof(low));
		memset(insta,0,sizeof(insta));
	}

	void dfs(int u)
	{
		insta[u]=1;
		sta[top++]=u;
		dfn[u]=low[u]=++idx;
		for(int i=head[u];i!=-1;i=edge[i].pre)
		{
			int v=edge[i].v;
			if(!dfn[v])
			{
				dfs(v);
				low[u]=min(low[u],low[v]);
			}
			else if(insta[v]&&dfn[v]<low[u]) low[u]=dfn[v];
		}

		if(low[u]==dfn[u])
		{
			++nLab; int tmp;
			do
			{
				tmp=sta[--top];
				insta[tmp]=0;
				lab[tmp]=nLab;
			}while(tmp!=u);
		}
	}
}tar;

