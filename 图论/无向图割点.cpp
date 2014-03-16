const int MaxN=200005;
const int MaxE=N*10;

struct Edge
{
    int v,pre;
    Edge(){}
    Edge(int v,int pre) : v(v),pre(pre) {}
}edge[MaxE];

int hBef[MaxN],hAft[MaxN],nEdge;

void edgeInit()
{
    nEdge=0;
    memset(hBef,-1,sizeof(hBef));
    memset(hAft,-1,sizeof(hAft));
}
void addEdge(int u,int v,int head[])
{
    edge[nEdge]=Edge(v,head[u]);
    head[u]=nEdge++;
}

struct Tarjan_Cutpt
{
    int stk[N],top;
    int dfn[N],low[N],idx;
    bool cut[N];

    int bCnt;
	vector <int> block[N];

    void tarInit()
    {
        top=idx=bCnt=0;
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        memset(cut,0,sizeof(cut));
        for(int i=0;i<N;i++) block[i].clear();
    }
    void dfs(int u,int pre)
    {
        stk[top++]=u;
        dfn[u]=low[u]=++idx;

        int v,Rt=0;
        bool flag=1;
        for(int i=hBef[u];i!=-1;i=edge[i].pre)
        {
            v=edge[i].v;
            if(v==pre&&flag) { flag=0; continue; }

            if(dfn[v]==0)
            {
                dfs(v,u);
                low[u]=min(low[u],low[v]);
                if(low[v]>=dfn[u])
                {
                    if(pre==-1) Rt++;
                    else cut[u]=1;
                    while(1)
                    {
                        int tmp=stk[--top];
                        block[bCnt].push_back(tmp);
                        if(tmp==v) break;
                    }
                    block[bCnt].push_back(u);
                    bCnt++;
                }
            }
            else low[u]=min(low[u],dfn[v]);
        }
        if(pre==-1) cut[u]=(Rt>1);
    }
    void solve()
    {
        for(int i=0;i<n;i++) if(dfn[i]==0)
        {
            dfs(i,-1);
		}
        //for(int i=0;i<n;i++) printf("%d ",cut[i]); puts("");
    }
}tar;
