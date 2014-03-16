#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

#define MIN(a,b)((a)>(b)?(b):(a))
#define Eps 1e-9

using namespace std ;

const int MAXN = 100 ;
const double INFINITE = 20000000000.0 ;

bool HL[MAXN+1] , HR[MAXN+1] ;
double v[MAXN+1][MAXN+1] ;
double slack[MAXN+1] ;
double L[MAXN+1] , R[MAXN+1] ;

int Link[MAXN+1] ;
int N ;
int ans[MAXN+1] ;

struct point
{
      double x , y ;
}A[MAXN+1] , B[MAXN+1] ;

double dist(point a , point b)
{
      return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

bool dfs(int x)
{
      HL[x] = true ;
      for (int i = 1 ; i <= N ; i++)
            if (!HR[i])
            {
                  double temp = L[x] + R[i] - v[x][i] ;
                  if (fabs(temp)<Eps)
                  {
                        HR[i] = true ;
                        if (!Link[i]|| dfs(Link[i]))
                        {
                              Link[i] = x ;
                              return true ;
                        }
                  }
                  else slack[i] = min(temp,slack[i]);
            }

      return false ;
}

int main()
{
      //freopen("input.txt","r",stdin);
      while (scanf("%d",&N)==1)
      {
            for (int i = 1 ; i <= N ; i++)
                  scanf("%lf%lf",&A[i].x,&A[i].y) ;
            for (int i = 1 ; i <= N ; i++)
                  scanf("%lf%lf",&B[i].x,&B[i].y) ;
            for (int i = 1 ; i <= N ; i++)
                  for (int j = 1 ; j <= N ; j++)
                        v[i][j] = -dist(A[i],B[j]);

            double Max = -INFINITE ;
            for (int i = 1 ; i <= N ; i++)
                  for (int j = 1 ; j <= N ; j++)
                        if (v[i][j]>Max)
                              Max = v[i][j] ;

            for (int i = 1 ; i <= N ; i++)
                  L[i] = Max , R[i] = 0 ;
            for (int i = 1 ; i <= N ; i++)
            {
                  for (int j = 1 ; j <= N ; j++)
                        slack[j] = INFINITE ;
                  while (1)
                  {
                        memset(HL,false,sizeof(HL));
                        memset(HR,false,sizeof(HR));
                        if (dfs(i)) break ;
                        double delta = INFINITE ;
                        for (int j = 1 ; j <= N ; j++)
                              if (!HR[j])
                                    delta = min(delta , slack[j]);
                        for (int j = 1 ; j <= N ; j++)
                              if (HL[j])
                                    L[j] -= delta ;
                        for (int j = 1 ; j <= N ; j++)
                              if (HR[j])
                                    R[j] += delta ;
                              else
                                    slack[j] -= delta ;
                  }
            }
            for (int i = 1 ; i <= N ; i++)
                  ans[Link[i]] = i ;
            for (int i = 1 ; i <= N ; i++)
                  printf("%d\n",ans[i]);
      }
      return 0 ;
}
