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
lqueue *init_lqueue()               //���ӵĳ�ʼ�������������˿ռ䡣
{
	lqueue *q;
	qnode *p;
	q=new lqueue;
	p=new qnode;
	p->next=NULL;
	q->front=q->rear=p;
	return q;
}
int empty_lqueue(lqueue*q)                       //�ж������Ƿ�Ϊ�գ�Ϊ�շ���1
{
	if(q->front==q->rear)
		return 1;
	else
		return 0;
}
void in_lqueue(lqueue*q,int f,int n)              //���
{
	qnode *p;
	p=new qnode;
	p->f=f;
	p->n=n;
	p->next=NULL;
	q->rear->next=p;
	q->rear=p;
}
void xianshi(lqueue* q)                 //��ʾ����ʽ��������ʾ֮���Ѷ���ʽ����Ϊ�նӡ����Ҳ����ò���ָ�봫�ݶ���Ӱ�죬��Ϊlqueue����������ָ��!!�������������ó��Ӻ�����ֱ���±�һ����
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
	//cout<<f<<"x^"<<n;//�����ж���дһ���Ŀ�����õ�һ������š�
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
	q->front=q->rear;                 //�����������������ȳ�ʼ��Ϊ�գ��������Եڶ���ʹ�ü�������
	int f,n;
	cout<<"���������ʽ(ϵ�� ָ��)������0 0 ����\n";
		cout<<"����������ϵ��";
		cin>>f;
		cout<<"����������ָ��";
		cin>>n;
		cout<<endl;
	if(f==0&&n==0)
	{
		in_lqueue(q,f,n);
		cout<<"�����Ķ���ʽΪ��  0";
		cout<<endl;
		cout<<endl;
		return;
	}

	while(f!=0||n!=0)
	{
        in_lqueue(q,f,n);
		cout<<"����������ϵ��";
		cin>>f;
		cout<<"����������ָ��";
		cin>>n;
		cout<<endl;
	};
	cout<<"�����Ķ���ʽΪ��  ";
	xianshi(q);
	cout<<endl;
	cout<<endl;
}
int out_lqueue(lqueue*q,int &f,int &n)                 //����
{
	qnode *p;
	if(empty_lqueue(q))
	{
		return 0;
	}
	else 
	{
		p=q->front->next;                      //��ͷָ��Ķ���
		q->front->next=p->next;
		f=p->f;
		n=p->n;
		if(q->front->next==NULL)
			q->rear=q->front;
		return 1;
	}
}
/*
lqueue* jia(lqueue a,lqueue* b)        //�ӷ����㡣
{
	lqueue c;
	c=a;                               //���������a��a�ͳ������˰������������ʵ�ε��βδ��ݵ���ָ��a��c=a֮���Ӱ��a�����Բ���ָ�봫���ˡ�  �����ò���ָ�붼��Ӱ�죬��Ϊlqueue����������ָ�롤������
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
lqueue* jian(lqueue*a,lqueue*b)          //���ּ���������㷨��д��˷����Ȼ�뵽�ģ��տ�ʼд���㷨�������¶�����a1��b1Ȼ���a1��b1�����޸����㡣��һ���ƺ��͵�һ�ֵ�ʱ�临�Ӷ�һ����ֻ���ٶ�������������
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
		y=1;                            //�ǵ�yҪ��һ����
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
	cout<<"������xֵ��";
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
	cout<<"              *              ��ӭʹ�ö���ʽ������                *"<<endl;
	cout<<"              *                                                  *"<<endl;
	cout<<"              ****************************************************"<<endl;
	cout<<"              *                                                  *"<<endl;
	cout<<"              *   *****************        *****************     *"<<endl;
	cout<<"              *   * A.��������ʽa *        * B.��������ʽb *     *"<<endl;
	cout<<"              *   *****************        *****************     *"<<endl;
	cout<<"              *   *****************        *****************     *"<<endl;
	cout<<"              *   * C.  ����a+b   *        * D.  ����a-b   *     *"<<endl;
	cout<<"              *   *****************        *****************     *"<<endl;
	cout<<"              *   *****************        *****************     *"<<endl;
	cout<<"              *   * E.  ����a*b   *        * F.����x������ *     *"<<endl;
	cout<<"              *   *****************        *****************     *"<<endl;
	cout<<"              *               *****************                  *"<<endl;
	cout<<"              *               * G.  �Ƴ�ϵͳ  *                  *"<<endl;
	cout<<"              *               *****************                  *"<<endl;
	cout<<"              ****************************************************"<<endl;
	cout<<"                                   ������";
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
	default:cout<<"                              �����������������\n";
	}
	}
}