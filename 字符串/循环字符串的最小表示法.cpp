int find(int a[])
{
	int i=0,j=1,k=0;
	int flag;

	while(i<n&&j<n&&k<n)
	{
	 	flag = a[(i+k)%n] - a[(j+k)%n];

		if(flag==0) k++;
		else
		{
			if(flag>0) i=i+k+1;
			else j=j+k+1;
			if(i==j) j++;
			k = 0;
		}
	}
	return (i<j?i:j);
}