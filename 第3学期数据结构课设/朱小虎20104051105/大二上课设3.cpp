#include<iostream>
#include<fstream>
#include<time.h>
using namespace std;
#include<string>
#define max 1000
typedef struct
{
	int data[max+1];
	int length;
}ST;
typedef struct             
{
	int m,n;
	string name;
}paixu;               //用来记录排序过程中比较次数和交换次数。
                     //编程过程中记录比较次数的时候不能用&&（p。m++）那样影响一点排序结果，直接用逗号就可以，最终判断语句是判断最后一个逗号之后的语句！也就是说把p.m++放到判断语句之前用逗号隔开就好啦。
void ziranshu()          //用来向文件中写入n个随机自然数···
{

	int x[1000];
    srand( (unsigned)time( NULL ) );
/******************************************************************/
 //产生1000个3位自然随机数
/******************************************************************/
    for(int i=0;i<1000;i++)
	{   
        x[i]=rand();
        while(x[i]>1000||x[i]<=0)
            x[i]=rand();
	}
	ofstream outfile("fff.txt",ios::out);
	if(!outfile)
	{
		cout<<"打开文件错误。";
		exit(1);
	}
	for(i=0;i<1000;i++)
	{   
        outfile<<x[i]<<" ";
		if(x[i]==0)
			break;
	}
	cout<<"建立随机自然数完毕\n";
}
void baocun(ST*t)          //向文件里保存排序好的学生信息
{
	ofstream outfile("ffffff.txt",ios::out);
	if(!outfile)
	{
		cout<<"打开文件错误。";
		exit(1);
	}
	for(int i=1;i<=max;i++)
	{
		outfile<<t->data[i]<<" ";
		if(t->data[i]==0)
			break;
	}
	cout<<"\n保存完毕\n";
}
ST* jianli()         //建立顺序表（从文件里读入）
{
	ST *t;
	t=new ST;
	t->length=0;
	ifstream infile("fff.txt",ios::in);
	if(!infile)
	{
		cout<<"打开文件错误。";
		exit(1);
	}
	for(int i=1;i<=max;i++)
	{
		infile>>t->data[i];
		if(t->data[i]==0)
			break;
		t->length++;	
	}
	return t;
}
void shuchu(ST*t)
{
	for(int i=1;i<=t->length;i++)
		cout<<t->data[i]<<" ";
	cout<<endl;
}
ST * huanyuan(ST*T)                  // 还原t为原来的数据
{
	ST *t;
	t=new ST;
	t->length=0;
	for(int i=1;i<=T->length;i++)
	{
		t->data[i]=T->data[i];
		if(t->data[i]==0)
			break;
		t->length++;	
	}
	return t;
}
paixu insert(ST*t)                     //直接插入排序方法
{
	paixu p;
	p.m=0,p.n=0;
	p.name="直接插入排序";
	for(int i=2;i<=t->length;i++)
		if(p.m++,t->data[i]<t->data[i-1])
		{
			t->data[0]=t->data[i];
			p.n++;
			for(int j=i-1;p.m++,t->data[0]<t->data[j];j--)
			{
				t->data[j+1]=t->data[j];
				p.n++;
			}
			t->data[j+1]=t->data[0];
			p.n++;
		}
//	cout<<"元素比较次数为"<<p.m<<"元素移动次数为"<<p.n<<endl;
	return p;
}
paixu select(ST*t)                //选择排序方法
{
	paixu p;
	p.m=0,p.n=0;
	p.name="选择排序";
	int i,j,k;
	for(i=1;i<t->length;i++)
	{
		for(k=i,j=i+1;j<=t->length;j++)
			if(p.m++,t->data[j]<t->data[k])
				k=j;
		if(i!=k)
		{
			t->data[0]=t->data[k];p.n++;
			t->data[k]=t->data[i];p.n++;
			t->data[i]=t->data[0];p.n++;
		}
	}
//	cout<<"元素比较次数为"<<p.m<<"元素移动次数为"<<p.n<<endl;
	return p;
}
paixu bubble(ST*t)             //冒泡排序方法
{
	paixu p;
	p.m=0,p.n=0;
	p.name="冒泡排序";
	int i,j,s;
	for(i=1;i<t->length;i++)
	{
		s=0;
		for(j=1;j<=t->length-i;j++)
			if(p.m++,t->data[j]>t->data[j+1])
			{
				t->data[0]=t->data[j];p.n++;
		    	t->data[j]=t->data[j+1];p.n++;
		    	t->data[j+1]=t->data[0];p.n++;
				s=1;
			}
			if(s==0)
				break;
	}
//	cout<<"元素比较次数为"<<p.m<<"元素移动次数为"<<p.n<<endl;
	return p;
}
paixu shell(ST*t,int dk)             // 希尔排序方法
{
	paixu p;
	p.m=0,p.n=0;
	p.name="希尔排序";
	int i,j;
	for(i=dk+1;i<=t->length;i++)
		if(p.m++,t->data[i]<t->data[i-dk])
		{
			t->data[0]=t->data[i];p.n++;
         	for(j=i-dk;p.m++,j>0&&(t->data[0]<t->data[j]);j=j-dk)
			{
	        	t->data[j+dk]=t->data[j];p.n++;
			}
        	t->data[j+dk]=t->data[0];p.n++;
		}
	return p;
}
paixu Shell(ST*t)
{
	paixu p,q;
	p.m=0,p.n=0;
	p.name="希尔排序";
	int dk;
	for(dk=t->length;dk>=1;dk/=2)
	{
		q=shell(t,dk);
		p.m+=q.m;
		p.n+=q.n;
	}
//	cout<<"元素比较次数为"<<p.m<<"元素移动次数为"<<p.n<<endl;
	return p;
}
paixu pt(ST*t,int i,int j,int &n)              //快速排序算法,用n来返回支点记录
{
	paixu p;
	p.m=0,p.n=0;
	p.name="快速排序";
	t->data[0]=t->data[i];
	p.n++;
	while(i<j)
	{
		while(i<j&&(p.m++,t->data[j]>=t->data[0]))j--;
		if(i<j)
		{
			t->data[i]=t->data[j];
			p.n++;
			i++;
		}
		while(i<j&&(p.m++,t->data[i]<t->data[0]))i++;
		if(i<j)
		{
			t->data[j]=t->data[i];
			p.n++;
			j--;
		}
	}
	t->data[i]=t->data[0];
	p.n++;
	n=i;               //记录支点的下标
	return p;
}
paixu P;                  //全局变量

paixu quick(ST*T,int s,int t)
{
	paixu q;
	int n;
	if(s<t)
	{
		q=pt(T,s,t,n);
		P.n+=q.n;
		P.m+=q.m;
		quick(T,s,n-1);                         //这里不需要再累加了，因为没次递归调用的时候就上一条语句的p有用；
		quick(T,n+1,t);
	}
	return P;
}
paixu Quick(ST*t)
{
	paixu p;
//	p.m=0,p.n=0;
//	p.name="快速排序方法";
	P.m=0;
    P.n=0;
    P.name="快速排序";
	p=quick(t,1,t->length);
//	cout<<"元素比较次数为"<<p.m<<"元素移动次数为"<<p.n<<endl;
	return p;
}

paixu head(ST*T,int s,int t)                //堆排序
{
	paixu p;
	p.m=0,p.n=0;
	p.name="堆排序";
	int i,j;
	int rc;
	rc=T->data[s];p.n++;i=s;
	for(j=2*i;j<=t;j=j*2)
	{
		if(j<t&&(p.m++,T->data[j]<T->data[j+1]))
			j=j+1;
		if(p.m++,rc>T->data[j])
			break;
		T->data[i]=T->data[j];
		p.n++;
		i=j;
	}
	T->data[i]=rc;
	p.n++;
	return p;
}
paixu heap(ST*t)
{
	paixu p,q;
	p.m=0,p.n=0;
	p.name="堆排序";
	int i;
	for(i=(t->length/2);i>0;i--)
	{
		q=head(t,i,t->length);
		p.m+=q.m;
		p.n+=q.n;
	}
	for(i=t->length;i>1;i--)
	{
		t->data[0]=t->data[1];p.n++;
		t->data[1]=t->data[i];p.n++;
		t->data[i]=t->data[0];p.n++;
		q=head(t,1,i-1);
		p.m+=q.m;
		p.n+=q.n;
	}
//	cout<<"元素比较次数为"<<p.m<<"元素移动次数为"<<p.n<<endl;
	return p;
}
void merge(int T[],int T1[],int s,int m,int t)               //归并排序算法
{

	int i,j,k;
	i=s;
	j=m+1;
	k=s;
	while(i<=m&&j<=t)
		if((P.m)++,T[i]<T[j])
		{
			T1[k]=T[i];
			P.n++;
			k++;
			i++;
		}
		else
		{
			T1[k]=T[j];
			P.n++;
			k++;
			j++;
		}
	while(i<=m)
	{
		T1[k]=T[i];
		P.n++;
		k++;
		i++;
	}
	while(j<=t)
	{
		T1[k]=T[j];
		P.n++;
		k++;
		j++;
	}			
}
void mp(int r[],int r1[],int len,int n)
{
	
	int i;
	for(i=1;i+2*len-1<=n;i=i+2*len)
		merge(r,r1,i,i+len-1,i+2*len-1);
	//		cout<<len<<"  11111"<<endl;             //是在这个for语句最后一次的时候len变的696；因为那时候r1的空间最多为max所以就把最后一个数据存在了实参len的位置上，导致len的值变了···
	if(i+len-1<n)
		merge(r,r1,i,i+len-1,n);
	else
		if(i<=n)
			while(i<=n)
			{
				r1[i++]=r[i++];
				P.n++;
			}
}
paixu ms(ST*t)
{
	paixu p;
	P.m=0,P.n=0;
	P.name="归并排序";
	int len=1;
	int r1[max+1];                         //这个一定记得是max+1因为在ST中的data数据就是【max+1】。如果缺少空间，有可能会把其他的变量的空间占用了，这样会莫名奇妙的改变其他的变量。以后记得一定要申请够空间。并且得清楚需要申请多少空间。
	while(len<t->length)
	{
		mp(t->data,r1,len,t->length);
		len=2*len;
		mp(r1,t->data,len,t->length);
	}
	p.m=P.m;
	p.n=P.n;
	p.name=P.name;
//	cout<<"元素比较次数为"<<p.m<<"元素移动次数为"<<p.n<<endl;
	return p;
}
void main()
{
	ziranshu();
	
	paixu a[8];     //用来记录每种排序的比较次数和交换次数的数组
	int i=1;
	ST *T,*t;
	T=jianli();
	cout<<"请输入数组长度length的值";
	cin>>T->length;
	cout<<"原信息\n";
	shuchu(T);
	cout<<"\n直接插入排序\n";
	t=huanyuan(T);
	a[i]=insert(t);i++;
	shuchu(t);
	cout<<"\n选择排序\n";
	t=huanyuan(T);
	a[i]=select(t);i++;
	shuchu(t);
	cout<<"\n冒泡排序\n";
	t=huanyuan(T);
	a[i]=bubble(t);i++;
	shuchu(t);
	cout<<"\n希尔排序\n";
	t=huanyuan(T);
	a[i]=Shell(t);i++;
	shuchu(t);
	cout<<"\n快速排序\n";
	t=huanyuan(T);
	a[i]=Quick(t);i++;
	shuchu(t);
	cout<<"\n堆排序\n";
	t=huanyuan(T);
	a[i]=heap(t);i++;
	shuchu(t);
	cout<<"\n归并排序\n";
	t=huanyuan(T);
	a[i]=ms(t);i++;
	shuchu(t);
/*	for(i=1;i<=7;i++)
	{
		cout<<a[i].name;
		cout<<"的元素比较次数为"<<a[i].m<<"元素移动次数为"<<a[i].n<<endl;
	}*/
    baocun(t);
	cout<<"\n按比较次数升序排序7中排序方法（排序数据为"<<t->length<<"）时："<<endl;
	for(i=2;i<=7;i++)
		if(a[i].m<a[i-1].m)
		{
			a[0]=a[i];
			for(int j=i-1;a[0].m<a[j].m;j--)
				a[j+1]=a[j];
			a[j+1]=a[0];
		}
	
	i=1;
	cout<<" ****************************************************************************\n";
	cout<<" **    排序方法    **  比较次数  **  移动次数  **  比较次数与移动次数之和  **\n";
	cout<<" ****************************************************************************\n";
	cout<<" **    "<<a[i].name<<"    **     "<<a[i].m<<"    **    "<<a[i].n<<"     **         "<<a[i].n+a[i].m<<"          **\n";i++;
	cout<<" ****************************************************************************\n";
	cout<<" **    "<<a[i].name<<"    **     "<<a[i].m<<"    **    "<<a[i].n<<"     **         "<<a[i].n+a[i].m<<"          **\n";i++;
	cout<<" ****************************************************************************\n";
	cout<<" **    "<<a[i].name<<"      **     "<<a[i].m<<"    **    "<<a[i].n<<"     **         "<<a[i].n+a[i].m<<"          **\n";i++;
	cout<<" ****************************************************************************\n";
	cout<<" **    "<<a[i].name<<"    **     "<<a[i].m<<"    **    "<<a[i].n<<"     **         "<<a[i].n+a[i].m<<"          **\n";i++;	
	cout<<" ****************************************************************************\n";
	cout<<" **  "<<a[i].name<<"  **     "<<a[i].m<<"    **    "<<a[i].n<<"     **         "<<a[i].n+a[i].m<<"          **\n";i++;	
	cout<<" ****************************************************************************\n";
	cout<<" **    "<<a[i].name<<"    **     "<<a[i].m<<"    **    "<<a[i].n<<"     **         "<<a[i].n+a[i].m<<"          **\n";i++;
	cout<<" ****************************************************************************\n";
	cout<<" **    "<<a[i].name<<"    **     "<<a[i].m<<"    **    "<<a[i].n<<"     **         "<<a[i].n+a[i].m<<"          **\n";i++;
	cout<<" ****************************************************************************\n";





	paixu p;
	int b[5]={10,30,50,100,1000};
	cout<<"\n直接插入排序\n";
	cout<<" ************************************************************************\n";
	cout<<" **  排序个数  **  比较次数  **  移动次数  **  比较次数与移动次数之和  **\n";
	cout<<" ************************************************************************\n";
	for(int j=0;j<5;j++)
	{
		T->length=b[j];
		t=huanyuan(T);
		p=insert(t);
	cout<<" **     "<<b[j]<<"    **     "<<p.m<<"    **    "<<p.n<<"     **         "<<p.n+p.m<<"          **\n";
	cout<<" ************************************************************************\n";
	}
	 


	cout<<"\n选择排序\n";
	cout<<" ************************************************************************\n";
	cout<<" **  排序个数  **  比较次数  **  移动次数  **  比较次数与移动次数之和  **\n";
	cout<<" ************************************************************************\n";
	for(j=0;j<5;j++)
	{
		T->length=b[j];
		t=huanyuan(T);
		p=select(t);
	cout<<" **     "<<b[j]<<"    **     "<<p.m<<"    **    "<<p.n<<"     **         "<<p.n+p.m<<"          **\n";
	cout<<" ************************************************************************\n";
	}


	cout<<"\n冒泡排序\n";
	cout<<" ************************************************************************\n";
	cout<<" **  排序个数  **  比较次数  **  移动次数  **  比较次数与移动次数之和  **\n";
	cout<<" ************************************************************************\n";
	for(j=0;j<5;j++)
	{
		T->length=b[j];
		t=huanyuan(T);
		p=bubble(t);
	cout<<" **     "<<b[j]<<"    **     "<<p.m<<"    **    "<<p.n<<"     **         "<<p.n+p.m<<"          **\n";
	cout<<" ************************************************************************\n";
	}


	cout<<"\n希尔排序\n";
	cout<<" ***********************************************************************\n";
	cout<<" **  排序个   **  比较次数  **  移动次数  **  比较次数与移动次数之和  **\n";
	cout<<" ***********************************************************************\n";
	for(j=0;j<5;j++)
	{
		T->length=b[j];
		t=huanyuan(T);
		p=Shell(t);
	cout<<" **     "<<b[j]<<"    **     "<<p.m<<"    **    "<<p.n<<"     **         "<<p.n+p.m<<"          **\n";
	cout<<" ************************************************************************\n";
	}


	cout<<"\n快速排序\n";
	cout<<" ************************************************************************\n";
	cout<<" **  排序个数  **  比较次数  **  移动次数  **  比较次数与移动次数之和  **\n";
	cout<<" ************************************************************************\n";
	for(j=0;j<5;j++)
	{
		T->length=b[j];
		t=huanyuan(T);
		p=Quick(t);
	cout<<" **     "<<b[j]<<"    **     "<<p.m<<"    **    "<<p.n<<"     **         "<<p.n+p.m<<"          **\n";
	cout<<" ************************************************************************\n";
	}


	cout<<"\n堆排序\n";
	cout<<" ************************************************************************\n";
	cout<<" **  排序个数  **  比较次数  **  移动次数  **  比较次数与移动次数之和  **\n";
	cout<<" ***********************************************************************\n";
	for(j=0;j<5;j++)
	{
		T->length=b[j];
		t=huanyuan(T);
		p=heap(t);
	cout<<" **     "<<b[j]<<"    **     "<<p.m<<"    **    "<<p.n<<"     **         "<<p.n+p.m<<"          **\n";
	cout<<" ************************************************************************\n";
	}


	cout<<"\n归并排序\n";
	cout<<" ************************************************************************\n";
	cout<<" **  排序个数  **  比较次数  **  移动次数  **  比较次数与移动次数之和  **\n";
	cout<<" ************************************************************************\n";
	for(j=0;j<5;j++)
	{
		T->length=b[j];
		t=huanyuan(T);
		p=ms(t);
	cout<<" **     "<<b[j]<<"    **     "<<p.m<<"    **    "<<p.n<<"     **         "<<p.n+p.m<<"          **\n";
	cout<<" ************************************************************************\n";
	}
}
