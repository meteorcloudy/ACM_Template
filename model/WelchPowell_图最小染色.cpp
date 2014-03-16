#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
int n;
int color[100];// 顶点i涂得颜色
int col_kinds;
int link[100][100];
class Nodes
{
public:
    int degree;
    int index;
    bool operator>(const Nodes &n)
    {
        return degree>n.degree;
    }
};

bool cmp(const Nodes &m,const Nodes &n)
{
    return m.degree>n.degree;
}
Nodes p[100];


bool Check_ok(int i,int j)
{
    int k;
    if(link[p[i].index][p[j].index]!=0||color[j]!=0) return false;//相连的情况
    for(k=0; k<j; k++)
    {
        if(link[p[i].index][p[k].index]==0&&link[p[k].index][p[j].index]!=0)//与已经涂的点相连
            return false;
    }
    return true;
}

void Welech_Powell()
{
    int i,j;

    for(i=0; i<n; i++)
    {
        if(color[i]==0)
        {
            color[i]=++col_kinds;
            for(j=0; j<n; j++)
            {
                if(Check_ok(i,j))
                {
                    color[j]=col_kinds;
                }
            }
        }

    }
}

int main()
{
    int i,j,e,k;
    while(cin>>n>>e)
    {
        col_kinds=0;
        memset(link,0,sizeof(link));
        memset(color,0,sizeof(color));
        for(k=0; k<e; k++)
        {
            cin>>i>>j;
            link[i][j]=link[j][i]=1;
        }
        for(i=0; i<n; i++)
        {
            for(j=0; j<n; j++)
                cout<<link[i][j]<<" ";
            cout<<endl;
        }

        for(i=0; i<n; i++)
        {
            p[i].index=i;
            p[i].degree=0;
            for(j=0; j<n; j++)
                p[i].degree+=link[i][j];
        }

        sort(p,p+n,cmp);
        Welech_Powell();
        cout<<col_kinds<<endl;
        for(i=0; i<n; i++)
            cout<<p[i].index<<" "<<color[i]<<" "<<endl;
    }
    return 0;
}
