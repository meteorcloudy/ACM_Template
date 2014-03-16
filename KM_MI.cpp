/*POJ 2195*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
using namespace std;

const int INF=0x3f3f3f3f;
const int N=1005;

typedef pair<int,int> PII;

int iabs(int x){return x>0?x:-x;}

struct KM_MI
{
	int nx,ny,delta;			//二分图两边的点数
	int W[1005][1005];			//边权
	int LX[1005],LY[1005];		//顶标
	int linkX[1005],linkY[1005];	//点X与Y中哪个点匹配，点Y与X中哪个点匹配
	bool visX[1005],visY[1005];

	void init()
	{
		memset(LY,0,sizeof(LY));		//LY初始赋值为0
		memset(LX,0x3f,sizeof(LX));		//LX初始化为与X相连的边的最小权值
		memset(linkY,-1,sizeof(linkY));
		memset(W,0x3f,sizeof(W));
	}

	bool dfs(int u)			//匈牙利找南增广路
	{
		visX[u]=1;
		for(int i=1;i<=ny;i++)
		{
			if(visY[i]) continue;

			int tmp=W[u][i]-(LX[u]+LY[i]);
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
		for(int i=1;i<=nx;i++)	//初始化顶标为最小值
		{
			LX[i]=INF;
			for(int j=1;j<=ny;j++) LX[i]=min(LX[i],W[i][j]);
		}

		for(int i=1;i<=nx;i++)
		{
			delta=INF;
			while(1)
			{
				memset(visX,0,sizeof(visX));
				memset(visY,0,sizeof(visY));

				if(dfs(i)) break;

				for(int i=1;i<=nx;i++) if(visX[i]) LX[i]+=delta;
				for(int i=1;i<=ny;i++) if(visY[i]) LY[i]-=delta;
			}
		}

		int ans=0;

		for(int i=1;i<=ny;i++)
		{
			if(linkY[i]!=-1&&W[linkY[i]][i]!=INF) ans+=W[linkY[i]][i];
		}

		printf("%d\n",ans);
		for(int i=1;i<=ny;i++) if(linkY[i]!=-1) linkX[linkY[i]]=i;

		//for(int i=0;i<nx;i++) printf("%d ",linkX[i]);puts("");
		//for(int i=0;i<ny;i++) printf("%d ",linkY[i]);puts("");
	}
}KM;
int main()
{
	//freopen("tmp.in","r",stdin);
	//freopen("tmp.out","w",stdout);

	int n,m;
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		if(n==0&&m==0) break;

		KM.init();

		vector<PII> man,house;
		for(int i=0;i<n;i++)
		{
			string str; cin>>str;
			for(int j=0;j<(int)str.length();j++)
			{
				if(str[j]=='m') man.push_back(make_pair(i,j));
				else if(str[j]=='H') house.push_back(make_pair(i,j));
			}
		}


		for(int i=0;i<(int)man.size();i++)
		{
			for(int j=0;j<(int)house.size();j++)
			{
				KM.W[i+1][j+1]=iabs(man[i].first-house[j].first)+iabs(man[i].second-house[j].second);
			}
		}

		KM.solve((int)man.size(),(int)man.size());
	}
	return 0;
}

