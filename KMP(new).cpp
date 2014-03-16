#include <iostream>
#include <stdio.h>
#include <string.h>
#define maxn 100000
using namespace std;

int fail[maxn];
char s1[maxn],s2[maxn]; //s1,s2����0��ʼ�洢


void getFail(char s[maxn],int f[maxn])  //��ȡʧƥָ�룬sΪģʽ��
{
    int n=strlen(s);
    int k,j;
    k=0; j=f[0]=-1;
    while (k<n)
    {
        if (j==-1)
        {
            j++; k++; f[k]=0; continue;
        }

        if (s[k]==s[j])
        {
            j++; k++; f[k]=j; continue;
        }

        j=f[j];
    }
}

int KMP(char a[maxn],char s[maxn],int f[maxn])   //aΪĸ����sΪģʽ����fΪs��ʧƥָ��
{
    int m=strlen(a);
    int n=strlen(s);
    int k=0,j=0;

    while (k<m&&j<n)
    {
        if (j==-1)
        {
            j++; k++; continue;
        }

        if (a[k]==s[j])
        {
            j++; k++; continue;
        }

        j=f[j];
    }
    if (j<n) return -1;
    return k-n;
}



int main()
{
    freopen("C:\\Users\\py\\Desktop\\input.txt","r",stdin);
    scanf("%s%s",s1,s2);
    getFail(s1,fail);

    for (int i=0;i<strlen(s1);i++)
        cout << fail[i] << " ";
    cout << endl;
    printf("%d\n",KMP(s2,s1,fail));
    return 0;
}

























