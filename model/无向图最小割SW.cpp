#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std ;

const int MAXN=510;
const int INFINITE=0x3f3f3f3f;

int map[MAXN][MAXN] ;
bool cmb[MAXN];
int N,M;
int S,T,ans;
int mincut;
int visit[MAXN],wet[MAXN];

void prim()
{
      int Max,tmp;
      memset(visit,0,sizeof(visit));
      memset(wet,0,sizeof(wet));
      S=T=-1;
      for (int i=0;i<N;i++){
            Max=-INFINITE;
            for (int j=1;j<=N;j++){
                  if (!cmb[j]&&!visit[j]&&wet[j]>Max){
                        tmp=j;
                        Max=wet[j];
                  }
            }
            if (T==tmp)return ;
            S=T;T=tmp;
            mincut=Max;
            visit[tmp]=1;
            for (int j=1;j<=N;j++)
                  if (!cmb[j] && !visit[j])
                        wet[j]+=map[tmp][j];
      }
}

int SW(){
      for (int i=1;i<=N;i++) cmb[i]=false;
      ans=INFINITE;
      for (int i=1;i<N;i++){
            prim();
            if (mincut<ans)ans=mincut;
            if (ans==0) return 0;
            cmb[T]=true;
            for (int j=1;j<=N;j++)
                  if (!cmb[j]){
                        map[S][j]+=map[T][j];
                        map[j][S]+=map[j][T];
                  }
      }
      return ans;
}

int main(){
      while (scanf("%d%d",&N,&M)==2){
            memset(map,0,sizeof(map));
            for (int i=1;i<=M;i++){
                  int a,b,c;
                  scanf("%d%d%d",&a,&b,&c);
                  a++;b++;
                  map[a][b]+=c;
                  map[b][a]+=c;
            }
            printf("%d\n",SW());
      }
      return 0;
}
