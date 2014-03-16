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
#define maxn 100100
#define oo 1000000000
#define clearAll(a) memset(a,0,sizeof(a))
#define sq(a) ((a)*(a))

using namespace std;

typedef long long ll;


int sa[maxn];
int rank[maxn];
int h[maxn];
int s[maxn];
char str[maxn];

void radix(int *str,int *a,int *b,int n,int m)
{
	static int count[maxn];
	clearAll(count);
	for (int i=0;i<n;++i) ++count[str[a[i]]];
	for (int i=1;i<=m;++i) count[i]+=count[i-1];
	for (int i=n-1;i>=0;--i) b[--count[str[a[i]]]] = a[i];
}

void suffix_array(int *str,int n,int m)
{
	static int a[maxn],b[maxn];
	for (int i=0;i<n;++i) rank[i]=i;
	radix(str,rank,sa,n,m);

	rank[sa[0]]=0;
	for (int i=1;i<n;++i) rank[sa[i]] = rank[sa[i-1]] + (str[sa[i]]!=str[sa[i-1]]);
	for (int i=0;(1<<i)<n;++i)
	{	for (int j=0;j<n;++j)
		{
			a[j] = rank[j]+1;
			b[j] = j + (1<<i) >= n ? 0 :rank[j+(1<<i)] + 1;
			sa[j] = j;
		}
		radix(b,sa,rank,n,n);
		radix(a,rank,sa,n,n);
		rank[sa[0]]=0;
		for (int j=1;j<n;++j)
		{
			rank[sa[j]] = rank[sa[j-1]] + (a[sa[j-1]]!=a[sa[j]] || b[sa[j-1]]!=b[sa[j]]);
		}
	}
}

void calc_height(int *str,int n)
{
	int k = 0;
	h[0]=0;
	for (int i=0;i<n;++i)
	{
		k = k==0 ? 0 : k-1;
		if (rank[i]!=0)
			while (str[i+k]==str[sa[rank[i]-1]+k]) ++k;
		h[rank[i]] = k;
	}
	for (int i=n;i>=1;--i)
		h[i]=h[i-1];
}

int R[maxn][25];

void prepareRMQ(int *a,int n)
{
	for (int i=1;i<=n;i++)
		R[i][0]=i;

	for (int j=1;(1<<j)<=n;j++)
		for (int i=1;i+(1<<j)-1<=n;i++)
			R[i][j]=((a[R[i][j-1]]<=a[R[i+(1<<(j-1))][j-1]])?R[i][j-1]:R[i+(1<<j-1)][j-1]);
}

int ask(int l,int r,int *a)
{
	int k = (int) (log((double)(r-l+1))/log(2.0));

	return (a[R[l][k]]<=a[R[r-(1<<k)+1][k]])?R[l][k]:R[r-(1<<k)+1][k];
}

int calc(int x)
{
	if (!x) return 1;
	int res = 0;
	while (x)
	{
		res++;
		x/=10;
	}
	return res;
}

int main()
{
    freopen("C:\\Users\\py\\Desktop\\input.txt","r",stdin);
    //freopen("C:\\Users\\py\\Desktop\\output.txt","w",stdout);

    while (scanf("%s",str)==1)
    {
    	int n = strlen(str);
    	int mx = 0;
    	for (int i=0;i<n;i++)
    	{
    		mx = max(mx,str[i]-'a'+1);
    		s[i]=str[i]-'a'+1;
    	}
    	//mx++;
    	suffix_array(s,n,mx);
    	calc_height(s,n);
        prepareRMQ(h,n);
    	
        int Q;
        scanf("%d",&Q);
        ll ans1 = 0; 
        ll ans2 = 0;
        int x,y,px,py;
        bool flag = false;

        while (Q--)
        {
        	scanf("%d%d",&x,&y);
        	 // for (int i=x;i<y;i++)
        	 // 	printf("%c",str[i]);

        	y--;
        	mx = 0;
        	if (flag)
        	{
        		if (x==px) mx = n - x;
        		else	mx = h[ask(min(rank[x],rank[px])+2,max(rank[x],rank[px])+1,h)];
        		mx = min(mx,min(py-px+1,y-x+1));
        	}
        	//printf("  : %d\n",mx);
        	flag=true;
        	ans1+= (y-x)+2;
        	ans2+= calc(mx) + (y-x+1-mx) + 2;
        	px = x; py = y;
        }
        printf("%I64d %I64d\n",ans1,ans2);
    }

    return 0;
}
