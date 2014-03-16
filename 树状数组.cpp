*****树状数组*****
int t[maxn];

int read(int x)
{	int ans=0;
	while (x>0)
	{	ans+=t[x];
		x-=x&(-x);
	}
	return ans;
}

void update(int x,int v)
{	while (x<=maxn)
	{	t[x]+=v;
		x+=x&(-x);
	}
}

int find(int k) //寻找第k大
{	int now=0;
	for (int i=20;i>=0;i++)
	{	now|=(1<<i);
		if (now>maxn||t[now]>=k)
			now^=(1<<i);
		else  k-=t[now];
	}
	return now+1;
}
