\subsection{*Splay}
	持续学习中。\\
	注意节点的size值不一定是真实的值！如果有需要需要特别维护！\\
	\begin{enumerate}
	  \item 旋转和Splay操作
	  \item rank操作
	  \item insert操作（。。很多题目都有）
	  \item del操作（郁闷的出纳员）
	  \item 由数组建立Splay
	  \item 前驱后继（营业额统计）
	  \item Pushdown Pushup的位置
	  \item *。。。暂时想不起了
	\end{enumerate}

	\subsubsection{节点定义}
	\begin{lstlisting}[language=c++]
const int MaxN = 50003;

struct Node
{
	int size,key;

	Node *c[2];
	Node *p;
} mem[MaxN], *cur, *nil;
	\end{lstlisting}
	无内存池的几个初始化函数。\\
	\begin{lstlisting}[language=c++]
Node *newNode(int v, Node *p)
{
	cur->c[0] = cur->c[1] = nil, cur->p = p;
	cur->size = 1;
	cur->key = v;
	return cur++;
}

void Init()
{
	cur = mem;
	nil = newNode(0, cur);
	nil->size = 0;
}
	\end{lstlisting}
	带内存池的几个函数。\\
	\begin{lstlisting}[language=c++]
int emp[MaxN], totemp;

Node *newNode(int v, Node *p)
{
	cur = mem + emp[--totemp];
	cur->c[0] = cur->c[1] = nil, cur->p = p;
	cur->size = 1;
	cur->key = v;
	return cur;
}

void Init()
{
	for (int i = 0; i < MaxN; ++i)
		emp[i] = i;
	totemp = MaxN;
	cur = mem + emp[--totemp];
	nil = newNode(0, cur);
	nil->size = 0;
}

void Recycle(Node *p)
{
	if (p == nil)   return;
	Recycle(p->c[0]), Recycle(p->c[1]);
	emp[totemp++] = p - mem;
}
	\end{lstlisting}
	\subsubsection{维护序列}
	一切下标从0开始。\\
	\begin{lstlisting}[language=c++]
struct SplayTree
{
	Node *root;
	void Init()
	{
		root = nil;
	}
	void Pushup(Node *x)
	{
		if (x == nil)   return;
		Pushdown(x); Pushdown(x->c[0]); Pushdown(x->c[1]);
		x->size = x->c[0]->size + x->c[1]->size + 1;
	}
	void Pushdown(Node *x)
	{
		if (x == nil)   return;
		//do something
	}
	void Rotate(Node *x, int f)
	{
		if (x == nil)   return;
		Node *y = x->p;
		y->c[f ^ 1] = x->c[f], x->p = y->p;
		if (x->c[f] != nil)
			x->c[f]->p = y;
		if (y->p != nil)
			y->p->c[y->p->c[1] == y] = x;
		x->c[f] = y, y->p = x;
		Pushup(y);
	}
	void Splay(Node *x, Node *f)
	{
		static Node *stack[maxn];
		int top = 0;
		stack[top++] = x;
		for (Node *y = x; y != f;y = y->p)
			stack[top++] = y->p;
		while (top)
			Pushdown(stack[--top]);

		while (x->p != f)
		{
			Node *y = x->p;
			if (y->p == f)
				Rotate(x, x == y->c[0]);
			else
			{
				int fd = y->p->c[0] == y;
				if (y->c[fd] == x)
					Rotate(x, fd ^ 1), Rotate(x, fd);
				else
					Rotate(y, fd), Rotate(x, fd);
			}
		}
		Pushup(x);
		if (f == nil)
			root = x;
	}
	void Select(int k, Node *f)
	{
		Node *x = root;
		Pushdown(x);
		int tmp;
		while ((tmp = x->c[0]->size) != k)
		{
			if (k < tmp)	x = x->c[0];
			else
				x = x->c[1], k -= tmp + 1;
			Pushdown(x);
		}
		Splay(x, f);
	}
	void Select(int l, int r)
	{
		Select(l, nil), Select(r + 2, root);
	}
	Node *Make_tree(int a[], int l, int r, Node *p)
	{
		if (l > r)  return nil;
		int mid = l + r >> 1;
		Node *x = newNode(a[mid], p);
		x->c[0] = Make_tree(a, l, mid - 1, x);
		x->c[1] = Make_tree(a, mid + 1, r, x);
		Pushup(x);
		return x;
	}
	void Insert(int pos, int a[], int n)
	{
		Select(pos, nil), Select(pos + 1, root);
		root->c[1]->c[0] = Make_tree(a, 0, n - 1, root->c[1]);
		Splay(root->c[1]->c[0], nil);
	}
	void Insert(int v)
	{
		Node *x = root, *y = nil;
		while (x != nil)
		{
			y = x;
			y->size++;
			x = x->c[v >= x->key];
		}
		y->c[v >= y->key] = x = newNode(v, y);
		Splay(x, nil);
	}
	void Remove(int l, int r)
	{
		Select(l, r);
		//Recycle(root->c[1]->c[0]);
		root->c[1]->c[0] = nil;
		Splay(root->c[1], nil);
	}
};
	\end{lstlisting}
	例题：旋转区间赋值求和求最大子序列。\\
	注意打上懒标记后立即Pushup。Pushup(root-c[1]-c[0]),Pushup(root-c[1]),Pushup(root);\\
	\begin{lstlisting}[language=c++]
	void Pushup(Node *x)
	{
		if (x == nil)	return;
		Pushdown(x); Pushdown(x->c[0]); Pushdown(x->c[1]);
		x->size = x->c[0]->size+x->c[1]->size+1;

		x->sum = x->c[0]->sum+x->c[1]->sum+x->key;
		x->lsum = max(x->c[0]->lsum,
			x->c[0]->sum+x->key+max(0,x->c[1]->lsum));
		x->rsum = max(x->c[1]->rsum,
			x->c[1]->sum+x->key+max(0,x->c[0]->rsum));
		x->maxsum = max(max(x->c[0]->maxsum,x->c[1]->maxsum),
			x->key+max(0,x->c[0]->rsum)+max(0,x->c[1]->lsum));
	}
	void Pushdown(Node *x)
	{
		if (x == nil)	return;
		if (x->rev)
		{
			x->rev = 0;
			x->c[0]->rev ^= 1;
			x->c[1]->rev ^= 1;
			swap(x->c[0],x->c[1]);

			swap(x->lsum,x->rsum);
		}
		if (x->same)
		{
			x->same = false;
			x->key = x->lazy;
			x->sum = x->key*x->size;
			x->lsum = x->rsum = x->maxsum = max(x->key,x->sum);
			x->c[0]->same = true, x->c[0]->lazy = x->key;
			x->c[1]->same = true, x->c[1]->lazy = x->key;
		}
	}

int main()
{
	int totcas;
	scanf("%d",&totcas);
	for (int cas = 1;cas <= totcas;cas++)
	{
		Init();
		sp.Init();
		nil->lsum = nil->rsum = nil->maxsum = -Inf;
		sp.Insert(0);
		sp.Insert(0);

		int n,m;
		scanf("%d%d",&n,&m);
		for (int i = 0;i < n;i++)
			scanf("%d",&a[i]);
		sp.Insert(0,a,n);

		for (int i = 0;i < m;i++)
		{
			int pos,tot,c;
			scanf("%s",buf);
			if (strcmp(buf,"MAKE-SAME") == 0)
			{
				scanf("%d%d%d",&pos,&tot,&c);
				sp.Select(pos-1,pos+tot-2);
				sp.root->c[1]->c[0]->same = true;
				sp.root->c[1]->c[0]->lazy = c;
				sp.Pushup(sp.root->c[1]), sp.Pushup(sp.root);
			}
			else if (strcmp(buf,"INSERT") == 0)
			{
				scanf("%d%d",&pos,&tot);
				for (int i = 0;i < tot;i++)
					scanf("%d",&a[i]);
				sp.Insert(pos,a,tot);
			}
			else if (strcmp(buf,"DELETE") == 0)
			{
				scanf("%d%d",&pos,&tot);
				sp.Remove(pos-1,pos+tot-2);
			}
			else if (strcmp(buf,"REVERSE") == 0)
			{
				scanf("%d%d",&pos,&tot);
				sp.Select(pos-1,pos+tot-2);
				sp.root->c[1]->c[0]->rev ^= 1;
				sp.Pushup(sp.root->c[1]), sp.Pushup(sp.root);
			}
			else if (strcmp(buf,"GET-SUM") == 0)
			{
				scanf("%d%d",&pos,&tot);
				sp.Select(pos-1,pos+tot-2);
				printf("%d\n",sp.root->c[1]->c[0]->sum);
			}
			else if (strcmp(buf,"MAX-SUM") == 0)
			{
				sp.Select(0,sp.root->size-3);
				printf("%d\n",sp.root->c[1]->c[0]->maxsum);
			}
		}
	}
	return 0;
}
	\end{lstlisting}
	\subsubsection{维护括号序列}
	不需要哨兵。\\
	\\
	合并操作：\\
	\\
	先转成下面的样子：\\
	\[\pstree[levelsep=35pt]{\Tcircle{lv}}
	{
		\Tcircle{c0}
		\Tcircle{c1}
	}
	~~~~~~~~~~
	\pstree[levelsep=35pt]{\Tcircle{lu}}
	{
		\Tcircle{}
		\pstree[levelsep=35pt]{\Tcircle{ru}}
		{
			\Tcircle{c2}
			\Tcircle{}
		}
	}\]
	再链接成这样：
	\[\pstree[levelsep=35pt]{\Tcircle{lv}}
	{
		\Tcircle{c0}
		\pstree[levelsep=35pt]{\Tcircle{lu}}
		{
			\Tcircle{}
			\pstree[levelsep=35pt]{\Tcircle{ru}}
			{
				\Tcircle{c2}
				\Tcircle{c1}
			}
		}
	}\]
	~\\
	分离操作：\\
	\\
	先把lu和ru转上去：\\
	\[\pstree[levelsep=35pt]{\Tcircle{lu}}
	{
		\pstree[levelsep=35pt]{\Tcircle{c0}}
		{
			\Tcircle{prev}
			\Tcircle{last}
		}
		\pstree[levelsep=35pt]{\Tcircle{ru}}
		{
			\Tcircle{c1}
			\Tcircle{c2}
		}
	}\]
	把c0和c2从原来的位置断开\\
	然后接上：\\
	\[\pstree[levelsep=35pt]{\Tcircle{last}}
	{
		\pstree[levelsep=35pt]{\Tcircle{c0}}
		{
			\Tcircle{prev}
			\Tcircle{}
		}
		\Tcircle{c2}
	}
	~~~~~~~~~~
	\pstree[levelsep=35pt]{\Tcircle{lu}}
	{
		\Tcircle{}
		\pstree[levelsep=35pt]{\Tcircle{ru}}
		{
			\Tcircle{c1}
			\Tcircle{}
		}
	}\]
	\begin{lstlisting}[language=c++]
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 500000;
const int mod = 99990001;
struct Node
{
	int size,key;

	int a,b;
	int minid,id;

	Node *c[2];
	Node *p;
}mem[maxn],*cur,*nil;
Node *l[maxn],*r[maxn];//左括号右括号定义在前面

int emp[maxn],totemp;
Node *newNode(int v,Node *p)
{
	cur->c[0] = cur->c[1] = nil,cur->p = p;
	cur->size = 1;
	cur->key = v;

	cur->a = 1;
	cur->b = 0;
	cur->minid = cur->id = maxn;

	return cur++;
}
void Init()
{
	cur = mem;
	nil = newNode(0,cur);
	nil->size = 0;
}

struct SplayTree
{
	Node *root;
	void Init()
	{
		root = nil;
	}
	void Pushup(Node *x)
	{
		if (x == nil)	return;
		Pushdown(x);
		Pushdown(x->c[0]);
		Pushdown(x->c[1]);
		x->size = x->c[0]->size+x->c[1]->size+1;

		x->minid = x->id;
		for (int i = 0;i < 2;i++)
			if (x->c[i] != nil)
				x->minid = min(x->minid,x->c[i]->minid);
	}
	void Pushdown(Node *x)
	{
		if (x == nil)	return;

		x->key = ((long long)x->key*x->a%mod+x->b)%mod;
		for (int i = 0;i < 2;i++)
			if (x->c[i] != nil)
			{
				x->c[i]->a = (long long)x->c[i]->a*x->a%mod;
				x->c[i]->b = ((long long)x->c[i]->b*x->a%mod+x->b)%mod;
			}
		x->a = 1;
		x->b = 0;
	}
	void Rotate(Node *x,int f)
	{
		if (x == nil)	return;
		Node *y = x->p;
		y->c[f^1] = x->c[f], x->p = y->p;
		if (x->c[f] != nil)
			x->c[f]->p = y;
		if (y->p != nil)
			y->p->c[y->p->c[1] == y] = x;
		x->c[f] = y, y->p = x;
		Pushup(y);
	}
	void Splay(Node *x,Node *f)
	{
		static Node *stack[maxn];
		int top = 0;
		stack[top++] = x;
		for (Node *y = x; y != f;y = y->p)
			stack[top++] = y->p;
		while (top)
			Pushdown(stack[--top]);

		while (x->p != f)
		{
			Node *y = x->p;
			if (y->p == f)
				Rotate(x,x == y->c[0]);
			else
			{
				int fd = y->p->c[0] == y;
				if (y->c[fd] == x)
					Rotate(x, fd^1), Rotate(x,fd);
				else
					Rotate(y,fd), Rotate(x,fd);
			}
		}
		Pushup(x);
		if (f == nil)
			root = x;
	}
	Node *Last(Node *now)
	{
		Splay(now,nil);
		while (now->c[1] != nil)
			now = now->c[1];
		return now;
	}
	//`把u接到v下面去，边权为w`
	//`需要保证u是某棵树的根`
	void Link(int u,int v,int w)
	{
		Splay(l[v],nil);

		Splay(l[u],nil);
		l[u]->key = w;
		Pushup(l[u]);
		Splay(r[u],l[u]);

		Node *c1 = l[v]->c[1];
		l[v]->c[1] = l[u];
		r[u]->c[1] = c1;
		l[u]->p = l[v];
		c1->p = r[u];
		Pushup(r[u]);
		Pushup(l[u]);
		Pushup(l[v]);
		Splay(l[u],nil);
	}
	//`把u为根的子树分离开`
	int Split(int u)
	{
		Splay(l[u],nil);

		int ret = l[u]->key;
		Splay(r[u],l[u]);
		Node *c0 = l[u]->c[0], *c2 = r[u]->c[1]; 

		l[u]->key = 0;//去掉边权
		l[u]->c[0] = r[u]->c[1] = c0->p = c2->p = nil;
		Pushup(r[u]);
		Pushup(l[u]);

		Node *last = Last(c0);
		Splay(last,nil);
		last->c[1] = c2;
		c2->p = last;
		Pushup(last);

		//对拆分后的两部份进行处理
		Node *nu = last;
		Node *nv = l[u];
		if (nu->size > nv->size || (nu->size == nv->size && nu->minid > nv->minid))
			swap(nu,nv);
		nu->a = (long long)nu->a*ret%mod;
		nu->b = (long long)nu->b*ret%mod;
		nv->b = (nv->b+ret)%mod;

		return ret;//返回原边权
	}
};

SplayTree sp;
int n;
struct Edge
{
	int to,next,w,id;
};
Edge edge[maxn];
int head[maxn],L;
int eid[maxn],toid[maxn];

void addedge(int u,int v,int w,int id)
{
	edge[L].to = v;
	edge[L].w = w;
	edge[L].id = id;
	edge[L].next = head[u];
	head[u] = L++;
}

void DFS(int now,int fa)
{
	for (int i = head[now];i != -1;i = edge[i].next)
		if (edge[i].to != fa)
		{
			sp.Link(edge[i].to,now,edge[i].w);
			eid[edge[i].id] = edge[i].to;
			toid[edge[i].id] = now;

			DFS(edge[i].to,now);
		}
}

int main()
{
	Init();
	sp.Init();

	scanf("%d",&n);

	for (int i = 0;i < n;i++)
	{
		l[i] = newNode(0,nil);
		r[i] = newNode(0,nil);
		l[i]->id = r[i]->id = i;
		l[i]->c[1] = r[i], r[i]->p = l[i];
		sp.Pushup(l[i]);

		head[i] = -1;
	}
	L = 0;

	for (int i = 0;i < n-1;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		u--,v--;

		addedge(u,v,w,i);
		addedge(v,u,w,i);
	}

	DFS(0,-1);

	for (int i = 0;i < n-1;i++)
	{
		fflush(stdout);

		int id;
		scanf("%d",&id);
		id--;

		int ret = sp.Split(eid[id]);
		printf("%d\n",ret);
	}

	return 0;
}
	\end{lstlisting} 