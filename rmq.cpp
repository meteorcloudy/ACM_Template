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
#define maxn 1000010
#define oo 1000000000
#define clearAll(a) memset(a,0,sizeof(a))
#define sq(a) ((a)*(a))

using namespace std;

typedef long long ll;

int a[maxn];
int R[maxn][25];
int n;

void prepareRMQ()
{
	for (int i=1;i<=n;i++)
		R[i][0]=i;

	for (int j=1;(1<<j)<=n;j++)
		for (int i=1;i+(1<<j)-1<=n;i++)
			R[i][j]=((a[R[i][j-1]]<=a[R[i+(1<<(j-1))][j-1]])?R[i][j-1]:R[i+(1<<j-1)][j-1]);
}

int ask(int l,int r)
{
  int k = (int) (log((double)(r-l+1))/log(2.0));

	return (a[R[l][k]]<=a[R[r-(1<<k)+1][k]])?R[l][k]:R[r-(1<<k)+1][k];
}

int main()
{
    freopen("C:\\Users\\py\\Desktop\\input.txt","r",stdin);
    //freopen("C:\\Users\\py\\Desktop\\output.txt","w",stdout);

    cin >> n;
    for (int i=1;i<=n;i++)
    	cin >> a[i];
   	prepareRMQ();
   	int m;
   	cin >> m;
   	int l,r;
   	for (int i=1;i<=m;i++)
   	{
   		cin >> l >> r;
   		cout << ask(l,r) <<endl;
   	}
    return 0;
}
