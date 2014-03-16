#include<iostream>
#include<math.h>
#include<fstream>
#define maxn 500
#define oo 99999999

using namespace std;
ifstream fin("input.txt");
ofstream fout("output.txt");


class Fraction                      // 定义分数，并重载运算符 
 {
         
    public:
      int a,b;
      Fraction() {a=0;b=1;}     
      void FractionSimplify();
      Fraction(int x,int y) {a=x; b=y; FractionSimplify(); }
      friend Fraction operator + (Fraction &x,Fraction &y);
      friend Fraction operator - (Fraction &x,Fraction &y);
      friend Fraction operator * (Fraction &x,Fraction &y);
      friend Fraction operator / (Fraction &x,Fraction &y);
      void setdata();
      void display();         
 };

int max(int a,int b)
{
   return((a>b)?a:b);   
}

int min(int a,int b)
{
   return ((a<b)?a:b);    
}

int zdgys(int a,int b)                     //求出两个数的最大公约数，化简用 
{
   if (a%b==0) return b;
    else
     return zdgys(b,a%b);    
}

void Fraction :: FractionSimplify()        //化简分数 
{
 if(a!=0)    
 {
    int py=zdgys(max(a,b),min(a,b));
    a/=py;
    b/=py;
 }  else b=1; 
 
 if (a*b<0) {a=-(int)fabs(a); b=(int)fabs(b);} 
}

void Fraction :: setdata()                  //读入分数的值 
{
  char ch;   
  fin >>a;
  ch=fin.get();
  if (ch!='/') b=1; else fin >>b;
  if (b==0) { fout <<"分母不能为0，请重新输入！"; setdata(); }
  FractionSimplify();
}

void Fraction :: display()                  //输出分数的值 
{
  bool flag=0;   
  if (a*b<0) flag=1;
  if (flag) fout <<"-";
  if (fabs(b)!=1) fout <<fabs(a) <<"/" <<fabs(b);     
   else fout <<fabs(a);
}

 
Fraction operator + (Fraction &x,Fraction &y)        
{
   Fraction z;
   z.a=x.a*y.b+x.b*y.a;
   z.b=x.b*y.b;
   z.FractionSimplify();
   return z;  
}

Fraction operator - (Fraction &x,Fraction &y)
{
   Fraction z;
   z.a=x.a*y.b-x.b*y.a;
   z.b=x.b*y.b;
   z.FractionSimplify();
   return z;        
}

Fraction operator * (Fraction &x,Fraction &y)
{
   Fraction z;
   z.a=x.a*y.a;
   z.b=x.b*y.b;
   z.FractionSimplify();
   return z;        
}


Fraction operator / (Fraction &x,Fraction &y)    
{
   Fraction z;
   z.a=x.a*y.b;
   z.b=x.b*y.a;
   z.FractionSimplify();
   return z;        
}                                                 //重载运算符+-*/ 

Fraction a[maxn][maxn],b[maxn][maxn];                           //定义矩阵，用分数形式存储 
int n,m,num[maxn],xnum[maxn];

void init()                                       //读入矩阵 
{
   fin >>n;
   m=n;
   for (int i=1;i<=n;i++)
    for (int j=1;j<=n;j++)
     a[i][j].setdata();  
     
   for (int i=1;i<=n;i++)
       b[i][i].a=1;   
}

void outit()                                      //输出矩阵 
{
   
     for (int i=1;i<=n;i++)
   {
    for (int j=1;j<=m;j++)
     { b[i][j].display(); fout <<' ';}
     fout <<endl; 
   }
}

void swapIJ(int i,int j)                          //交换i行和j行 
{
   Fraction tmp;  
   for (int x=1;x<=n;x++)
   {
      tmp=a[i][x];
      a[i][x]=a[j][x];
      a[j][x]=tmp;  
       
      tmp=b[i][x];
      b[i][x]=b[j][x];
      b[j][x]=tmp; 
   }     
}

void addKItoJ(int i,int j,Fraction k)                 //将i行乘以k的值加到j行 
{
   Fraction tmp;  
   for (int x=1;x<=n;x++)
    {
        tmp=a[i][x]*k;    
        a[j][x]=a[j][x]+tmp; 
        
        tmp=b[i][x]*k;    
        b[j][x]=b[j][x]+tmp;
    }    
}

void ItoKI(int i,Fraction k)
{
  Fraction tmp;   
    for (int x=1;x<=n;x++)
      { a[i][x]=a[i][x]*k; b[i][x]=b[i][x]*k;}
}

int FindFlag(int i)                                    //找到第i行第一个不为0的数的位置 
{
    for (int x=1;x<=m;x++)
      if (a[i][x].a!=0) return x;
   return 0;   
} 

void transform()                                 //上下翻转矩阵 
{
     for (int i=1;i<=n/2;i++)
       swapIJ(i,n-i+1);
}

void gaosixiaoyuan()
{
     for (int i=1;i<=n;i++)
     {
         int flag;
         flag=FindFlag(i);
         
         if (flag==0) continue;                  //如果全为0则直接跳到下一个循环 
         
         Fraction tmp;
         tmp=a[i][flag];
         for (int k=1;k<=n;k++)  
         {   a[i][k]=a[i][k]/tmp;
             b[i][k]=b[i][k]/tmp;
         }                                     //整行都除以第flag个数的值 
   
         for (int j=i+1;j<=n;j++)                    
          if (a[j][flag].a!=0)
          {
            Fraction  py(0,1);
            py=py-a[j][flag];                  
            addKItoJ(i,j,py); 
          }  
     }     
}

void qksort(int l,int r)                             //将矩阵排序，化为简化行阶梯形矩阵 
{
   int i=l,j=r,x=num[(l+r)/2],t;
   do 
   {
      while (num[i]<x) i++;
      while (num[j]>x) j--;
      if (i<=j)
      {
         t=num[i];
         num[i]=num[j];
         num[j]=t;
         swapIJ(i,j); 
         i++; j--;        
      }
   }  while (i<=j);
   if (l<j) qksort(l,j);
   if (i<r) qksort(i,r);
}

void  DealTheMatrix()                                //找到每一行第一个1，并用快排化简
                                                     //然后统计其自由未知量的个数并命名 
{
   for (int i=1;i<=n;i++)
     num[i]=oo;
        
      for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            if (a[i][j].a!=0)
             {
               num[i]=j;
               break;
             }
   qksort(1,n);  
   
   
   int tt=0;
   for (int i=1;i<=m;i++)
   {     
     int j;  
     xnum[i]=0;  
     for (j=n;j>=1;j--)
        if (a[j][i].a!=0) break;
        
     if (a[j][i].a!=1) {tt++; xnum[i]=tt;}
   }           
}

void work()                                      //矩阵变换 
{
     gaosixiaoyuan();
     transform();
     gaosixiaoyuan();
     transform();
}

int main()
{
    init(); 
    work();
    DealTheMatrix();
    outit();
    return 0;     
}
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
