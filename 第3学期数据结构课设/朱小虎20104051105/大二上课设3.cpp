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
}paixu;               //������¼��������бȽϴ����ͽ���������
                     //��̹����м�¼�Ƚϴ�����ʱ������&&��p��m++������Ӱ��һ����������ֱ���ö��žͿ��ԣ������ж�������ж����һ������֮�����䣡Ҳ����˵��p.m++�ŵ��ж����֮ǰ�ö��Ÿ����ͺ�����
void ziranshu()          //�������ļ���д��n�������Ȼ��������
{

	int x[1000];
    srand( (unsigned)time( NULL ) );
/******************************************************************/
 //����1000��3λ��Ȼ�����
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
		cout<<"���ļ�����";
		exit(1);
	}
	for(i=0;i<1000;i++)
	{   
        outfile<<x[i]<<" ";
		if(x[i]==0)
			break;
	}
	cout<<"���������Ȼ�����\n";
}
void baocun(ST*t)          //���ļ��ﱣ������õ�ѧ����Ϣ
{
	ofstream outfile("ffffff.txt",ios::out);
	if(!outfile)
	{
		cout<<"���ļ�����";
		exit(1);
	}
	for(int i=1;i<=max;i++)
	{
		outfile<<t->data[i]<<" ";
		if(t->data[i]==0)
			break;
	}
	cout<<"\n�������\n";
}
ST* jianli()         //����˳������ļ�����룩
{
	ST *t;
	t=new ST;
	t->length=0;
	ifstream infile("fff.txt",ios::in);
	if(!infile)
	{
		cout<<"���ļ�����";
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
ST * huanyuan(ST*T)                  // ��ԭtΪԭ��������
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
paixu insert(ST*t)                     //ֱ�Ӳ������򷽷�
{
	paixu p;
	p.m=0,p.n=0;
	p.name="ֱ�Ӳ�������";
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
//	cout<<"Ԫ�رȽϴ���Ϊ"<<p.m<<"Ԫ���ƶ�����Ϊ"<<p.n<<endl;
	return p;
}
paixu select(ST*t)                //ѡ�����򷽷�
{
	paixu p;
	p.m=0,p.n=0;
	p.name="ѡ������";
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
//	cout<<"Ԫ�رȽϴ���Ϊ"<<p.m<<"Ԫ���ƶ�����Ϊ"<<p.n<<endl;
	return p;
}
paixu bubble(ST*t)             //ð�����򷽷�
{
	paixu p;
	p.m=0,p.n=0;
	p.name="ð������";
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
//	cout<<"Ԫ�رȽϴ���Ϊ"<<p.m<<"Ԫ���ƶ�����Ϊ"<<p.n<<endl;
	return p;
}
paixu shell(ST*t,int dk)             // ϣ�����򷽷�
{
	paixu p;
	p.m=0,p.n=0;
	p.name="ϣ������";
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
	p.name="ϣ������";
	int dk;
	for(dk=t->length;dk>=1;dk/=2)
	{
		q=shell(t,dk);
		p.m+=q.m;
		p.n+=q.n;
	}
//	cout<<"Ԫ�رȽϴ���Ϊ"<<p.m<<"Ԫ���ƶ�����Ϊ"<<p.n<<endl;
	return p;
}
paixu pt(ST*t,int i,int j,int &n)              //���������㷨,��n������֧���¼
{
	paixu p;
	p.m=0,p.n=0;
	p.name="��������";
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
	n=i;               //��¼֧����±�
	return p;
}
paixu P;                  //ȫ�ֱ���

paixu quick(ST*T,int s,int t)
{
	paixu q;
	int n;
	if(s<t)
	{
		q=pt(T,s,t,n);
		P.n+=q.n;
		P.m+=q.m;
		quick(T,s,n-1);                         //���ﲻ��Ҫ���ۼ��ˣ���Ϊû�εݹ���õ�ʱ�����һ������p���ã�
		quick(T,n+1,t);
	}
	return P;
}
paixu Quick(ST*t)
{
	paixu p;
//	p.m=0,p.n=0;
//	p.name="�������򷽷�";
	P.m=0;
    P.n=0;
    P.name="��������";
	p=quick(t,1,t->length);
//	cout<<"Ԫ�رȽϴ���Ϊ"<<p.m<<"Ԫ���ƶ�����Ϊ"<<p.n<<endl;
	return p;
}

paixu head(ST*T,int s,int t)                //������
{
	paixu p;
	p.m=0,p.n=0;
	p.name="������";
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
	p.name="������";
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
//	cout<<"Ԫ�رȽϴ���Ϊ"<<p.m<<"Ԫ���ƶ�����Ϊ"<<p.n<<endl;
	return p;
}
void merge(int T[],int T1[],int s,int m,int t)               //�鲢�����㷨
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
	//		cout<<len<<"  11111"<<endl;             //�������for������һ�ε�ʱ��len���696����Ϊ��ʱ��r1�Ŀռ����Ϊmax���ԾͰ����һ�����ݴ�����ʵ��len��λ���ϣ�����len��ֵ���ˡ�����
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
	P.name="�鲢����";
	int len=1;
	int r1[max+1];                         //���һ���ǵ���max+1��Ϊ��ST�е�data���ݾ��ǡ�max+1�������ȱ�ٿռ䣬�п��ܻ�������ı����Ŀռ�ռ���ˣ�������Ī������ĸı������ı������Ժ�ǵ�һ��Ҫ���빻�ռ䡣���ҵ������Ҫ������ٿռ䡣
	while(len<t->length)
	{
		mp(t->data,r1,len,t->length);
		len=2*len;
		mp(r1,t->data,len,t->length);
	}
	p.m=P.m;
	p.n=P.n;
	p.name=P.name;
//	cout<<"Ԫ�رȽϴ���Ϊ"<<p.m<<"Ԫ���ƶ�����Ϊ"<<p.n<<endl;
	return p;
}
void main()
{
	ziranshu();
	
	paixu a[8];     //������¼ÿ������ıȽϴ����ͽ�������������
	int i=1;
	ST *T,*t;
	T=jianli();
	cout<<"���������鳤��length��ֵ";
	cin>>T->length;
	cout<<"ԭ��Ϣ\n";
	shuchu(T);
	cout<<"\nֱ�Ӳ�������\n";
	t=huanyuan(T);
	a[i]=insert(t);i++;
	shuchu(t);
	cout<<"\nѡ������\n";
	t=huanyuan(T);
	a[i]=select(t);i++;
	shuchu(t);
	cout<<"\nð������\n";
	t=huanyuan(T);
	a[i]=bubble(t);i++;
	shuchu(t);
	cout<<"\nϣ������\n";
	t=huanyuan(T);
	a[i]=Shell(t);i++;
	shuchu(t);
	cout<<"\n��������\n";
	t=huanyuan(T);
	a[i]=Quick(t);i++;
	shuchu(t);
	cout<<"\n������\n";
	t=huanyuan(T);
	a[i]=heap(t);i++;
	shuchu(t);
	cout<<"\n�鲢����\n";
	t=huanyuan(T);
	a[i]=ms(t);i++;
	shuchu(t);
/*	for(i=1;i<=7;i++)
	{
		cout<<a[i].name;
		cout<<"��Ԫ�رȽϴ���Ϊ"<<a[i].m<<"Ԫ���ƶ�����Ϊ"<<a[i].n<<endl;
	}*/
    baocun(t);
	cout<<"\n���Ƚϴ�����������7�����򷽷�����������Ϊ"<<t->length<<"��ʱ��"<<endl;
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
	cout<<" **    ���򷽷�    **  �Ƚϴ���  **  �ƶ�����  **  �Ƚϴ������ƶ�����֮��  **\n";
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
	cout<<"\nֱ�Ӳ�������\n";
	cout<<" ************************************************************************\n";
	cout<<" **  �������  **  �Ƚϴ���  **  �ƶ�����  **  �Ƚϴ������ƶ�����֮��  **\n";
	cout<<" ************************************************************************\n";
	for(int j=0;j<5;j++)
	{
		T->length=b[j];
		t=huanyuan(T);
		p=insert(t);
	cout<<" **     "<<b[j]<<"    **     "<<p.m<<"    **    "<<p.n<<"     **         "<<p.n+p.m<<"          **\n";
	cout<<" ************************************************************************\n";
	}
	 


	cout<<"\nѡ������\n";
	cout<<" ************************************************************************\n";
	cout<<" **  �������  **  �Ƚϴ���  **  �ƶ�����  **  �Ƚϴ������ƶ�����֮��  **\n";
	cout<<" ************************************************************************\n";
	for(j=0;j<5;j++)
	{
		T->length=b[j];
		t=huanyuan(T);
		p=select(t);
	cout<<" **     "<<b[j]<<"    **     "<<p.m<<"    **    "<<p.n<<"     **         "<<p.n+p.m<<"          **\n";
	cout<<" ************************************************************************\n";
	}


	cout<<"\nð������\n";
	cout<<" ************************************************************************\n";
	cout<<" **  �������  **  �Ƚϴ���  **  �ƶ�����  **  �Ƚϴ������ƶ�����֮��  **\n";
	cout<<" ************************************************************************\n";
	for(j=0;j<5;j++)
	{
		T->length=b[j];
		t=huanyuan(T);
		p=bubble(t);
	cout<<" **     "<<b[j]<<"    **     "<<p.m<<"    **    "<<p.n<<"     **         "<<p.n+p.m<<"          **\n";
	cout<<" ************************************************************************\n";
	}


	cout<<"\nϣ������\n";
	cout<<" ***********************************************************************\n";
	cout<<" **  �����   **  �Ƚϴ���  **  �ƶ�����  **  �Ƚϴ������ƶ�����֮��  **\n";
	cout<<" ***********************************************************************\n";
	for(j=0;j<5;j++)
	{
		T->length=b[j];
		t=huanyuan(T);
		p=Shell(t);
	cout<<" **     "<<b[j]<<"    **     "<<p.m<<"    **    "<<p.n<<"     **         "<<p.n+p.m<<"          **\n";
	cout<<" ************************************************************************\n";
	}


	cout<<"\n��������\n";
	cout<<" ************************************************************************\n";
	cout<<" **  �������  **  �Ƚϴ���  **  �ƶ�����  **  �Ƚϴ������ƶ�����֮��  **\n";
	cout<<" ************************************************************************\n";
	for(j=0;j<5;j++)
	{
		T->length=b[j];
		t=huanyuan(T);
		p=Quick(t);
	cout<<" **     "<<b[j]<<"    **     "<<p.m<<"    **    "<<p.n<<"     **         "<<p.n+p.m<<"          **\n";
	cout<<" ************************************************************************\n";
	}


	cout<<"\n������\n";
	cout<<" ************************************************************************\n";
	cout<<" **  �������  **  �Ƚϴ���  **  �ƶ�����  **  �Ƚϴ������ƶ�����֮��  **\n";
	cout<<" ***********************************************************************\n";
	for(j=0;j<5;j++)
	{
		T->length=b[j];
		t=huanyuan(T);
		p=heap(t);
	cout<<" **     "<<b[j]<<"    **     "<<p.m<<"    **    "<<p.n<<"     **         "<<p.n+p.m<<"          **\n";
	cout<<" ************************************************************************\n";
	}


	cout<<"\n�鲢����\n";
	cout<<" ************************************************************************\n";
	cout<<" **  �������  **  �Ƚϴ���  **  �ƶ�����  **  �Ƚϴ������ƶ�����֮��  **\n";
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
