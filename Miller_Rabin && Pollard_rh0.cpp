#define C 16381
	ll minn;

	ll multi(ll a,ll b,ll n)
	{
		ll tmp=a%n,s=0;
		while (b)
		{
			if (b&1)
				s=(s+tmp)%n;
			tmp=(tmp+tmp)%n;
			b>>=1;
		}
		return s;
	}

	ll Pow(ll a,ll b,ll n)
	{
		ll tmp=a%n,s=1;
		while (b)
		{
			if (b&1)
				s=multi(s,tmp,n);
			tmp=multi(tmp,tmp,n);
			b>>=1;
		}
		return s;
	}

	int witness(ll a,ll n)
	{
		ll u=n-1,t=0,x,y;
		while (!(u&1))
			u>>=1,t++;
		x=Pow(a,u,n);
		for (int i=1;i<=t;i++)
		{
			y=multi(x,x,n);
			if (y==1&&x!=1&&x!=n-1)
				return 1;
			x=y;
		}
		if (x!=1) return 1;
		return 0;
	}

	int test(ll n)
	{
		ll a;
		int i;
		if (n==2) return 1;
		if (n<2||!(n&1)) return 0;
		srand((ll) time(0));
		for (i=0;i<10;i++)
		{
			a=((ll) rand())%(n-2)+2;
			if (witness(a,n)) return 0;
		}
		return 1;
	}

	ll gcd(ll a, ll b)
	{
		return b?gcd(b,a%b):a;
	}

	ll pollard_rho(ll n, ll c)
	{
		ll x,y,d,i=1,k=2;
		x=((ll) rand())%(n-1)+1;
		y=x;
		while (1)
		{
			i++;
			x=(multi(x,x,n)+c)%n;
			d=gcd(y-x+n,n);
			if (d!=1&&d!=n) return d;
			if (y==x) return n;
			if (i==k) y=x,k<<=1;
		}
		return 0;
	}

	void find(ll n,ll c)	//找最小素因子
	{
		ll r;
		if (n<=1) return;
		if (test(n))
		{
			minn=min(minn,n);
			return ;
		}
		r=pollard_rho(n,c--);
		find(n/r,c);
		find(r,c);
	}


    ll MaxPrimeFactor(ll n)
    {
        if(test(n))
        return n;

        I64 k=-1,g;
        min=n;
        find(n,C);

        g=MaxPrimeFactor(min);
        k=g>k?g:k;

        g=MaxPrimeFactor(n/min);
        k=g>k?g:k;
        return k;
    }


    int main(){
        ll n;
            while(~scanf("%I64d", &n))
            {
                // if(test(n)){                //test(n)测试n是不是素数
                // printf("Prime\n");
                // continue;
                // }
                // min = n;                   //min表示n的最小素因子
                // find(n, C);                //找出n的最小素因子
                // printf("%I64d\n",min);
                printf("%I64d\n",MaxPrimeFactor(n));//求n的最大素因子
            }
        return 0;
    }
