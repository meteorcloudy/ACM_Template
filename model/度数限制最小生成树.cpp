#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXN=100;
const int INFINITE=0x3f3f3f3f;

int n,m;
char s[MAXN][MAXN];
char now[MAXN];
char s1[MAXN],s2[MAXN];
int f[MAXN][MAXN],ori[MAXN][MAXN];
int k;

struct node{
      int u,v,len;
}E[MAXN*MAXN];
int cnt=0;
int father[MAXN];
bool visit[MAXN];
int ans;
bool connect[MAXN];
int U[MAXN],V[MAXN],Max[MAXN];



bool cmp(const node &a,const node &b){
      return a.len<b.len;
}

int getfather(int x){
      if (father[x]==x) return father[x];
      father[x]=getfather(father[x]);
      return father[x];
}

void DFS(int pre,int u,int MM,int uu,int vv){
      visit[u]=true;
      U[u]=uu;V[u]=vv;Max[u]=MM;
      for (int i=0;i<=n;i++){
            if (!visit[i]&&f[i][u]!=INFINITE){
                  if (f[i][u]>MM)
                        DFS(u,i,f[i][u],i,u);
                  else
                        DFS(u,i,MM,uu,vv);
            }
      }
}

void solve1()
{
      for (int i=0;i<=n;i++)
            father[i]=i;
      ans=0;
      for (int i=1;i<=cnt;i++){
            int k1=E[i].u,k2=E[i].v,cost=E[i].len;
            if (k1==0||k2==0)continue;
            if (getfather(k1)==getfather(k2)) continue;
            father[getfather(k1)]=getfather(k2);
            f[k1][k2]=ori[k1][k2];
            f[k2][k1]=ori[k2][k1];
            ans+=f[k1][k2];
      }
      // 给每个连同块连边
      for (int i=1;i<=n;i++){
            visit[i]=false;
            connect[i]=false;
      }
      int used=0;
      for (int i=1;i<=n;i++){
            int fuck=getfather(i);
            if (visit[fuck])continue;

            int low=ori[i][0],find=i;
            for (int j=1;j<=n;j++){
                  int fa=getfather(j);
                  if (fa==fuck){
                        if (ori[j][0]<low){
                              low=ori[j][0];
                              find=j;
                        }
                  }
            }
            f[find][0]=f[0][find]=low;
            used++;
            connect[find]=true;
            ans+=low;
            visit[fuck]=true;
      }
      // 找环

      for (int _=used+1;_<=k;_++){
            for (int i=1;i<=n;i++) visit[i]=false;
            visit[0]=true;
            for (int i=1;i<=n;i++)
                  if (f[0][i]!=INFINITE)
                        DFS(0,i,f[0][i],0,i);
            int dif=0,kth=-1;
            for (int i=1;i<=n;i++)
                  if (Max[i]-ori[i][0]>dif){
                        dif=Max[i]-ori[i][0];
                        kth=i;
                  }
            if (dif==0)
                  break;
            int k1=U[kth],k2=V[kth];
            f[k1][k2]=f[k2][k1]=INFINITE;
            f[kth][0]=f[0][kth]=ori[0][kth];
            ans=ans-dif;
      }

      printf("Total miles driven: %d\n",ans);
}

int main()
{
      //freopen("input.txt","r",stdin);
      //freopen("output.txt","w",stdout);
      while (scanf("%d",&m)==1){
            n=0;strcpy(s[0],"Park");cnt=0;
            memset(ori,0x3f,sizeof(ori));
            memset(f,0x3f,sizeof(f));
            for (int i=1;i<=m;i++){
                  bool flag;
                  int k1,k2,len;
                  scanf("%s",s1);
                  flag=false;
                  for (int i=0;i<=n;i++)
                        if (strcmp(s1,s[i])==0){
                              k1=i;
                              flag=true;
                              break;
                        }
                  if (!flag){
                        strcpy(s[++n],s1); k1=n;
                  }
                  scanf("%s",s2);
                  flag=false;
                  for (int i=0;i<=n;i++){
                        if (strcmp(s2,s[i])==0){
                              k2=i;
                              flag=true;
                              break;
                        }
                  }
                  if (!flag){
                        strcpy(s[++n],s2); k2=n;
                  }
                  scanf("%d",&len);
                  ori[k1][k2]=ori[k2][k1]=len;
                  cnt++;E[cnt].u=k1;E[cnt].v=k2;E[cnt].len=len;
            }
            scanf("%d",&k);
            sort(E+1,E+cnt+1,cmp);
            solve1();
      }
      return 0;
}
