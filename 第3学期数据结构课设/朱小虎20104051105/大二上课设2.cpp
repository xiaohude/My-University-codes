#include<iostream>
#include<math.h>
#include<string.h>
using namespace std;
#define max 40
#define MAXNODE 40

int mmm=0;
typedef struct                         //开始用的是共用体，后来还是决定用结构体，这样可以用i来记录运算符的优先级。 
{
	char ch;
	int i;
}DataType;
typedef struct bithrnode
{
	DataType data;
	struct bithrnode *lchild;
	struct bithrnode *rchild;
	struct bithrnode *parent;                       //用来记录双亲的指针。
}bt,*btp;
typedef struct
{
	btp link;
	int flag;
}st;
int M(char c)                               //计算符号c优先级的函数；
{
	int m;
	switch(c)
	{
	case '+':m=1;break;
	case '-':m=1;break;
	case '/':m=2;break;
	case '*':m=2;break;
	}
	return m; 
}
int panduan(char c)                       //判断字符是否为数字的函数，是则返回1；
{
	if(c>='0'&&c<='9')
		return 1;
	else
		return 0;
}
void in(btp &t)
{
	btp A[max];
	int a=0;                  //数组A用来记录数字的节点数组。n用来标记整形数的位数。像24，这样就是2*10加4；开始想错了，直接在那乘10就可以，不用那么麻烦。 
	btp B[max];
	int b=0;                      //数组B用来记录运算符的节点数组，其中i记录这个运算符的优先级。
	char c[max];                    //放原始字符串的字符数组。
	int m=0;
	for(int i=0;c[i-1]!='=';i++)
	    cin>>c[i];
	i=0;
	while(c[i]!='=')
	{
		if(panduan(c[i]))
		{
			A[a]=new bt;
	        A[a]->data.i=0;
			A[a]->lchild=A[a]->rchild=NULL;
			do
			{
			A[a]->data.i=A[a]->data.i*10+c[i]-48;       //可以直接把10乘后面，因为开始的data。i等于0；
			i++;
			}
			while(panduan(c[i]));
			a++;
		}
		else
		{
			if(c[i]=='(')                //目的是用m来使括号内的所有运算符的优先级都提升2，这样就能区分有没有括号了。
			{
				m=2;
				i++;                   //i++的目的是跳过（这个字符，存下一个运算符；
				continue;
			}
			if(c[i]==')')               //遇到）后再使m归0；
			{
				m=0;
				i++;
				continue;
			}
			B[b]=new bt;
			B[b]->data.ch=c[i];
			B[b]->data.i=M(c[i])+m;
			B[b]->lchild=B[b]->rchild=NULL;
			b++;
			i++;
		}
	}




	int aa=a;
	int bb=b;
	a=0;b=0;
/*	for(;a<aa;a++)
		cout<<A[a]->data.i<<endl;
	for(;b<bb;b++)
		cout<<B[b]->data.ch<<endl;
	b=0;*/                             //用来检测建立的是否正确的显示函数；



	t->rchild=B[0];
	B[0]->parent=t;
	while(b<bb)
	{
		if(B[b]->lchild==NULL)
		{
			B[b]->lchild=A[b];
		}
		if(b+1==bb)
		{
			B[b]->rchild=A[b+1];
			break;
		}
		if(B[b]->data.i>B[b+1]->data.i)
		{
		//	cout<<"比后大\n"<<endl;
			B[b]->rchild=A[b+1];
			if(B[b]->parent==t)
			{
			B[b+1]->lchild=B[b];
			B[b]->parent->rchild=B[b+1];
			B[b+1]->parent=B[b]->parent;
			B[b]->parent=B[b+1];
			}
			else
			{
				B[b+1]->lchild=B[b]->parent;
				B[b]->parent->parent->rchild=B[b+1];
				B[b+1]->parent=B[b]->parent->parent;
				B[b]->parent=B[b+1];
			}
		}
		if(B[b]->data.i==B[b+1]->data.i)
		{
		//	cout<<"和后相等\n"<<endl;
			B[b]->rchild=A[b+1];
			B[b+1]->lchild=B[b];
			B[b]->parent->rchild=B[b+1];
			B[b+1]->parent=B[b]->parent;
			B[b]->parent=B[b+1];
		}
		if(B[b]->data.i<B[b+1]->data.i)
		{
		//	cout<<"比后小\n"<<endl;
			B[b]->rchild=B[b+1];
			B[b+1]->parent=B[b];
			B[b+1]->lchild=A[b+1];
		}
		b++;
	}
	t=t->rchild;
}
int feiqian(btp t)
{
	btp stack[MAXNODE],p;
	int top;
	if(t==NULL)
		return 1;
	top=-1;
	p=t;
	while (!(p==NULL&&top==-1))
	{
		while(p!=NULL)
		{
			if(p->lchild==NULL&&p->rchild==NULL)
                cout<<p->data.i;
        	else
        		cout<<p->data.ch;
			if(top<MAXNODE-1)
			{
				top++;
				stack[top]=p;
			}
			else
			{
				cout<<"栈溢出"<<endl;
				return 0;
			}
			p=p->lchild;
		}
		if(top==-1)
			return 1;
		else
		{
			p=stack[top];
			top--;
			p=p->rchild;
		}
	}
	return 0;
}


int feizhong(btp t)
{
	btp stack[MAXNODE],p;
	int top;
	if(t==NULL)
		return 1;
	top=-1;
	p=t;
	while (!(p==NULL&&top==-1))
	{
		while(p!=NULL)
		{
			if(top<MAXNODE-1)
			{
				top++;
				stack[top]=p;
			}
			else
			{
				cout<<"栈溢出"<<endl;
				return 0;
			}
			p=p->lchild;
		}
		if(top==-1)
			return 1;
		else
		{
			p=stack[top];
			top--;
			if(p->lchild==NULL&&p->rchild==NULL)
                cout<<p->data.i;
        	else
        		cout<<p->data.ch;
			p=p->rchild;
		}
	}
return 0;
}
int yunsuanfu(int a,char c,int b)
{
	if(c=='+'){return (a+b);}
	else if(c=='-'){return (a-b);}
	else if(c=='*'){return (a*b);}
	else if(c=='/'){return (a/b);}
}
int feihou(btp t)
{
	st stack[MAXNODE];
	btp p;
	int top,sign;
	int a[max],i=-1,b;            //用来后缀表达式符号的前两个数字
	if(t==NULL)
		return 1;
	top=-1;
	p=t;
	while (!(p==NULL&&top==-1))
	{
		if(p!=NULL)
		{
			top++;
			stack[top].link=p;
			stack[top].flag=1;
			p=p->lchild;
		}
		else
		{
			p=stack[top].link;
			sign=stack[top].flag;
			top--;
			if(sign==1)    
			{
				top++;
				stack[top].link=p;
			    stack[top].flag=2;
				p=p->rchild;
			}
			else 
			{
				if(p->lchild==NULL&&p->rchild==NULL)
				{
					i++;
					a[i]=p->data.i;                   //数字进栈
                    cout<<p->data.i;
				}
            	else
				{
					
					b=yunsuanfu(a[i-1],p->data.ch,a[i]);  //两个数字出栈，顺便把计算结果进栈；
			       	//cout<<"("<<a[i-1]<<p->data.ch<<a[i]<<"="<<b<<")";    //用来找错的输出函数；
					i--;                                   
					a[i]=b;
            		cout<<p->data.ch;
				}
				p=NULL;
			}	
		}
	}
	cout<<"="<<a[0];
return 0;
}
void ceng(btp t)
{
	cout<<"建立的二叉树图形为\n";
	btp q[MAXNODE];
	btp n;                               //用来标记当这个节点为空时。
	n=new bt;                            //以后记得建立一个类型的变量后需要用new来给它申请空间才能用。
	n->data.i=0;
	n->data.ch=' ';
	n->lchild=NULL;
	n->rchild=NULL;

	int f,r,a,b;
	if(t==NULL)
		return;
	f=-1;                 //顺序栈出栈的下标
	r=0;                 //进栈的下标
	a=0;                  //记录这是第a+1行；
	b=0;                 //用来判断这层是否全为空的标记。
	q[r]=t;
	for(int j=1;j<=(2<<(4-a))-1;j++)    
				cout<<" ";
	while(f!=r)
	{
		f++;           
		if(q[f]->lchild==NULL&&q[f]->rchild==NULL)  //经计算，同一行数据之间的空格数应该为2的（这是倒数第几行）次方-1个。
            cout<<q[f]->data.i;
    	else
	    	cout<<q[f]->data.ch;
		                                  //而距离屏幕左端的空格数为2的（这是倒数第几行-1）次方-1个。
		                                  //这样设计的是最后一行靠最左端，数据之间间隔一个空格。
		for(int i=1;i<=(2<<(5-a))-1;i++)
			cout<<" ";
		b=(b||!(q[f]->data.ch==' '));        //b用来判断是否这一层都为空，如果为空，停止循环，防止死循环下去。
		if((f+1)==(2<<a)-1)               //这里用了一下汇编的移位算数，算出2的a+1次方-1。!!!!!!这里应该算的是总数，不是这一层的数量。
		{
			if(!b)
				break;
		//	cout<<(2<<a)-1;            //显示一共有多少节点。
			a++;
			cout<<"        \n";
			for(int j=1;j<=(2<<4-a)-1;j++)    //这里计算有点乱了。应该拿笔算算。
				cout<<" ";
			b=0;
		}
		if(q[f]->lchild!=NULL)
		{
			r++;
		    q[r]=q[f]->lchild;
		}
		else
		{
			r++;
			q[r]=n;
		}
		if(q[f]->rchild!=NULL)
		{
			r++;
		    q[r]=q[f]->rchild;
		}
		else
		{
			r++;
			q[r]=n;
		}
	}
}
int main()
{
	btp T;
	T=new bt;                        //你再次忘记了申请指针的空间就开始用了！！！
	cout<<"请输入表达式：（以中缀形式输入以‘=’结束）\n";
	in(T);
	cout<<endl;
	cout<<"前缀表达式为：";
	feiqian(T);
	cout<<endl;
	cout<<"中缀表达式为："; 
	feizhong(T);
	cout<<endl;
	cout<<"后缀表达式并求值为：";
	feihou(T);
	cout<<endl;
	ceng(T);
	return 0;
}
