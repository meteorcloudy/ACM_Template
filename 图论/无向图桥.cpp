const int MaxN=10005;
const int MaxE=100005;

struct Edge
{
    int u,v,id,pre;
    Edge(){}
    Edge(int u,int v,int id,int pre) :
        u(u),v(v),id(id),pre(pre) {}
}edge[MaxE*2];

int n,m;
int head[MaxN],nEdge;

void edgeInit()
{
    nEdge=0;
    memset(head,-1,sizeof(head));
}
void addEdge(int u,int v,int id,int head[])
{
    edge[nEdge]=Edge(u,v,id,head[u]);
    head[u]=nEdge++;
}

struct Tarjan_bridge
{
    int stk[MaxE],top;
    int lab[MaxE],nLab;
    int dfn[MaxN],low[MaxN],idx;
    bool cut[MaxN],Rt;
    bool bri[MaxE],used[MaxE];

    void init()
    {
        top=idx=nLab=0;
        memset(cut,0,sizeof(cut));
        memset(bri,0,sizeof(bri));
        memset(dfn,0,sizeof(dfn));
        memset(lab,-1,sizeof(lab));
        memset(used,0,sizeof(used));
    }
    void dfs(int u)
    {
        int v,id,sCnt=0;
        dfn[u]=low[u]=++idx;
        for(int i=head[u];i!=-1;i=edge[i].pre)
        {
            v=edge[i].v,id=edge[i].id;
            
            if(used[id]) continue;

            used[id]=1;    stk[top++]=id;

            if(dfn[v]==0){
                dfs(v);  sCnt++;
                low[u]=min(low[u],low[v]);
                if(low[v]>=dfn[u]){
                    int tmp; nLab++;
                    do{
                        tmp=stk[--top];
                        lab[ edge[tmp].id ]=nLab;
                    }while(tmp!=id);

                    if(u!=Rt) cut[u]=1;
                    if(low[v]>dfn[u]) bri[id]=1;
                }
            }
            else low[u]=min(low[u],dfn[v]);
        }
        if(u==Rt&&sCnt>1) cut[u]=1;
    }
    void solve()
    {
        for(int i=0;i<n;i++) if(dfn[i]==0)
        {
            Rt=i;
            dfs(i);
        }
    }
}tar;
