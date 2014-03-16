/*ZOJ2362*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
using namespace std;

const int INF=(1<<30);
const int N=1005;

typedef pair<int,int> PII;

int iabs(int x){return x>0?x:-x;}

struct KM_MX
{
	int nx,ny,delta;				//二分图两边的点数
	int W[1005][1005];			//边权
	int LX[1005],LY[1005];		//顶标
	int linkX[1005],linkY[1005];	//点X与Y中哪个点匹配，点Y与X中哪个点匹配
	bool visX[1005],visY[1005];

	void init()
	{
		memset(LY,0,sizeof(LY));		//LY初始赋值为0
		memset(W,0,sizeof(W));
		memset(linkX,0,sizeof(linkX));
		memset(linkY,-1,sizeof(linkY));
	}
	bool dfs(int u)			//匈牙利找南增广路
	{
		visX[u]=1;
		for(int i=1;i<=ny;i++)
		{
			if(visY[i]) continue;

			int tmp=(LX[u]+LY[i])-W[u][i];
			if(tmp==0)		//如果tmp=0，表示最小的匹配
			{
				visY[i]=1;
				if(linkY[i]==-1||dfs(linkY[i]))
				{
					linkY[i]=u; return true;
				}
			}
			else if(delta>tmp) delta=tmp;
		}
		return false;
	}
	void solve(int _nx,int _ny)
	{
		nx=_nx; ny=_ny;

		for(int i=1;i<=nx;i++)	//初始化LX为与其相连的边的最大权值
		{
			LX[i]=-INF;
			for(int j=1;j<=ny;j++) LX[i]=max(LX[i],W[i][j]);
		}

		for(int i=1;i<=nx;i++)
		{
			delta=INF;
			while(1)
			{
				memset(visX,0,sizeof(visX));
				memset(visY,0,sizeof(visY));

				if(dfs(i)) break;

				for(int i=1;i<=nx;i++) if(visX[i]) LX[i]-=delta;
				for(int i=1;i<=ny;i++) if(visY[i]) LY[i]+=delta;
			}
		}

		int ans=0;
		for(int i=1;i<=ny;i++)
		{
			if(W[linkY[i]][i]>0&&linkY[i]>-1)
			{
				ans+=W[linkY[i]][i];
				linkX[linkY[i]]=i;
			}
		}
		//printf("%d\n",ans);
		for(int i=1;i<=nx;i++) printf("%d%c",linkX[i],i==nx?'\n':' ');
		//for(int i=1;i<=ny;i++) printf("%d ",linkY[i]);puts("");
	}
}KM;

int a[N];

int main()
{
	//freopen("tmp.in","r",stdin);
	//freopen("tmp.out","w",stdout);

	int t; scanf("%d",&t);
	while(t--)
	{
		KM.init();

		int n; scanf("%d",&n);

		for(int i=1;i<=n;i++) scanf("%d",&a[i]);

		for(int i=1;i<=n;i++)
		{
			int m; scanf("%d",&m);
			for(int j=0;j<m;j++)
			{
				int tmp; scanf("%d",&tmp);
				KM.W[i][tmp]=a[i];
			}
			//cout<<"i="<<KM.LX[i]<<endl;
		}

		KM.solve(n,n);
		if(t) puts("");
	}
	return 0;
}

