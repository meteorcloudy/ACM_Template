#pragma comment(linker, "/STACK:102400000,102400000")

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 200010 ;
const int K = 25 ;

int n , m ;
vector<int> e[N] , scc[N] , e2[N] ;
int dfn[N] , low[N] , color[N] , belong[N] , visit[N] , cut[N] , stack[N] , top , step , sum[N] ;
int Cnt , Color , root ;
int father[N][K] ;
int l[N] , r[N] , c[N<<1] , deep[N] ;

void tarjan(int u , int fa){
    bool flag = true ;
    dfn[u] = low[u] = ++step ; color[u] = Color ;
    stack[top++] = u ;
    for (int i = 0 ; i < e[u].size() ; i++){
        int v = e[u][i] ;
        if (v == fa && flag){
            flag = false ;
            continue ;
        }
        if (dfn[v] == -1){
            tarjan(v , u) ;
            low[u] = min(low[u] , low[v]) ;
            if (low[v] >= dfn[u]){
                if (fa == -1) root++ ;
                else cut[u] = true ;
                ++Cnt ;
                int j ;
                do{
                    j = stack[--top];
                    scc[Cnt].push_back(j) ;
                }
                while (j != v) ;
                scc[Cnt].push_back(u) ;
            }
        }else
            low[u] = min(low[u] , dfn[v]) ;
    }
}
void init(){
    for (int i = 0 ; i < N ; i++)
        dfn[i] = -1 , visit[i] = 0 , cut[i] = 0 , color[i] = 0 , e[i].clear() , scc[i].clear() , e2[i].clear() , sum[i] = 0 ;
    int u , v;
    for (int i = 0 ; i < m ; i++){
        scanf("%d%d",&u,&v);
        e[u].push_back(v) ;
        e[v].push_back(u) ;
    }
}
void solve1(){
    top = 0 ; Color = 0 ; Cnt = 0 ; step = 0 ;
    for (int i = 0 ; i < n ; i++)
        if (dfn[i]==-1){
            Color++ ;
            root = 0 ;
            tarjan(i,-1) ;
            if (root > 1) cut[i] = true ;
        }
}

void DFS(int u,int fa,int dep){
    l[u] = ++step ; c[step] = c[step-1] + sum[u] ; deep[u] = dep ; visit[u] = true ;
    for (int i = 0 ; i < e2[u].size() ; i++){
        int v = e2[u][i] ;
        if (visit[v]) continue ;
        father[v][0] = u ;
        DFS(v,u,dep+1) ;
    }
    r[u] = ++step ; c[step] = c[step-1] - sum[u] ;
}

void get_father(){
    for (int i = 1 ; i < K ; i++)
        for (int j = 1 ; j <= m ; j++)
            father[j][i] = father[father[j][i-1]][i-1] ;
}

int get_Lca(int u,int v){
    bool flag = false ;
    if (deep[u] < deep[v]) swap(u,v) ;
    for (int i = K-1 ; i >= 0 ; i--)
        if (deep[father[u][i]] >= deep[v])
            u = father[u][i] ;
    if (u==v) return u ;
    for (int i = K-1 ; i >= 0 ; i--)
        if (father[u][i] != father[v][i]){
            u = father[u][i] ;
            v = father[v][i] ;
        }
    return father[u][0] ;
}

void makeTree(){

    memset(belong,0,sizeof(belong));
    m = 0 ;
    for (int i = 0 ; i < n ; i++){
        if (cut[i]){
            m++ ;
            belong[i] = m ;
            sum[m] = 1 ;
        }
    }
    for (int i = 1 ; i <= Cnt ; i++){
        m++ ;
        sum[m] = int(scc[i].size()) ;
        for (int j = 0 ; j < scc[i].size() ; j++){
            int u = scc[i][j] ;
            if (cut[u]){
                e2[belong[u]].push_back(m) ;
                e2[m].push_back(belong[u]) ;
            }else
                belong[u] = m ;
        }
    }

    /*for (int i = 1 ; i <= m ; i++)
        printf("%d\n",sum[i]) ;
    cout<<"M = " << m << endl ;*/

    memset(visit,true,sizeof(visit));
    memset(father,0,sizeof(father)) ;
    memset(deep,-1,sizeof(deep));
    for (int i = 1 ; i <= m ; i++) visit[i] = false , deep[i] = 0 ;
    step = 0 ; c[0] = 0 ;
    for (int i = 1 ; i <= m ; i++)
        if (!visit[i])
            DFS(i,0,0) ;
    get_father() ;
}

int main(){
    //freopen("input.txt","r",stdin) ;
    //freopen("output.txt","w",stdout) ;

    int cas = 0 ;
    while (~scanf("%d%d",&n,&m)){
        printf("Case #%d:\n",++cas) ;
        init() ;
        solve1() ;
        makeTree() ;
        int Q ; scanf("%d",&Q);
        for (int j = 1 ; j <= Q ; j++){
            int s , t ;
            scanf("%d%d",&s,&t) ;

            if (s == t){
                printf("%d\n",n-1);
                continue ;
            }
            if (color[s] != color[t])
            {
                printf("%d\n",n) ;
                continue ;
            }
            s = belong[s] ; t = belong[t] ;
            int Lca = get_Lca(s,t) ;
            int ans = c[l[s]] + c[l[t]] - 2*c[l[Lca]] + sum[Lca] - (deep[s]+deep[t]-2*deep[Lca]) ;
            printf("%d\n",n-ans) ;
        }
        printf("\n");
    }
    return 0 ;
}
