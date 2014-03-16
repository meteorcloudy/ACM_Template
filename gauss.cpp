#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <map>
#include <cmath>
#include <set>
#include <queue>
#include <vector>
#include <string.h>
#define eps 1e-8
#define sq(a) ((a)*(a))
#define maxn 105
#define clearAll(a) memset(a,0,sizeof(a))
#define oo 100000000
using namespace std;

typedef long long ll;

inline void swap(double a[maxn][maxn],int x,int y,int m)
{
    double tmp;
    for (int i=1; i<=m; i++)
    {
        tmp=a[x][i];
        a[x][i]=a[y][i];
        a[y][i]=tmp;
    }
}

void gauss(double a[maxn][maxn],int n,int m)
{
    int i,j;
    i=1;
    j=1;
    int maxi;

    while (i<=n && j<=m-1)  // ×¢Òâm-1
    {
        maxi=i;
        for (int k=i+1; k<=n; k++)
            if (abs(a[k][j])>abs(a[maxi][j]))
            {
                maxi=k;
            }

        if (a[maxi][j]!=0)
        {
            swap(a,i,maxi,m);
            for (int k=m; k>=j; k--)
                a[i][k]/=a[i][j];

            for (int k=i+1; k<=n; k++)
                for (int t=m; t>=j; t--)
                    a[k][t]-=a[k][j]*a[i][t];
            i++;
        }
        j++;
    }
}

double a[maxn][maxn];
int n,m;

int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            cin >> a[i][j];
    gauss(a,n,m);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            cout << a[i][j] <<((j==m)?'\n':' ');
    return 0;
}
