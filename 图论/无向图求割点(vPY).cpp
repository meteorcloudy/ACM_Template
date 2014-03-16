
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <queue>
#include <vector>
#include <set>
#include <sstream>
#define maxn 200005
#define oo 1000000000
#define clearAll(a) memset(a,0,sizeof(a))
#define sq(a) ((a)*(a))

using namespace std;

typedef long long ll;

vector<int> g[maxn];

int stk[maxn],top;
int dfn[maxn],low[maxn],idx;
bool cut[maxn];
int n;

void tarInit()
{
	top=idx=0;
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(cut,0,sizeof(cut));
}
void dfs(int u,int pre)
{
	dfn[u]=low[u]=++idx;

	int v,Rt=0;
	bool flag=1;
	int sz = g[u].size();

	for(int i=0;i<sz;i++)
	{
		v=g[u][i];
		if(v==pre&&flag) { flag=0; continue; }

		if(dfn[v]==0)
		{
			dfs(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u])
			{
				if(pre==-1) Rt++;
				else cut[u]=1;
			}
		}
		else low[u]=min(low[u],dfn[v]);
	}
	if(pre==-1) cut[u]=(Rt>1);
}
void solve()
{
	for(int i=1;i<=n;i++) if(dfn[i]==0)
	{
		dfs(i,-1);
	}
}

int main()
{
	freopen("C:\\Users\\py\\Desktop\\input.txt","r",stdin);
    //freopen("C:\\Users\\py\\Desktop\\output.txt","w",stdout);

	while (scanf("%d",&n)&&n)
	{
		for (int i=1;i<=n;i++)
			g[i].clear();

		string s;

		getline(cin,s);

		while (getline(cin,s))
		{
			istringstream in(s);
			int x;
			in >> x;
			if (x==0) break;
			int y;
			while (in>>y)
			{
				g[x].push_back(y);
				g[y].push_back(x);
			}
		}

		tarInit();
		solve();

		int ans = 0;
		for (int i=1;i<=n;i++)
			if (cut[i])
                ans++;
		printf("%d\n",ans);
	}


	return 0;
}
