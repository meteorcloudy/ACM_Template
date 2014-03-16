#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

const int maxn=2010;
const int maxm=20000010;

int n,m;
char s1[maxn],s2[maxn];
int d;


int cnt=0,end[maxm],next[maxm],g[maxn];
int cnt2=0,end2[maxm],next2[maxm],g2[maxn];
int map[maxn][maxn];
int dfn[maxn],bel[maxn],step;
bool visit[maxn];

int Cnt;

vector<int> scc[maxn];
int col[maxn];

struct node{
      int st,ed;
}s[maxn],t[maxn];

int fuck(char ss[],int i,int j){
      int ret=0;
      for (int kk=i;kk<=j;kk++)
            ret=ret*10+ss[kk]-'0';
      return ret;
}

bool fuck2(node a,node b){
      if (b.st>=a.st && b.st < a.ed) return 1;
      if (a.st>=b.st && a.st < b.ed) return 1;
      return 0;
}

void Print(node a){
      int hh1 = a.st / 60, mm1 = a.st % 60;
      if (hh1/10==0)
            printf("0%d",hh1);
      else
            printf("%d",hh1);
      printf(":");
      if (mm1/10==0)
            printf("0%d",mm1);
      else
            printf("%d",mm1);
      printf(" ");
      int hh2 = a.ed / 60, mm2 = a.ed % 60;
      if (hh2/10==0)
            printf("0%d",hh2);
      else
            printf("%d",hh2);
      printf(":");
      if (mm2/10==0)
            printf("0%d",mm2);
      else
            printf("%d",mm2);
      printf("\n");
}

void AddEdge(int u,int v){
      cnt++;next[cnt]=g[u];g[u]=cnt;end[cnt]=v;
}
void AddEdge2(int v,int u){
      cnt2++;next2[cnt2]=g2[u];g2[u]=cnt2;end2[cnt2]=v;
}

void dfs1(int u){
      for (int mark=g[u];mark>0;mark=next[mark]){
            int v=end[mark];
            if (!visit[v]){
                  visit[v]=1;
                  dfs1(v);
            }
      }
      dfn[step++]=u;
}

void dfs2(int u){
      scc[Cnt].push_back(u);
      bel[u]=Cnt;
      for (int mark=g2[u];mark>0;mark=next2[mark]){
            int v=end2[mark];
            if (!visit[v]){
                  visit[v]=1;
                  dfs2(v);
            }
      }
}



int main()
{
      //freopen("input.txt","r",stdin);
      scanf("%d\n",&n);
      for (int i=0;i<n;i++){
            scanf("%s%s%d\n",s1,s2,&d);
            int Ss=fuck(s1,0,1)*60+fuck(s1,3,4);
            int Tt=fuck(s2,0,1)*60+fuck(s2,3,4);
            s[i].st=Ss ; s[i].ed = Ss+d;
            t[i].st=Tt-d ; t[i].ed = Tt;
      }
      for (int i=0;i<2*n;i++) g[i]=0;cnt=0;
      for (int i=0;i<2*n;i++) g2[i]=0;cnt2=0;

      for (int i=0;i<n;i++)
            for (int j=0;j<n;j++)
                  if (i!=j){
                        if (fuck2(s[i],s[j])){
                              AddEdge(2*i,2*j+1);
                              AddEdge2(2*i,2*j+1);
                        }
                        if (fuck2(s[i],t[j])){
                              AddEdge(2*i,2*j);
                              AddEdge2(2*i,2*j);
                        }
                        if (fuck2(t[i],t[j])){
                              AddEdge(2*i+1,2*j);
                              AddEdge2(2*i+1,2*j);
                        }
                        if (fuck2(t[i],s[j])){
                              AddEdge(2*i+1,2*j+1);
                              AddEdge2(2*i+1,2*j+1);
                        }

                  }


      for (int i=0;i<2*n;i++) visit[i]=0;
      step=0;
      for (int i=0;i<2*n;i++)
            if (!visit[i]){
                  visit[i]=1;
                  dfs1(i);
            }
      for (int i=0;i<2*n;i++) visit[i]=0;
      Cnt=0;
      for (int i=2*n-1;i>=0;i--){
            if (!visit[dfn[i]]){
                  visit[dfn[i]]=1;
                  Cnt++;
                  scc[Cnt].clear();
                  dfs2(dfn[i]);
            }
      }

      for (int i=0;i<n;i++)
            if (bel[i*2]==bel[i*2+1])
            {
                  printf("NO\n");
                  return 0;
            }

      for (int i=1;i<=Cnt;i++) visit[i]=false;
      for (int i=Cnt;i>=1;i--){
            if (visit[i])continue;
            for (int j=0;j<scc[i].size();j++)
            {
                  int t=scc[i][j];
                  col[t]=1;
                  int opt=t^1;
                  if (!visit[bel[opt]]){
                        int fff=bel[opt];
                        visit[fff]=true;
                        for (int x=0;x<scc[fff].size();x++)
                              col[scc[fff][x]]=0;
                  }
            }
      }
      printf("YES\n");
      for (int i=0;i<n;i++)
            if (col[2*i]==1)
                  Print(s[i]);
            else
                  Print(t[i]);
      return 0;
}
