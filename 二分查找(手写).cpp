二分：
	二分查找（元素是否在序列中）：
	int bsearch(int *A,int l,int r,int x)  //注意：查找的区间左闭右开[l,r）!!  为升序排列！
	{	int m;
		while (l<r)
		{	m=(l+r)/2;
			if (A[m]==x) return m;
			if (A[m]>x) r=m; else l=m+1;			
		}
		return -1;
	}

	二分查找下界（即查找第一个元素可插入的位置使序列仍然有序）：


int a[] = {0, 1, 1 , 1, 1, 2};

int  lower_bound(int *A,int l,int r,int x) {
	int m;
	while (l<r){
		m=(l+r)/2;
		if (A[m]>=x) r=m; else l=m+1;
	}
	return l;
}

int  upper_bound(int *A,int l,int r,int x) {
	int m;
	while (l<r){
		m=(l+r)/2;
		if (A[m]>x) r=m; else l=m+1;
	}
	return r;
}

int main() {
	
	cout << lower_bound(a, 0, 6, 0) << endl;   //  0
	cout << upper_bound(a, 0, 6, 0) << endl;   //  1
	cout << lower_bound(a, 0, 6, 1) << endl;   //  1 
	cout << upper_bound(a, 0, 6, 1) << endl;   //  5
}


