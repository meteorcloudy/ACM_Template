***************************************矩阵快速幂******************************************************
#define maxn 105
typedef long long ll;
void Mul(ll res[][maxn],ll a[][maxn],ll b[][maxn],int n)		// res=a*b 
{
	ll tmp[maxn][maxn]={0};
	for(int i=0;i<n;i++)
		for(int k=0;k<n;k++)
			for(int j=0;j<n;j++)
			{
				tmp[i][j]+=a[i][k]*b[k][j];
				tmp[i][j]%=MOD;
			}
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			res[i][j]=tmp[i][j];
}

void Pow(ll res[][maxn],ll a[][maxn],ll x,int n) // res = a^x 
{
	ll tmp[maxn][maxn]={0};
	for(int i=0;i<maxn;i++)
		tmp[i][i]=1;
	while(x)
	{
		if(x%2)
			Mul(tmp,a,tmp,n);
		x/=2;
		Mul(a,a,a,n);
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			res[i][j]=tmp[i][j];
}
*********************************************************************************************
