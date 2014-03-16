void tarjan(int i){
	DFN[i] = LOW[i] = ++step;
	stack[++top] =  i ;
	visit[i] = true;
	for (int j = 1 ; j <= n ; j++)
		if (link[i][j])
		{
			if (!DFN[j])
			{
				tarjan(j);
				if (LOW[j] < LOW[i])
					LOW[i]  = LOW[j];
			}
			else
			{
				if (visit[j] && DFN[j] < LOW[i] )
					LOW[i] = DFN[j];
			}
		}
	if (DFN[i] == LOW[i])
	{
		Cnt ++ ;
		do
		{
			j = stack[top--];
			visit[j] = false;
			Belong[j] = Cnt;
		}
		while (j!=i);
	}
}
