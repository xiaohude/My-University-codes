#include<iostream.h>
typedef struct node 
{
	int f,n;
	struct node *next;
}qnode;
typedef struct
{
	qnode*front,*rear;
}lqueue;
lqueue *init_lqueue()               //链队的初始化，并且申请了空间。
{
	lqueue *q;
	qnode *p;
	q=new lqueue;
	p=new qnode;
	p->next=NULL;
	q->front=q->rear=p;
	return q;
}
int empty_lqueue(lqueue*q)                       //判断链队是否为空，为空反回1
{
	if(q->front==q->rear)
		return 1;
	else
		return 0;
}
void in_lqueue(lqueue*q,int f,int n)              //入队
{
	qnode *p;
	p=new qnode;
	p->f=f;
	p->n=n;
	p->next=NULL;
	q->rear->next=p;
	q->rear=p;
}
void xianshi(lqueue* q)                 //显示多项式。这里显示之后会把多项式出队为空队。并且不管用不用指针传递都会影响，因为lqueue类型里面是指针!!所以最后决定不用出队函数，直接新编一个。
{
	qnode *i;
	int f,n;
	i=q->front->next;
	f=i->f;
	n=i->n;
	if(f!=0)
	{
	    if(f!=1)
		{
			if(n>1)
			    cout<<f<<"x^"<<n;
			if(n==1)
				cout<<f<<"x";
			if(n==0)
				cout<<f;	
		}
		else
		{
		    if(n>1)
		        cout<<"x^"<<n;
	    	if(n==1)
		   		cout<<"x";
		    if(n==0)
	    		cout<<f;
		}
	}
	else
	{
		cout<<"0";
	}
	//cout<<f<<"x^"<<n;//这里有多余写一遍的目的是让第一项不带正号。
	i=i->next;
	for(;i;i=i->next)	
	{
		f=i->f;
		n=i->n;	
		if(f>0)
		{
			if(f!=1)
			{
			if(n>1)
			    cout<<"+"<<f<<"x^"<<n;
			if(n==1)
				cout<<"+"<<f<<"x";
			if(n==0)
				cout<<"+"<<f;	
			}
			else
			{
			    if(n>1)
			        cout<<"+"<<"x^"<<n;
	    		if(n==1)
		    		cout<<"+"<<"x";
			    if(n==0)
	    			cout<<"+"<<f;
			}
		}
		if(f<0)
		{
			if(n>1)
			    cout<<f<<"x^"<<n;
			if(n==1)
				cout<<f<<"x";
			if(n==0)
				cout<<f;
		}
	}

}
void jianli(lqueue*q)
{
	q->front=q->rear;                 //将即将建立的链表先初始化为空，这样可以第二次使用计算器。
	int f,n;
	cout<<"请输入多项式(系数 指数)。输入0 0 结束\n";
		cout<<"请输入子项系数";
		cin>>f;
		cout<<"请输入子项指数";
		cin>>n;
		cout<<endl;
	if(f==0&&n==0)
	{
		in_lqueue(q,f,n);
		cout<<"建立的多项式为：  0";
		cout<<endl;
		cout<<endl;
		return;
	}

	while(f!=0||n!=0)
	{
        in_lqueue(q,f,n);
		cout<<"请输入子项系数";
		cin>>f;
		cout<<"请输入子项指数";
		cin>>n;
		cout<<endl;
	};
	cout<<"建立的多项式为：  ";
	xianshi(q);
	cout<<endl;
	cout<<endl;
}
int out_lqueue(lqueue*q,int &f,int &n)                 //出队
{
	qnode *p;
	if(empty_lqueue(q))
	{
		return 0;
	}
	else 
	{
		p=q->front->next;                      //有头指针的队列
		q->front->next=p->next;
		f=p->f;
		n=p->n;
		if(q->front->next==NULL)
			q->rear=q->front;
		return 1;
	}
}
/*
lqueue* jia(lqueue a,lqueue* b)        //加法运算。
{
	lqueue c;
	c=a;                               //额，这里用完a后，a就成乱码了啊！？问题出在实参到形参传递的是指针a。c=a之后会影响a。所以不用指针传递了。  不管用不用指针都会影响，因为lqueue类型里面是指针····
	c.rear->next=b->front->next;
	return &c;
}
*/
lqueue* jia(lqueue*a,lqueue*b)          
{
	int f,n;
	lqueue*c;
	qnode *i,*j;
	c=init_lqueue();
	for(i=a->front->next;i;i=i->next)	
	{
		f=i->f;
		n=i->n;	
		in_lqueue(c,f,n);
	}
	for(j=b->front->next;j;j=j->next)
	{
		f=j->f;
		n=j->n;
		in_lqueue(c,f,n);
	}
		return c;
}
lqueue* jian(lqueue*a,lqueue*b)          //这种减法运算的算法是写完乘法后忽然想到的，刚开始写的算法是又重新定义了a1和b1然后对a1和b1进行修改运算。后一种似乎和第一种的时间复杂度一样。只是少定义了两个链表。
{
	int f,n;
	lqueue*c;
	qnode *i,*j;
	c=init_lqueue();
	for(i=a->front->next;i;i=i->next)	
	{
		f=i->f;
		n=i->n;	
		in_lqueue(c,f,n);
	}
	for(j=b->front->next;j;j=j->next)
	{
		f=j->f*-1;
		n=j->n;
		in_lqueue(c,f,n);
	}
		return c;
}
lqueue* cheng(lqueue*a,lqueue*b)
{
	int f,n;
	lqueue*c;
	qnode *i,*j;
	c=init_lqueue();
	for(i=a->front->next;i;i=i->next)
		for(j=b->front->next;j;j=j->next)
		{
			f=i->f*j->f;
			n=i->n+j->n;
			in_lqueue(c,f,n);
		}
		return c;
}
double jisuan(lqueue*q,int x)
{
	qnode *i;
	int f,n,j;
	double y,sum=0;
	for(i=q->front->next;i;i=i->next)	
	{
		y=1;                            //记得y要归一啊。
		f=i->f;
		n=i->n;
		if(n>0)
			for(j=1;j<=n;j++)
				y*=x;
		else
			for(j=-1;j>=n;j--)
				y/=x;
		sum+=(f*y);
	}
	return sum;

}
void C(lqueue*a,lqueue*b)
{
	cout<<endl;
	lqueue *c;
	c=jia(a,b);
	cout<<"                          ";
	cout<<"a+b=";
	xianshi(c);
	cout<<endl;
	cout<<endl;
}
void D(lqueue*a,lqueue*b)
{
	cout<<endl;
	lqueue *c;
	c=jian(a,b);
	cout<<"                          ";
	cout<<"a-b=";
	xianshi(c);
	cout<<endl;
	cout<<endl;
}
void E(lqueue*a,lqueue*b)
{
	cout<<endl;
	lqueue *c;
	c=cheng(a,b);
	cout<<"                          ";
	cout<<"a*b=";
	xianshi(c);
	cout<<endl;
	cout<<endl;
}
void F(lqueue*a,lqueue*b)
{
	cout<<endl;
	int x;
	double sum;
	lqueue *c;
	cout<<"                                ";
	cout<<"请输入x值：";
	cin>>x;

	c=jia(a,b);
	sum=jisuan(c,x);
	cout<<"                          ";
	cout<<"a+b=";
	xianshi(c);
	cout<<"="<<sum<<endl;

	c=jian(a,b);
	sum=jisuan(c,x);
	cout<<"                          ";
	cout<<"a-b=";
	xianshi(c);
	cout<<"="<<sum<<endl;

	c=cheng(a,b);
	sum=jisuan(c,x);
	cout<<"                          ";
	cout<<"a*b=";
	xianshi(c);
	cout<<"="<<sum<<endl;
	cout<<endl;
}
void main()
{
	int k=1;
	char m;
	lqueue *a,*b;
	a=init_lqueue();
	b=init_lqueue();
	while(k)
	{
	cout<<"              ****************************************************"<<endl;
	cout<<"              *                                                  *"<<endl;
	cout<<"              *              欢迎使用多项式运算器                *"<<endl;
	cout<<"              *                                                  *"<<endl;
	cout<<"              ****************************************************"<<endl;
	cout<<"              *                                                  *"<<endl;
	cout<<"              *   *****************        *****************     *"<<endl;
	cout<<"              *   * A.创建多项式a *        * B.创建多项式b *     *"<<endl;
	cout<<"              *   *****************        *****************     *"<<endl;
	cout<<"              *   *****************        *****************     *"<<endl;
	cout<<"              *   * C.  运算a+b   *        * D.  运算a-b   *     *"<<endl;
	cout<<"              *   *****************        *****************     *"<<endl;
	cout<<"              *   *****************        *****************     *"<<endl;
	cout<<"              *   * E.  运算a*b   *        * F.输入x并计算 *     *"<<endl;
	cout<<"              *   *****************        *****************     *"<<endl;
	cout<<"              *               *****************                  *"<<endl;
	cout<<"              *               * G.  推出系统  *                  *"<<endl;
	cout<<"              *               *****************                  *"<<endl;
	cout<<"              ****************************************************"<<endl;
	cout<<"                                   请输入";
	cin>>m;
	switch(m)
	{
	case 'a':jianli(a);break;
	case 'b':jianli(b);break;
	case 'c':C(a,b);break;
	case 'd':D(a,b);break;
	case 'e':E(a,b);break;
	case 'f':F(a,b);break;
	case 'g':k=0;break;
	default:cout<<"                              输入错误请重新输入\n";
	}
	}
}