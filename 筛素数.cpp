************************************筛素数*********************************************************
void findPrime(int maxx)
{
    clearAll(flag);
    cnt=0;
    int maxx = 1000000;
     for(int i=2;i<=maxx;++i)
     {
        if(!flag[i]) prime[++cnt]=i;
        for(int j=1;j<=cnt&&i*prime[j]<=maxx;++j)
        {
            flag[i*prime[j]]=1;
            if(i%prime[j]==0) break;
        }
    }
}
***********************************************************************************************
