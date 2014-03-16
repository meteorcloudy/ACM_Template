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
#define maxn 1000
#define	oo 1000000000 
using namespace std;

typedef long long ll;

//计算字符串s与target的匹配位置
string target; //目标字符串,如：abcdefgh
string s;		//待匹配字符串,如：def

int next[maxn]; //记录前i个字符所构成的字串头尾的覆盖程度,0表示由一个字母的长度覆盖
				//如abcdeabc: next[7]=2;
void getNext(const string &s)
{	int l=s.length();
	int index;
	next[0]=-1;
	for (int i=1;i<l;i++)
	{
		index=next[i-1];
		while (index>=0&&s[i]!=s[index+1])
		{
			index=next[index];
		}
		if (s[i]==s[index+1])
		{
			next[i]=index+1;
		}else
		{
			next[i]=-1;
		}
	}
}

int kmp_find(const string& s,const string& target)
{	int l1=s.length();
	int l2=target.length();
	int i=0,j=0;
	while (i<l1&&j<l2)
	{
		if (s[i]==target[j])
		{
			i++; j++;
		} else
		{
			if (i==0) j++; else i=next[i-1]+1;
		}
	}

	if (i==l1) return j-i; else return -1;
}

int main()
{	string s1,s2;
	cin >>s1;
	cin >>s2;
	getNext(s1);
	cout <<kmp_find(s1,s2) <<endl;
	return 0;
}






