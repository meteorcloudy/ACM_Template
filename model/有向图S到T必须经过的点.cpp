#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N=1000010;
vector<int> e[N] , path;
int n,m,s,t,reach,c[N],f[N];
bool visit[N] ;
bool find(int u){
    path.push_back(u);visit[u]=true;
    if (u==t) return true;
    for (int i=0;i<e[u].size();i++){
        int v=e[u][i];
        if (visit[v]) continue;
        if (find(v)) return true;
    }
    path.pop_back() ;
    return false ;
}

int dp(int u){
    if (f[u]!=-1) return f[u];
    f[u]=0;
    for (int i=0;i<e[u].size();i++){
        int v=e[u][i];
        if (c[v]==-1)
            f[u]=max(f[u],dp(v));
        else
            f[u]=max(f[u],c[v]);
    }
    return f[u];
}

int main(){
    freopen("assassination.in","r",stdin);
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for (int i=0;i<m;i++){
        int u,v;scanf("%d%d",&u,&v);
        e[u].push_back(v);
    }
    if (!find(s)){
        printf("0\n\n");
        return 0;
    }
    reach=-1;
    for (int i=1;i<=n;i++) c[i]=-1,f[i]=-1;
    for (int i=0;i<path.size();i++)
        c[path[i]]=i;
    vector<int> res;
    for (int i=1;i<path.size()-1;i++){
        int u=path[i];
        reach=max(reach,dp(path[i-1]));
        if (reach<=i)
            res.push_back(u);
    }
    printf("%d\n",res.size());
    sort(res.begin(),res.end()) ;
    for (int i=0;i<res.size();i++)
        printf("%d ",res[i]);
    printf("\n");
}
