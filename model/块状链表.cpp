#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

const int MAXN = 100010 ;

int n , m ;
int t[MAXN] , step[MAXN] , father[MAXN] , belong[MAXN];

void update(int x){
    int nx = x + t[x] ;
    if (nx > n){
        step[x] = 1 ;
        father[x] = 0 ;
    }else
        if (!father[nx] || belong[nx]>belong[x]){
            father[x] = nx ; step[x] = 1 ;
        }else{
            father[x] = father[nx] ; step[x] = step[nx]+1 ;
        }
}

int main(){
    //freopen("input.txt","r",stdin);
    scanf("%d%d",&n,&m) ;
    for (int i = 1 ; i <= n ; i++)
        scanf("%d",&t[i]);
    int k = int(sqrt(n)) ;
    for (int i = 1 ; i <= n ; i++)
        belong[i]=i/k ;
    for (int i = n ; i >= 1 ; i--) update(i) ;
    while (m--){
        int op; scanf("%d",&op);
        if (op){
            int x,ls;
            scanf("%d",&x) ; int ret=0;
            for (ret=0;x;ls=x,ret+=step[x],x=father[x]);
            printf("%d %d\n",ls,ret) ;
        }else{
            int x , tc ;
            scanf("%d%d",&x,&tc);
            t[x] = tc ;
            for (int i = x ; belong[i]==belong[x] ; i--)
                update(i) ;
        }
    }
    return 0 ;
}
