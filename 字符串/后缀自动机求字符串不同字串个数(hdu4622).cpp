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
#define maxn 2500
#define oo 1000000000
#define NUM 27
#define clearAll(a) memset(a,0,sizeof(a))
#define sq(a) ((a)*(a))

using namespace std;

typedef long long ll;

struct node
{
    node* next[NUM];
    node* pre;
    int len;
    int cnt;
    void init()
    {    memset(next,0,sizeof(next));
        pre = NULL;
        len = 0;
        cnt = 0;
    }
};

node py[2*maxn];
int n;
char s[maxn];
int cnt;
int ans[maxn][maxn];
int res;

node* root,* tail;

void add(int c)
{
    node *p = tail, *np = &py[cnt++]; np->init();
    np->len = p->len+1;


    for (;p&&!p->next[c];p=p->pre)
    {
        p->next[c]=np;
        np->cnt += p->cnt;
    }

    res+=np->cnt;

    tail = np;
    if (!p)
        np->pre = root;
    else
        if (p->next[c]->len==p->len+1)
            np->pre = p->next[c];
        else
        {    node *q = p->next[c], *r = &py[cnt++]; r->init();
            *r = *q;
            r->len = p->len + 1;
            r->cnt = 0;
            q->pre = np->pre = r;
            for (;p&&p->next[c]==q;p=p->pre)
            {
                p->next[c]=r;
                r->cnt += p->cnt;
                q->cnt -= p->cnt;
            }
        }
}



int main()
{
    //freopen("C:\\Users\\py\\Desktop\\input.txt","r",stdin);

    int tt;
    scanf("%d",&tt);

    while (tt--)
    {
        scanf("%s",s);
        n = strlen(s);

        for (int i=0;i<n;i++)
        {
            cnt = 0;
            root = &py[cnt++];  root->init(); root->cnt=1;
            tail = root;
            res = 0;
            for (int j=i;j<n;j++)
            {
                add(s[j]-'a');
                ans[i][j]=res;
            }
        }

        int m;
        scanf("%d",&m);
        int l,r;
        while (m--)
        {
            scanf("%d%d",&l,&r);
            l--; r--;
            printf("%d\n",ans[l][r]);
        }
    }
}

