/*
也可以直接用有向图的去跑
*/
const int MaxN=200005;
const int MaxE=2000005;

struct Edge
{
    int u,v,pre;
    Edge(){}
    Edge(int u,int v,int pre) : u(u),v(v),pre(pre) {}
}edge[MaxE*4];

int hBef[MaxN],hAft[MaxN],nEdge;

void edgeInit()
{
    nEdge=0;
    memset(hBef,-1,sizeof(hBef));
    memset(hAft,-1,sizeof(hAft));
}
void addEdge(int u,int v,int head[])
{
    edge[nEdge]=Edge(u,v,head[u]);
    head[u]=nEdge++;
}
struct Tarjan_undirected
{
    int lab[MaxN],nLab;
    int stk[MaxN],top;
    int low[MaxN],dfn[MaxN],idx;

    void tarInit()
    {
        nLab=idx=top=0;
        memset(lab,-1,sizeof(lab));
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
    }
    void solve(int u,int pre)
    {
        stk[top++]=u;
        low[u]=dfn[u]=++idx;

        bool flag=1;
        for(int i=hBef[u];i!=-1;i=edge[i].pre)
        {
            int v=edge[i].v;

            if(v==pre&&flag){ flag=0; continue; }//判重边

            if(!dfn[v]) {
                solve(v,u);
                low[u]=min(low[u],low[v]);
            }
            else if(dfn[v]<low[u]) low[u]=dfn[v];
        }
        if(low[u]==dfn[u])
        {
            int tmp=0; ++nLab;
            do
            {
                tmp=stk[--top];
                lab[tmp]=nLab;
            }while(tmp!=u);
        }
    }
}tar;

