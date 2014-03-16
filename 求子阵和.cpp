#define clearAll(a) memset(a,0,sizeof(a))
#define lowbit(x) ((x)&(-x))
#define maxn 100
typedef int elem_t;

struct MatrixSum
{	elem_t a[maxn][maxn],c[maxn][maxn],ret;
	int m,n,t;
	void init(int i,int j)
	{	clearAll(a); clearAll(c); n=i; m=j;}
	void update(int i,int j,int v) //v为增量
	{	i--; j--;
		for (a[i++][j++]+=v,t=j;i<=n;i+=lowbit(i))
			for (j=t;j<=m;c[i-1][j-1]+=v,j+=lowbit(j));
	}

	elem_t query(int i,int j)  //i,j为右下角坐标
	{
		for (ret=0,t=j;i;i^=lowbit(i))
			for (j=t;j;ret+=c[i-1][j-1],j^=lowbit(j));
		return ret;
	}
};
*********************test************************
int n,m;
int main()
{	scanf("%d %d",&n,&m);
	MatrixSum py;
	py.init(n,m);
	int x;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			scanf("%d",&x);
			py.update(i,j,x);
		}
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
			printf("%d ",py.query(i,j));
		printf("\n");
	}
	return 0;
}
