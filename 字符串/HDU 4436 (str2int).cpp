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
#define maxn 210000
#define oo 1000000000
#define NUM 13
#define MOD 2012
#define clearAll(a) memset(a,0,sizeof(a))
#define sq(a) ((a)*(a))

using namespace std;

typedef long long ll;

struct node
{
    node* next[NUM];
    node* pre;
    int len;
    int sum;
    int cnt;
    void init()
    {   memset(next,0,sizeof(next));
        pre = NULL;
        len = 0;
        cnt = 0;
        sum = 0;
    }
};

node py[2*maxn];
int n;
char s[maxn];
int cnt;
int res;

node* root,* tail;

void add(int c)
{
    node *p = tail, *np = &py[cnt++]; np->init();
    np->len = p->len+1;

    for (;p&&!p->next[c];p=p->pre)
        p->next[c]=np;
    tail = np;
    if (!p)
        np->pre = root;
    else
        if (p->next[c]->len==p->len+1)
            np->pre = p->next[c];
        else
        {   node *q = p->next[c], *r = &py[cnt++]; r->init();
            *r = *q;
            r->len = p->len + 1;
            q->pre = np->pre = r;
            for (;p&&p->next[c]==q;p=p->pre)
                p->next[c]=r;
        }
}

void bfs()
{
    queue<node *> q;
    root->cnt=1;
    q.push(root);

    node * now , *next;

    while (!q.empty())
    {
        now = q.front();
        q.pop();
        res+=now->sum;
        res%=MOD;
        for (int i=0;i<=10;i++)
        if (now->next[i])
        {
            next = now->next[i];
            if (i!=10&&(!(now==root&&i==0)))    // 处理前导零
            {
                next->cnt += now->cnt;
                next->cnt %= MOD;
                next->sum += now->sum*10 + now->cnt * i;
                next->sum %= MOD;
            }
            if (now->len+1==next->len)
                q.push(next);
        }
    }
}

int main()
{
    freopen("C:\\Users\\py\\Desktop\\input.txt","r",stdin);
    //freopen("C:\\Users\\py\\Desktop\\output.txt","w",stdout);

    while (scanf("%d",&n)==1)
    {
        cnt=0;
        root = &py[cnt++]; root->init();
        tail = root;

        res = 0;

        for (int i=1;i<=n;i++)
        {
            scanf("%s",s);
            int m = strlen(s);
            for (int j=0;j<m;+j++)
                add(s[j]-'0');
            add(10);
        }
        bfs();
        res = (res%MOD + MOD) % MOD;
        printf("%d\n",res);
    }




    return 0;
}
