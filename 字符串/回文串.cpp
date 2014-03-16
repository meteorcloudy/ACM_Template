/*****************************************
*
* 2011,UESTC_ACM
* 回文串
* By a180285
* O(n) 算法 
*****************************************/

# include <math.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <algorithm>
# include <iostream>
# include <string>
# include <queue>
# include <stack>
# include <map>
# include <set>
# include <vector>
# include <cstring>
# include <list>
# include <ctime>
# include <sstream>

# define For(i,a)   for((i)=0;i<(a);(i)++)
# define MAX(x,y)   ((x)>(y)? (x):(y))
# define MIN(x,y)   ((x)<(y)? (x):(y))
# define sz(a)      (sizeof(a))
# define MEM(a)     (memset((a),0,sizeof(a)))
# define MEME(a)    (memset((a),-1,sizeof(a)))
# define MEMX(a)    (memset((a),0x7f,sizeof(a)))
# define pb(a)      push_back(a)

using namespace std;

typedef long long           ll      ;
typedef unsigned long long  ull     ;
typedef unsigned int        uint    ;
typedef unsigned char       uchar   ;


template<class T> inline void checkmin(T &a,T b){if(a>b) a=b;}
template<class T> inline void checkmax(T &a,T b){if(a<b) a=b;}

const int oo=1<<30          ;
const double eps=1e-7       ;
const int N=1               ;
const int M=110011*2               ;
const ll P=10000000097ll    ;

char str[M];//start from index 1
int p[M];
char s[M];
int n;

void kp()
{
    int i;
    int mx = 0;
    int id;
    for(i=1; i<n; i++)
    {
        if( mx > i )
            p[i] = MIN( p[2*id-i], p[id]+id-i );
        else
            p[i] = 1;
        for(; str[i+p[i]] == str[i-p[i]]; p[i]++)
            ;
        if( p[i] + i > mx )
        {
            mx = p[i] + i;
            id = i;
        }
    }
}

void pre()
{
    int i,j,k;
    n = strlen(s);
    str[0] = '$';
    str[1] = '#';
    For(i, n)
    {
        str[i*2 + 2] = s[i];
        str[i*2 + 3] = '#';
    }
    n = n*2 + 2;
    str[n] = 0;
}

void pt()
{
    int i;
    int ans = 0;
//    For(i, n)
//        printf("%c", str[i]);
//    puts("");
//    For(i, n)
//        printf("%d", p[i]);
//    puts("");

    For(i, n)
        checkmax(ans, p[i]);
    printf("%d\n", ans-1);
}

int main()
{
    int T,_=0;
    while( 1==scanf("%s", s) )
    {
        pre();
        kp();
        pt();
    }
    return 0;
}
