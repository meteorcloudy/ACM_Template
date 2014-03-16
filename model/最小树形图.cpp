/*
Root为根，N为点的个数从0开始
cnt为边数,ret为答案
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>

using namespace std;

typedef long long ll;
const int inf=1<<29;

const int  MAXN=1010;
const int MAXM=2001000;
int ret;
struct edge{
    int u,to,w;
}e[MAXM];
int N,cnt,Root;
int id[MAXN],pre[MAXN],num,visit[MAXN];
int in[MAXN];

void add(int u,int v,int w)
{
    e[cnt].u=u;e[cnt].to=v;e[cnt].w=w;cnt++;
}

bool TreeMST()
{
    int u,v;
    ret=0;
    while(1)
    {
        for(int i=0;i<N;i++)
            in[i]=inf;
        memset(pre,-1,N*sizeof(int));
        for(int i=0;i<cnt;i++)
        {
            u=e[i].u;
            v=e[i].to;
            if(e[i].w<in[v]&&u!=v)//找除根和已删除的点以外每个点的最小入边
            {
                pre[v]=u;
                in[v]=e[i].w;
            }
        }
        for(int i=0;i<N;i++)
        {
            if(i==Root)continue;
            if(pre[i]==-1)return false;
        }
        in[Root]=0;
        num=0;
        memset(visit,-1,sizeof(visit));
        memset(id,-1,sizeof(id));
        for(int i=0;i<N;i++)
        {
            ret+=in[i];v=i;
            while(visit[v]!=i&&id[v]==-1&&v!=Root)
            {
                visit[v]=i;
                v=pre[v];
            }
            if(v!=Root&&id[v]==-1)//一个新环
            {
                for(u=pre[v];u!=v;u=pre[u])
                    id[u]=num;
                id[v]=num++;
            }
        }
        if(num==0)return true;//已经无环
        for(int i=0;i<N;i++)
            if(id[i]==-1)id[i]=num++;
        for(int i=0;i<cnt;i++)//可以去边，但貌似没效果
        {
            v=e[i].to;
            e[i].u=id[e[i].u];
            e[i].to=id[v];
            if(e[i].u!=e[i].to)
            e[i].w-=in[v];
        }
        N=num;
        Root=id[Root];
    }
    return true;
}
int abss(int x){
    if (x<0) return -x;
    return x;
}
struct Point{
    int x,y,z;
}p[MAXN];
int dis(Point x,Point y)
{
    return abss(x.x-y.x)+abss(x.y-y.y)+abss(x.z-y.z);
}

int main()
{
    int X,Y,Z,x,y,n;

    while(1)
    {
        scanf("%d%d%d%d",&n,&X,&Y,&Z);
        if(n==0&&X==0&&Y==0&&Z==0)break;
        Root=0;cnt=0;N=n+1;
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].z);
            add(Root,i,X*p[i].z);
        }
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&x);
            while(x--)
            {
                scanf("%d",&y);
                int d=dis(p[i],p[y]);
                int cost;
                if(p[y].z>p[i].z) cost=d*Y+Z;
                else cost=d*Y;
                add(i,y,cost);
            }
        }
        if(TreeMST())printf("%d\n",ret);
        else puts("poor XiaoA");
    }
    return 0;
}
