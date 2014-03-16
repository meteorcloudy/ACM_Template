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
#define maxn 2005
#define oo 1000000000
#define clearAll(a) memset(a,0,sizeof(a))
#define sq(a) ((a)*(a))

using namespace std;

typedef long long ll;

struct edge
{
	int id,x;
	edge() {}
	edge(int id,int x) : id(id),x(x) {}
};

vector<edge> v[maxn];
bool vis[maxn];
vector<int> ans;
int n;
int st;

bool cmp(edge x,edge y)
{
	return x.id<y.id;
}

void dfs(int x)
{	
	int sz = v[x].size();
	for (int i=0;i<sz;i++)
		if (!vis[v[x][i].id])
		{
			vis[v[x][i].id]=true;
			dfs(v[x][i].x);
			ans.push_back(v[x][i].id);
		}
}

bool work()
{
	for (int i=1;i<=n;i++)
	{
		if (v[i].size()%2)	return false;
		sort(v[i].begin(),v[i].end(),cmp);
	}

	clearAll(vis);
	ans.clear();
	dfs(st);
	for (int i=ans.size()-1;i>=0;i--)
		printf("%d%c",ans[i],(i==0)?'\n':' ');
	return true;
}

int main()
{
    freopen("C:\\Users\\py\\Desktop\\input.txt","r",stdin);
    //freopen("C:\\Users\\py\\Desktop\\output.txt","w",stdout);

    int m = 0;
    int x,y,z;
    n = 0;

    bool flag = true;

    while (scanf("%d%d",&x,&y)==2)
    {
    	if (x==0&&y==0) 
    	{
    		if (m==0) break;
    		else 
    		{
    			if (!work()) printf("Round trip does not exist.\n");
    			n = 0;
    			flag = true;
    			m = 0;
    			for (int i=0;i<maxn;i++)
    				v[i].clear();
    		}
    		continue;
    	}

    	m++;

    	scanf("%d",&z);
    	v[x].push_back(edge(z,y));
    	v[y].push_back(edge(z,x));
    	n = max(n,max(x,y));
    	if (flag)
    		st = min(x,y),flag=false;
    }

    return 0;
}
