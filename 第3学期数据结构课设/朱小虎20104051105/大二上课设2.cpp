#include<iostream>
#include<math.h>
#include<string.h>
using namespace std;
#define max 40
#define MAXNODE 40

int mmm=0;
typedef struct                         //��ʼ�õ��ǹ����壬�������Ǿ����ýṹ�壬����������i����¼����������ȼ��� 
{
	char ch;
	int i;
}DataType;
typedef struct bithrnode
{
	DataType data;
	struct bithrnode *lchild;
	struct bithrnode *rchild;
	struct bithrnode *parent;                       //������¼˫�׵�ָ�롣
}bt,*btp;
typedef struct
{
	btp link;
	int flag;
}st;
int M(char c)                               //�������c���ȼ��ĺ�����
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
int panduan(char c)                       //�ж��ַ��Ƿ�Ϊ���ֵĺ��������򷵻�1��
{
	if(c>='0'&&c<='9')
		return 1;
	else
		return 0;
}
void in(btp &t)
{
	btp A[max];
	int a=0;                  //����A������¼���ֵĽڵ����顣n���������������λ������24����������2*10��4����ʼ����ˣ�ֱ�����ǳ�10�Ϳ��ԣ�������ô�鷳�� 
	btp B[max];
	int b=0;                      //����B������¼������Ľڵ����飬����i��¼�������������ȼ���
	char c[max];                    //��ԭʼ�ַ������ַ����顣
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
			A[a]->data.i=A[a]->data.i*10+c[i]-48;       //����ֱ�Ӱ�10�˺��棬��Ϊ��ʼ��data��i����0��
			i++;
			}
			while(panduan(c[i]));
			a++;
		}
		else
		{
			if(c[i]=='(')                //Ŀ������m��ʹ�����ڵ���������������ȼ�������2����������������û�������ˡ�
			{
				m=2;
				i++;                   //i++��Ŀ��������������ַ�������һ���������
				continue;
			}
			if(c[i]==')')               //����������ʹm��0��
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
	b=0;*/                             //������⽨�����Ƿ���ȷ����ʾ������



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
		//	cout<<"�Ⱥ��\n"<<endl;
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
		//	cout<<"�ͺ����\n"<<endl;
			B[b]->rchild=A[b+1];
			B[b+1]->lchild=B[b];
			B[b]->parent->rchild=B[b+1];
			B[b+1]->parent=B[b]->parent;
			B[b]->parent=B[b+1];
		}
		if(B[b]->data.i<B[b+1]->data.i)
		{
		//	cout<<"�Ⱥ�С\n"<<endl;
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
				cout<<"ջ���"<<endl;
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
				cout<<"ջ���"<<endl;
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
	int a[max],i=-1,b;            //������׺���ʽ���ŵ�ǰ��������
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
					a[i]=p->data.i;                   //���ֽ�ջ
                    cout<<p->data.i;
				}
            	else
				{
					
					b=yunsuanfu(a[i-1],p->data.ch,a[i]);  //�������ֳ�ջ��˳��Ѽ�������ջ��
			       	//cout<<"("<<a[i-1]<<p->data.ch<<a[i]<<"="<<b<<")";    //�����Ҵ�����������
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
	cout<<"�����Ķ�����ͼ��Ϊ\n";
	btp q[MAXNODE];
	btp n;                               //������ǵ�����ڵ�Ϊ��ʱ��
	n=new bt;                            //�Ժ�ǵý���һ�����͵ı�������Ҫ��new����������ռ�����á�
	n->data.i=0;
	n->data.ch=' ';
	n->lchild=NULL;
	n->rchild=NULL;

	int f,r,a,b;
	if(t==NULL)
		return;
	f=-1;                 //˳��ջ��ջ���±�
	r=0;                 //��ջ���±�
	a=0;                  //��¼���ǵ�a+1�У�
	b=0;                 //�����ж�����Ƿ�ȫΪ�յı�ǡ�
	q[r]=t;
	for(int j=1;j<=(2<<(4-a))-1;j++)    
				cout<<" ";
	while(f!=r)
	{
		f++;           
		if(q[f]->lchild==NULL&&q[f]->rchild==NULL)  //�����㣬ͬһ������֮��Ŀո���Ӧ��Ϊ2�ģ����ǵ����ڼ��У��η�-1����
            cout<<q[f]->data.i;
    	else
	    	cout<<q[f]->data.ch;
		                                  //��������Ļ��˵Ŀո���Ϊ2�ģ����ǵ����ڼ���-1���η�-1����
		                                  //������Ƶ������һ�п�����ˣ�����֮����һ���ո�
		for(int i=1;i<=(2<<(5-a))-1;i++)
			cout<<" ";
		b=(b||!(q[f]->data.ch==' '));        //b�����ж��Ƿ���һ�㶼Ϊ�գ����Ϊ�գ�ֹͣѭ������ֹ��ѭ����ȥ��
		if((f+1)==(2<<a)-1)               //��������һ�»�����λ���������2��a+1�η�-1��!!!!!!����Ӧ�������������������һ���������
		{
			if(!b)
				break;
		//	cout<<(2<<a)-1;            //��ʾһ���ж��ٽڵ㡣
			a++;
			cout<<"        \n";
			for(int j=1;j<=(2<<4-a)-1;j++)    //��������е����ˡ�Ӧ���ñ����㡣
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
	T=new bt;                        //���ٴ�����������ָ��Ŀռ�Ϳ�ʼ���ˣ�����
	cout<<"��������ʽ��������׺��ʽ�����ԡ�=��������\n";
	in(T);
	cout<<endl;
	cout<<"ǰ׺���ʽΪ��";
	feiqian(T);
	cout<<endl;
	cout<<"��׺���ʽΪ��"; 
	feizhong(T);
	cout<<endl;
	cout<<"��׺���ʽ����ֵΪ��";
	feihou(T);
	cout<<endl;
	ceng(T);
	return 0;
}
