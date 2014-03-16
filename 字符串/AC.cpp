#include <stdio.h>
#include <string.h>
#include <string>
#include <cmath>
#include <iostream>
#include <queue>
#include <algorithm>
#define clearAll(a) memset(a,0,sizeof(a))
#define sq(a) ((a)*(a))
#define eps 1e-8
#define NUM 27
#define maxn 205
#define maxm 200500
#define    oo 1000000000
using namespace std;

typedef long long ll;

char s[maxm];
char a[maxm];
int ans[5];
struct node
{
    int id;
    node *next[NUM];
    node *fail;
    void clear()
    {
        id=-1; fail=NULL;
        memset(next,0,sizeof(next));
    }
};

node * q[maxm];
node * root;
node py[maxm];
int cnt;
int n,m,L;

void insert(char *str,node *root,int id)
{    node *p=root;
    int i=0,index;
    while (str[i])
    {
        index=str[i]-'a';
        if (p->next[index]==NULL)
        {
            cnt++;
            py[cnt].clear();
            p->next[index]=&py[cnt];
        }
        p=p->next[index];
        i++;
    }
    p->id=strlen(str);
}


void input()
{
    scanf("%s",s);
    L = strlen(s);
    cnt = 0;
    root = &py[cnt];
    root->clear();

    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%s",a);
        insert(a,root,i);
    }
}

void build()
{
    int head=0,tail=1;
    root->fail=NULL;
    q[head]=root;
    while (head!=tail)
    {
        node *tmp=q[head++];
        node *p=NULL;
        for (int i=0;i<26;i++)
            if (tmp->next[i]!=NULL)
            {
                if (tmp==root)
                    tmp->next[i]->fail = root;
                else
                {
                    p=tmp->fail;
                    while (p!=NULL)
                    {
                        if (p->next[i]!=NULL)
                        {
                            tmp->next[i]->fail=p->next[i];
                            break;
                        }
                        p=p->fail;
                    }
                    if (p==NULL) tmp->next[i]->fail=root;
                }
                q[tail++]=tmp->next[i];
            }
    }
}

bool query(char *s)
{
    int i=0,index;
    node *p=root;

    while (s[i])
    {
        index=s[i]-'a';
        while (p->next[index]==NULL&&p!=root)
            p=p->fail;
        p=p->next[index];
        p=(p==NULL)?root:p;
        node *tmp=p;
        while (tmp!=root && tmp->id!=-1 )//&& (h[tmp->id]==false))
        {
            int l = i+1-p->id;
            int r = L-(i+1);
            if (abs(l-r)==1) return true;
            tmp=tmp->fail;
        }
        i++;
    }


    return false;
}

int main()
{
freopen("C:\\Users\\py\\Desktop\\input.txt","r",stdin);
    int tt;
    scanf("%d",&tt);
    for (int i=1;i<=tt;i++)
    {
        printf("Case #%d: ",i);
        input();
        build();
        if (query(s))
            puts("zplinti1");
        else puts("bearchild");
    }
    return 0;
}
