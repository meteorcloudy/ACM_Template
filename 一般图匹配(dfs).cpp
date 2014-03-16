int first[maxn];
int next[maxn*maxn*2];
int v[maxn*maxn*2];
int match[maxn];
int n,m;
int vis[maxn];

bool aug(int now)
{	int t;
	bool flag=false;
	for (int i=first[now];i;i=next[i])
		if (!vis[t=v[i]])
		{
			if (match[t]<0)
				match[now]=t,match[t]=now,flag=true;
			else
			{
				vis[t]=1;
				if (aug(match[t]))
					match[now]=t,match[t]=now,flag=true;
				vis[t]=0;
			}
			if (flag) break;
		}
	vis[now]=0;
	return flag;
}

int graph_match()
{
	for (int i=1;i<=n;i++)
		vis[i]=0,match[i]=-1;
	for (int i=1,tot=n;i<=n&&tot>=2;)
		if (match[i]<0&&aug(i))
			i=0,tot-=2;
		else i++;
	int sum=0;
	for (int i=1;i<=n;i++)
		sum+=(match[i]>=0);
	return sum/2;
}
