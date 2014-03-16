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
#define maxn 1000010
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
	void init()
	{	memset(next,0,sizeof(next));
		pre = NULL;
		len = 0;
	}
};

node py[2*maxn];
int cnt;

node* root,* tail;

void add(int c,int len)
{
	node *p = tail, *np = &py[cnt++]; np->init();
	np->len = len;
	for (;p&&!p->next[c];p=p->pre)
        p->next[c]=np;
	tail = np;
	if (!p)
        np->pre = root;
	else
		if (p->next[c]->len==p->len+1)
            np->pre = p->next[c];
		else
		{	node *q = p->next[c], *r = &py[cnt++]; r->init();
			*r = *q;
			r->len = p->len + 1;
			q->pre = np->pre = r;
			for (;p&&p->next[c]==q;p=p->pre)
                p->next[c]=r;
		}
}

int main()
{
    freopen("C:\\Users\\py\\Desktop\\input.txt","r",stdin);
    //freopen("C:\\Users\\py\\Desktop\\output.txt","w",stdout);
    cnt=0;
    string s;
    cin >> s ;
    root = &py[cnt++]; root->init();
    tail = root;
    int len = s.length();
    for (int i=0;i<len;i++)
    	add(s[i]-'a',i+1);
    return 0;
}
