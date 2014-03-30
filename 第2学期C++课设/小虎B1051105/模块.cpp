#include<iostream>
#include<fstream>
using namespace std;
#include<string>
class staff;
void error();
class Date
{
public:
	int year;
	int month;
	int day;

	friend void set(Date&);
	friend void display(Date&);
};
void set(Date&d)
{
	int a[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	cout<<"�밴�ꡢ�¡������룺";
	cin>>d.year>>d.month>>d.day;
	if((d.year%4==0&&d.year%100!=0)||(d.year%400==0))
		a[1]=29;
	while(1)
	{
	   if(d.year<=0||d.month<=0||d.day<=0||d.month>12||d.day>a[d.month-1])
	   {
		   error();
   		  cout<<"����������������룺";
	   	  cin>>d.year>>d.month>>d.day;
		  system("color bd");
	   } 
	   else break;
	}
}

void display(Date&d)
{
	cout<<d.year<<"��"<<d.month<<"��"<<d.day<<"��"<<endl;
}
class staff
{public:
    int l;
	string num;
	string name;
	string sex;
	int age;
	string department;
	Date date;
	string job;
	string relation;
	int bonus;
	int deductwage;
	int basicwage;
	int saleroom;
	string grade;
	int subsidy;
	int hours;

	staff *next;


    virtual void SET(){}
    virtual void DISPLAY(){}
	void Set();
	void Display();
	virtual void WAGE(){}
	double wages();
	friend istream & operator>>(istream&,staff&);
	friend ostream & operator<<(ostream&,staff&);
};

istream & operator>>(istream &in,staff &c)
{
	c.Set();
	return in;
}
ostream & operator<<(ostream &out,staff &c)
{
	c.Display();
	return out;
}
void staff::Set()
{
	cout<<"������Ա����Ϣ\n";
	cout<<"��ţ�";
	cin>>num;
	cout<<"������";
	cin>>name;
	cout<<"�Ա�(man����woman)��";
	cin>>sex;
	while(1)
	{
	    if((sex>"mam"&&sex<"mao")||(sex>"womam"&&sex<"womao")){break;}
    	else
		{
			error();
	    	cout<<"����������������룺";
	    	cin>>sex;
			system("color bd");
		}
	}
	cout<<"���䣺";
	cin>>age;
	while(1)
	{
		if(age>0)break;
		else
		{
			error();
		    cout<<"����������������룺";
	    	cin>>age;
		}
	}
	cout<<"����:";
	cin>>department;
	cout<<"�μӹ���ʱ�䣺";
	set(date);
	cout<<"ְ��";
	cin>>job;
	cout<<"��ϵ��ʽ��";
	cin>>relation;
	cout<<"����";
	cin>>bonus;
	while(1)
	{
    	if(bonus<0)
		{
			error();
		    cout<<"����������������룺";
		    cin>>bonus;
		}
		else break;
	}
	cout<<"�۷����ʣ�";
	cin>>deductwage;
	while(1)
	{
    	if(deductwage<0)
		{
			error();
		    cout<<"����������������룺";
		    cin>>deductwage;
		}
		else break;
	}
	cout<<"��������";
	cin>>basicwage;
	while(1)
	{
    	if(basicwage<0)
		{
			error();
		    cout<<"����������������룺";
		    cin>>basicwage;
		}
		else break;
	}
}

void staff::Display()
{
	cout<<"\n\nԱ���Ļ�����Ϣ���£�";
	cout<<"\n��ţ�"<<num;
	cout<<"\n������"<<name;
	cout<<"\n�Ա�"<<sex;
	cout<<"\n���䣺"<<age;
	cout<<"\n����:"<<department;
	cout<<"\n�μӹ���ʱ�䣺";
	display(date);
	cout<<"ְ��"<<job;
	cout<<"\n��ϵ��ʽ��"<<relation;
	cout<<"\n����"<<bonus;
	cout<<"\n�۷����ʣ�"<<deductwage;
	cout<<"\n��������"<<basicwage<<endl;
}
double staff::wages()
{
	return basicwage+bonus-deductwage;
}
/////////////////////////////////////////���������ࡷ��///////////////////////////////////////////////////
class manager:virtual public staff
{	
public:
	friend istream & operator<<(istream & in,manager &m);
    friend ostream & operator>>(ostream & out,manager &m);
	void SET();
	void DISPLAY();
	void WAGE(){cout<<"ʵ������Ϊ��"<<Wage()<<endl;}
	double Wage(){return wages()+subsidy;}
};
istream & operator>>(istream & in,manager &m)
{
	m.Set();
	cout<<"�����뼶��";
	in>>m.grade;
	cout<<"������ְ�������";
	in>>m.subsidy;
	return in;
}
ostream & operator<<(ostream & out,manager &m)
{
	m.Display();
	out<<"����"<<m.grade<<endl;
	out<<"ְ�������"<<m.subsidy<<endl;
	return out;
}
void manager::SET(){l=3;cin>>*this;}              //Ҫ���ڱ����е��ñ����ĳ����������������������õĺ�����ȫд����ڵ�������������԰������������������ⶨ�壬����д����������صĺ��档
void manager::DISPLAY(){cout<<*this;}
///////////////////////////////////////����������Ա�ࡷ��////////////////////////////////////////////
class salesman:virtual public staff
{
protected:
	double ticheng;
public:                     //����Ժ��õ���������ؿ��Ծ����������֮�õ���set��������display������
	void SET();
	void DISPLAY();
	void WAGE(){cout<<"ʵ������Ϊ��"<<wages()+wage()<<endl;}
	double wage();
};
void salesman::SET()
{
	l=1;
	Set();
	cout<<"���������۶"<<endl;
	cin>>saleroom;
}
double salesman::wage()
{
	if(saleroom>=50000)
		ticheng=0.1;
	else if(saleroom>=20000)
		ticheng=0.07;
	else if(saleroom>=5000)
		ticheng=0.05;
	else ticheng=0.03;
    return saleroom*ticheng;
}
void salesman::DISPLAY()
{
	Display();
	cout<<"���۶�Ϊ��"<<saleroom<<endl;
	cout<<"ʵ������Ϊ��"<<wages()+wage()<<endl;
}
////////////////////////////////////////����������Ա�ࡷ��///////////////////////////////////////////
class technician:virtual public staff
{
protected:
	int money;
public:
	void SET();
	void DISPLAY();
    void WAGE(){cout<<"ʵ������Ϊ��"<<wages()+wage()<<endl;}
	double wage();
};
void technician::SET()
{
	l=2;
	Set();
	cout<<"�����빤��ʱ��(ʱ/��):"<<endl;
	cin>>hours;
}
double technician::wage()
{
	if(hours>=200)
		money=10;
	else if(hours>=150)
		money=7;
	else if(hours>=100)
		money=5;
	else money=3;
    return hours*money;
}
void technician::DISPLAY()
{
	Display();
	cout<<"����ʱ��Ϊ��"<<hours<<"ʱ/��"<<endl;
	cout<<"ʵ������Ϊ��"<<wages()+wage()<<endl;
}
/////////////////////////////////////////�������۾����ࡷ��////////////////////////////////////////
class salesmanager:public manager,public salesman
{
public:
	void SET();
	void DISPLAY();
	void WAGE(){cout<<"ʵ������Ϊ��"<<Wage()+wage()<<endl;}
};
void salesmanager::SET()
{
	l=4;
	cin>>*this;
	cout<<"���������۶"<<endl;
	cin>>saleroom;
}
void salesmanager::DISPLAY()
{
	cout<<*this;
	cout<<"���۶�Ϊ��"<<saleroom<<endl;
	cout<<"ʵ������Ϊ��"<<Wage()+wage()<<endl;
}
//////////////////////////////////////////���������ܼ��ࡷ��////////////////////////////////////////
class techmanager:public manager,public technician
{
public:
	void SET();
	void DISPLAY();
	void WAGE(){cout<<"ʵ������Ϊ��"<<Wage()+wage()<<endl;}
};
void techmanager::SET()
{
	l=5;
	cin>>*this;
	cout<<"�����빤��ʱ��(ʱ/��):"<<endl;
	cin>>hours;
}
void techmanager::DISPLAY()
{
	cout<<*this;
	cout<<"����ʱ��Ϊ��"<<hours<<"ʱ/��"<<endl;
	cout<<"ʵ������Ϊ��"<<Wage()+wage()<<endl;
}
////////////////////////////////////////////���������ࡷ��//////////////////////////////////////////////////////////////////
class control
{
protected:
	int a;
	staff*head;
	staff*p,*p1;
	staff*r;
public:	
	control(int x=0):a(x){p=head=new staff;head->next=0;};
	void choose(int*);
};
void control::choose(int *nnn)
{
	a=*nnn;
//	p=head=new staff;///����������������ÿ�ζ������µġ�������������ܷ�������Է��ڹ��캯��������ʺٺ١�
	switch(a)
	{
	case 4:
		{
			p=head;
			while(p->next!=0)////////////������pָ��ָ�������ĩβ��
			{
				p=p->next;
			}
			int n;
			system("cls");
			system("color bd");
                  cout<<"               **************************************************\n";
                  cout<<"               *                                                *\n";
                  cout<<"               *            ��ѡ��Ҫ���Ա����ְ��              *\n";
                  cout<<"               *        1.������Ա          2.������Ա          *\n";
                  cout<<"               *                    3.����                      *\n";
                  cout<<"               *        4.���۾���          5.�����ܼ�          *\n";
                  cout<<"               *                                                *\n";
                  cout<<"               *                 ��������Ӧ��ţ�               *\n";
                  cout<<"               *                                                *\n";
                  cout<<"               **************************************************\n";
		          cout<<"                                   �������ţ�";
	              cin>>n;
		          cout<<"\n\n\n\n";
				  switch(n)
				  {
                   case 1:///////////////////////////////�����̱��˵�ʱ����µ���У��µĺ��뷨�������Ϳ��Բ���goto����ˡ�
					   {
						  p=head;
                     	  r=new salesman;  
	             		  r->SET();
						  while(p->next!=0)/////Ҫ����������������ָ�����һ����Ա��ָ�������ӣ�������ָ�����һ����Ա��next��ָ�����ӡ�
						  {
							  p=p->next;
							  if(r->num==p->num)
							  {
								  error();
								  cout<<"Ա������ظ�������������\n";
								  r->SET();
								  p=head;
							  }
						  }
						  p->next=r;
	            		  r->next=0;
						  break;
					   }
						  
     	           case 2:
					   {
to2:		   			  r=new technician;	            		  
	             		  r->SET();
						  p1=head;
						  while(1)
						  {
							  p1=p1->next;
							  if(p1==0)break;
							  if(r->num==p1->num)
							  {
								  error();
								  cout<<"Ա������ظ�������������\n";
								  goto to2;
								  break;
							  }
						  }
						  p->next=r;
	            		  r->next=0;
            			  p=r;
						   break;
					   }
                   case 3:
					   {
to3:		   			  r=new manager;	            		  
	             		  r->SET();
						  p1=head;
						  while(1)
						  {
							  p1=p1->next;
							  if(p1==0)break;
							  if(r->num==p1->num)
							  {
								  error();
								  cout<<"Ա������ظ�������������\n";
								  goto to3;
								  break;
							  }
						  }
						  p->next=r;
	            		  r->next=0;
            			  p=r;
						   break;
					   }
                   case 4:
					   {
to4:			   		  r=new salesmanager;	            		  
	             		  r->SET();
						  p1=head;
						  while(1)
						  {
							  p1=p1->next;
							  if(p1==0)break;
							  if(r->num==p1->num)
							  {
								  error();
								  cout<<"Ա������ظ�������������\n";
								  goto to4;
								  break;
							  }
						  }
						  p->next=r;
	            		  r->next=0;
            			  p=r;
						   break;
					   }
                   case 5:
					   {
to5:		   			  r=new techmanager;				
	             		  r->SET();
						  p1=head;
						  while(1)
						  {
							  p1=p1->next;
							  if(p1==0)break;
							  if(r->num==p1->num)
							  {
								  error();
								  cout<<"Ա������ظ�������������\n";
								  goto to5;
								  break;
							  }
						  }
						  p->next=r;
	            		  r->next=0;
            			  p=r;
						   break;
					   }
				  }
			        cout<<"               **************************************************\n";
					cout<<"               *                                                *\n";
					cout<<"               *         1.�������ְ����Ϣ                     *\n";
					cout<<"               *         2.������һĿ¼                         *\n";
					cout<<"               *         3.�˳���Ϣ����ϵͳ                     *\n";
					cout<<"               *                                                *\n";
					cout<<"               *                 ��������Ӧ��ţ�               *\n";
					cout<<"               *                                                *\n";
					cout<<"               **************************************************\n";
					cout<<"                                    �������ţ�";
					int x;
					cin>>x;
					switch(x)
					{
					case 1:*nnn=4;break;
					case 2:*nnn=0;break;
					case 3:*nnn=9;break;
					default:*nnn=0;
					}
		break;
		}
	case 2:
		{
			int m;
			string n;
			p=head;
			if(head->next==0)
			{
				cout<<"��δ����Ա�����ݡ�������ӡ�\n";
				*nnn=0;
				break;
			}
			        cout<<"               **************************************************\n";
					cout<<"               *                                                *\n";
					cout<<"               *         1.����Ų�ѯ          2.��������ѯ     *\n";
					cout<<"               *         3.�����Ų�ѯ          4.��ְ���ѯ     *\n";
					cout<<"               *                                                *\n";
					cout<<"               *                 ��������Ӧ��ţ�               *\n";
					cout<<"               *                                                *\n";
					cout<<"               **************************************************\n";
					cout<<"                                   �������ţ�";
			cin>>m;
			cout<<"\n\n\n\n";
			switch(m)
			{
			case(1):
				{
				cout<<"\n�������ѯ�ı�ţ�";
		    	cin>>n;
			    while(1)
				{
	    			p=p->next;
	     			if(p->num==n)
					{
			    		p->DISPLAY();
			    		break;          //�����breakֻ�ܴ��while��䣬û�д��case��䡣���Ժ���ü���break��
					}
		    		if(p->next==0)//����ֹ��ѭ����ȥ���ͻ�ֹͣ�������ǵ�ֻ����дp->next������p��
					{
						error();
						string x;
		    			cout<<"�������ݴ�����������?(y/n)";
						cin>>x;
						if(x=="y")
						{
						cout<<"\n�������ѯ�ı�ţ�";
		    			cin>>n;
		    			p=head;
						}
						else break;
					}
				}
				break;
				}
			case(2):
				{
					int k=0;
				cout<<"\n�������ѯ��������";
		    	cin>>n;
			    while(1)
				{
	    			p=p->next;
	     			if(p->name==n)
					{
			    		p->DISPLAY();
			    	//	break;          //�����breakֻ�ܴ��while��䣬û�д��case��䡣���Ժ���ü���break��
						//ȡ��break��ԭ��������������ģ���ֻ����ʾ�����ǰ����ˣ�ֻ��ȡ����break���ܶ���ʾ������
						k=1;
					}
                    if(p->next==0&&k)
						break;
		    		if(p->next==0&&!k)//����ֹ��ѭ����ȥ���ͻ�ֹͣ�������ǵ�ֻ����дp->next������p��
					{
						error();
						string x;
		    			cout<<"�������ݴ�����������?(y/n)";
						cin>>x;
						if(x=="y")
						{
							cout<<"\n�������ѯ��������";
		    			cin>>n;
		    			p=head;
						}
						else break;
					}
				}
				break;
				}
			case(3):
				{
				cout<<"\n�������ѯ�Ĳ��ţ�";
		    	cin>>n;
			    while(1)
				{
	    			p=p->next;
	     			if(p->department==n)
					{
			    		p->DISPLAY();
			    		break;          //�����breakֻ�ܴ��while��䣬û�д��case��䡣���Ժ���ü���break��
					}
		    		if(p->next==0)//����ֹ��ѭ����ȥ���ͻ�ֹͣ�������ǵ�ֻ����дp->next������p��
					{
						error();
						string x;
		    			cout<<"�������ݴ�����������?(y/n)";
						cin>>x;
						if(x=="y")
						{
							cout<<"\n�������ѯ�Ĳ��ţ�";
		    			cin>>n;
		    			p=head;
						}
						else break;					}
				}
				break;
				}
			case(4):
				{
				cout<<"\n�������ѯ��ְ��";
		    	cin>>n;
			    while(1)
				{
	    			p=p->next;
	     			if(p->job==n)
					{
			    		p->DISPLAY();
			    		break;          //�����breakֻ�ܴ��while��䣬û�д��case��䡣���Ժ���ü���break��
					}
		    		if(p->next==0)//����ֹ��ѭ����ȥ���ͻ�ֹͣ�������ǵ�ֻ����дp->next������p��
					{
						error();
						string x;
		    			cout<<"�������ݴ�����������?(y/n)";
						cin>>x;
						if(x=="y")
						{
							cout<<"\n�������ѯ��ְ��";
		    			cin>>n;
		    			p=head;
						}
						else break;
					}
				}
				break;
				}
			}
			        cout<<"               **************************************************\n";
					cout<<"               *                                                *\n";
					cout<<"               *         1.������ѯְ����Ϣ                     *\n";
					cout<<"               *         2.������һĿ¼                         *\n";
					cout<<"               *         3.�˳���Ϣ����ϵͳ                     *\n";
					cout<<"               *                                                *\n";
					cout<<"               *                 ��������Ӧ��ţ�               *\n";
					cout<<"               *                                                *\n";
					cout<<"               **************************************************\n";
					cout<<"                                   �������ţ�";
					int x;
					cin>>x;
					switch(x)
					{
					case 1:*nnn=2;break;
					case 2:*nnn=0;break;
					case 3:*nnn=9;break;
					default:*nnn=0;
					}
		break;
		}
	case 3:
		{
			int d;
			p=head;
			if(head->next==0)
			{
				cout<<"��δ����Ա�����ݡ�������ӡ�\n";
				*nnn=0;
				break;
			}
            string n;


			        cout<<"               **************************************************\n";
					cout<<"               *                                                *\n";
					cout<<"               *         1.�����ɾ��          2.������ɾ��     *\n";
					cout<<"               *         3.������ɾ��          4.��ְ��ɾ��     *\n";
					cout<<"               *                                                *\n";
					cout<<"               *                 ��������Ӧ��ţ�               *\n";
					cout<<"               *                                                *\n";
					cout<<"               **************************************************\n";
					cout<<"                                   �������ţ�";
			cin>>d;
			cout<<"\n\n\n\n";
           switch(d)
			{
			case 1:
				{
        			cout<<"\n��������Ҫɾ����Ա�ı�ţ�";
            		cin>>n;
        			while(1)
					{
        				r=p;
        				p=p->next;
        				if(p->num==n)
						{
							p->DISPLAY();
		    	    		char m;
							cout<<"               **************************************************\n";
							cout<<"               *                  �Ƿ�ȷ��ɾ����                *\n";					
							cout<<"               *                                                *\n";
							cout<<"               *           Y.ȷ��ɾ��       N.ȡ��ɾ��          *\n";
							cout<<"               *                                                *\n";
							cout<<"               *                                                *\n";
							cout<<"               *                 ��������Ӧ��ĸ��               *\n";
							cout<<"               *                                                *\n";
							cout<<"               **************************************************\n";
							cout<<"                                   ��������ĸ��";
							cin>>m;
							cout<<"\n\n\n\n";
							if(m=='y')
							{
							    r->next=p->next;
				//		    	delete p;           //////////////////////����Ϊʲô���������أ�Ϊʲô����ֹ��?
							    cout<<"ɾ���ɹ�!\n";
							    break;
							}
							else if(m=='n')  {cout<<"��ȡ��ɾ��\n";break;}
							else cout<<"���������ȡ��ɾ��\n";
						}
						if(p->next==0)//����ֹ��ѭ����ȥ���ͻ�ֹͣ�������ǵ�ֻ����дp->next������p��
						{
						error();
						string x;
		    			cout<<"�������ݴ�����������?(y/n)";
						cin>>x;
						if(x=="y")
						{
						cout<<"\n��������Ҫɾ����Ա�ı�ţ�";
		    			cin>>n;
		    			p=head;
						}
						else break;						}

					}		
					break;
				}
			case 2:
				{
					int k=0;
        			cout<<"\n��������Ҫɾ����Ա��������";
            		cin>>n;
        			while(1)
					{
        				r=p;
        				p=p->next;
        				if(p->name==n)
						{
							k=1;
							p->DISPLAY();
		    	    		char m;
							cout<<"               **************************************************\n";
							cout<<"               *                  �Ƿ�ȷ��ɾ����                *\n";					
							cout<<"               *                                                *\n";
							cout<<"               *           Y.ȷ��ɾ��       N.ȡ��ɾ��          *\n";
							cout<<"               *                                                *\n";
							cout<<"               *                                                *\n";
							cout<<"               *                 ��������Ӧ��ĸ��               *\n";
							cout<<"               *                                                *\n";
							cout<<"               **************************************************\n";
							cout<<"                                   ��������ĸ��";
							cin>>m;
							cout<<"\n\n\n\n";
							if(m=='y')
							{
							    r->next=p->next;
				//		    	delete p;           //////////////////////����Ϊʲô���������أ�Ϊʲô����ֹ��?
							    cout<<"ɾ���ɹ�!\n";
				//			    break;//ȡ����Ŀ��ͬ����Ϊ�˲�ȫ���е���������ֹ�����������ʱ©����Ա��
							}
							else if(m=='n')  {cout<<"��ȡ��ɾ��\n";}
							else cout<<"���������ȡ��ɾ��\n";
						}
						if(p->next==0&&k)
							break;
						if(p->next==0&&!k)//����ֹ��ѭ����ȥ���ͻ�ֹͣ�������ǵ�ֻ����дp->next������p��
						{
						error();
						string x;
		    			cout<<"�������ݴ�����������?(y/n)";
						cin>>x;
						if(x=="y")
						{
						cout<<"\n��������Ҫɾ����Ա��������";
		    			cin>>n;
		    			p=head;
						}
						else break;						}
					}		
					break;
				}
			case 3:
				{
					int k=1;
        			cout<<"\n��������Ҫɾ���Ĳ��ţ�";
            		cin>>n;
        			while(1)
					{
        				r=p;
        				p=p->next;
        				if(p->department==n)
						{
							if(k)
							{
								p->DISPLAY();
								char m;
								cout<<"               **************************************************\n";
								cout<<"               *                  �Ƿ�ȷ��ɾ����                *\n";					
								cout<<"               *                                                *\n";
								cout<<"               *           Y.ȷ��ɾ��       N.ȡ��ɾ��          *\n";
								cout<<"               *                                                *\n";
								cout<<"               *                                                *\n";
								cout<<"               *                 ��������Ӧ��ĸ��               *\n";
								cout<<"               *                                                *\n";
								cout<<"               **************************************************\n";
								cout<<"                                   ��������ĸ��";
								cin>>m;
								cout<<"\n\n\n\n";
								if(m=='y')
								{
								     k=0;
								}
								else if(m=='n')  {cout<<"��ȡ��ɾ��\n";break;}
								else {cout<<"�������,��ȡ��ɾ��\n";break;}
							}
							r->next=p->next;
							cout<<"ɾ��һ����\n";
					//		p=p->next;        /////////������䣬���ܼ���ɾ��ͬ���ŵ����ˡ���������������ѭ����ȥ��ͷ�и�r=p.�ͻ��ְ�p���ӻ����ˡ���Ҳ�����������delete pΪʲô�������ˡ���Ϊɾ����r=p���޷������ˡ�������ٷ�delete���������delete�ˡ����ǲ��а���
					 //       delete p;////////////////����Ϊʲô���������أ�Ϊʲô����ֹ��?�򣬵�һ�����ã�֮��Ͳ��������أ�
							p=r;       //////////�ǵ�����Ӧ��Ϊp=r��Ϊ��ѭ����ȥ��ʱ����Ҫr=p�ġ��Ժ�һ�������ͼ���������

						}

////��������k�Ǹ����뷨���жϸ�ִ��˭��ʲô����¸�ִ��˭��
						if((p->next==0)&&(1-k))///////////���if��䲻�ܷ�����һ�����氡��
						{
							cout<<"ɾ���ɹ�!\n";
							break;
						}
						if((p->next==0)&&k)//����ֹ��ѭ����ȥ���ͻ�ֹͣ�������ǵ�ֻ����дp->next������p��
						{
						error();
						string x;
		    			cout<<"�������ݴ�����������?(y/n)";
						cin>>x;
						if(x=="y")
						{
						cout<<"\n��������Ҫɾ���Ĳ��ţ�";
		    			cin>>n;
		    			p=head;
						}
						else break;
						}
					}		
				break;
				}
			case 4:
				{
					int k=1;
        			cout<<"\n��������Ҫɾ����ְ��";
            		cin>>n;
        			while(1)
					{
        				r=p;
        				p=p->next;
        				if(p->job==n)
						{
							if(k)
							{
								p->DISPLAY();
								char m;
								cout<<"               **************************************************\n";
								cout<<"               *                  �Ƿ�ȷ��ɾ����                *\n";					
								cout<<"               *                                                *\n";
								cout<<"               *           Y.ȷ��ɾ��       N.ȡ��ɾ��          *\n";
								cout<<"               *                                                *\n";
								cout<<"               *                                                *\n";
								cout<<"               *                 ��������Ӧ��ĸ��               *\n";
								cout<<"               *                                                *\n";
								cout<<"               **************************************************\n";
								cout<<"                                   ��������ĸ��";
								cin>>m;
								cout<<"\n\n\n\n";
								if(m=='y')
								{
								     k=0;
								}
								else if(m=='n')  {cout<<"��ȡ��ɾ��\n";break;}
								else {cout<<"�������,��ȡ��ɾ��\n";break;}
							}
							r->next=p->next;
							cout<<"ɾ��һ����\n";
							p=r;       /////////////////�ǵ�����Ӧ��Ϊp=r��Ϊ��ѭ����ȥ��ʱ����Ҫr=p�ġ��Ժ�һ�������ͼ���������

						}

////��������k�Ǹ����뷨���жϸ�ִ��˭��ʲô����¸�ִ��˭��
						if((p->next==0)&&(1-k))////////////////////////���if��䲻�ܷ�����һ�����氡��
						{
							cout<<"ɾ���ɹ�!\n";
							break;
						}
						if((p->next==0)&&k)//����ֹ��ѭ����ȥ���ͻ�ֹͣ�������ǵ�ֻ����дp->next������p��
						{
						error();
						string x;
		    			cout<<"�������ݴ�����������?(y/n)";
						cin>>x;
						if(x=="y")
						{
						cout<<"\n��������Ҫɾ����ְ��";
		    			cin>>n;
		    			p=head;
						}
						else break;
						}
					}		
				break;
				}
			default:cout<<"�����Ŵ��󣡣���";
		   }    
			        cout<<"               **************************************************\n";
					cout<<"               *                                                *\n";
					cout<<"               *         1.����ɾ��ְ����Ϣ                     *\n";
					cout<<"               *         2.������һĿ¼                         *\n";
					cout<<"               *         3.�˳���Ϣ����ϵͳ                     *\n";
					cout<<"               *                                                *\n";
					cout<<"               *                 ��������Ӧ��ţ�               *\n";
					cout<<"               *                                                *\n";
					cout<<"               **************************************************\n";
					cout<<"                                   �������ţ�";
					int x;
					cin>>x;
					switch(x)
					{
					case 1:*nnn=3;break;
					case 2:*nnn=0;break;
					case 3:*nnn=9;break;
					default:*nnn=0;
					}
		break;
		}
	case 1:
		{
			p=head;
			if(head->next==0)
			{
				cout<<"��δ����Ա�����ݡ�������ӡ�\n";
				*nnn=0;
				break;
			}
			string n;
			int k=1;
			cout<<"\n��������Ҫ�޸���Ա�ı�ţ�";
			cin>>n;
			while(1)
			{
				p=p->next;
				if(p->num==n)
				{
					int m;
					cout<<"               **************************************************\n";
					cout<<"               *                                                *\n";
					cout<<"               *         1.�޸�����          2.�޸Ĳ���         *\n";
					cout<<"               *         3.�޸�ְ��          4.�޸���ϵ�绰     *\n";
					cout<<"               *         5.�޸Ľ���          6.�޸Ŀ۷�����     *\n";
					cout<<"               *         7.�޸Ļ�������      8.�����ϼ��˵�     *\n";
					cout<<"               *                                                *\n";
					cout<<"               *                 ��������Ӧ��ţ�               *\n";
					cout<<"               *                                                *\n";
					cout<<"               **************************************************\n";
					cout<<"                                   �������ţ�";
					cin>>m;
					cout<<"\n\n\n\n";
					switch(m)
					{
					case 1:
						{
							cout<<"�������޸ĺ�������";
							cin>>p->name;
							break;
						}
					case 2:
						{
							cout<<"�������޸ĺ��ţ�";
							cin>>p->department;
							break;
						}
					case 3:
						{
							cout<<"�������޸ĺ�ְ��";
							cin>>p->job;
							break;
						}
					case 4:
						{
							cout<<"�������޸ĺ���ϵ�绰��";
							cin>>p->relation;
							break;
						}
					case 5:
						{
							cout<<"�������޸ĺ󽱽�";
							cin>>p->bonus;
							break;
						}
					case 6:
						{
							cout<<"�������޸ĺ�۷����ʣ�";
							cin>>p->deductwage;
							break;
						}
					case 7:
						{
							cout<<"�������޸ĺ�������ʣ�";
							cin>>p->basicwage;
							break;
						}
					case 8:
						{
							*nnn=0;
							k=0;
							break;
						}
					}

					break;
				}
				if(p->next==0)//����ֹ��ѭ����ȥ���ͻ�ֹͣ�������ǵ�ֻ����дp->next������p��
				{
						error();
						string x;
		    			cout<<"�������ݴ�����������?(y/n)";
						cin>>x;
						if(x=="y")
						{
						cout<<"\n��������Ҫ�޸���Ա�ı�ţ�";
		    			cin>>n;
		    			p=head;
						}
						else break;
				}
			}
			if(k)
			{
			        cout<<"�޸ĳɹ���\n";
			        cout<<"               **************************************************\n";
					cout<<"               *                                                *\n";
					cout<<"               *         1.�����޸�ְ����Ϣ                     *\n";
					cout<<"               *         2.������һĿ¼                         *\n";
					cout<<"               *         3.�˳���Ϣ����ϵͳ                     *\n";
					cout<<"               *                                                *\n";
					cout<<"               *                 ��������Ӧ��ţ�               *\n";
					cout<<"               *                                                *\n";
					cout<<"               **************************************************\n";
					cout<<"                                   �������ţ�";
					int x;
					cin>>x;
					switch(x)
					{
					case 1:*nnn=1;break;
					case 2:*nnn=0;break;
					case 3:*nnn=9;break;
					default:*nnn=0;
					}
			}
			break;
		}
	case 5:
		{
			p=head;
			if(head->next==0)
			{
				cout<<"��δ����Ա�����ݡ�������ӡ�\n";
				*nnn=0;
				break;
			}
			while(1)
			{
				p=p->next;
				p->DISPLAY();
				if(p->next==0)
					break;
			}
			        cout<<"               **************************************************\n";
					cout<<"               *                                                *\n";
					cout<<"               *         1.������һĿ¼                         *\n";
					cout<<"               *         2.�˳���Ϣ����ϵͳ                     *\n";
					cout<<"               *                                                *\n";
					cout<<"               *                 ��������Ӧ��ţ�               *\n";
					cout<<"               *                                                *\n";
					cout<<"               **************************************************\n";
					cout<<"                                   �������ţ�";
					int x;
					cin>>x;
					switch(x)
					{
					case 1:*nnn=0;break;
					case 2:*nnn=9;break;
					default:cout<<"������������Զ�������һĿ¼��\n";*nnn=0;
					}
			break;
		}
	case 6:
		{
			p=head;
			if(head->next==0)
			{
				cout<<"��δ����Ա�����ݡ�������ӡ�\n";
				*nnn=0;
				break;
			}
			string n;
			int k=1;
			cout<<"\n��������Ҫ���㹤����Ա�ı�ţ�";
			cin>>n;
			while(1)
			{
				p=p->next;
				if(p->num==n)
				{
					p->WAGE();
					break;
				}
				if(p->next==0)//����ֹ��ѭ����ȥ���ͻ�ֹͣ�������ǵ�ֻ����дp->next������p��
				{
						error();
						string x;
		    			cout<<"�������ݴ�����������?(y/n)";
						cin>>x;
						if(x=="y")
						{
						cout<<"\n��������Ҫ���㹤����Ա�ı�ţ�";
		    			cin>>n;
		    			p=head;
						}
						else break;
				}
			}
			if(k)
			{
			        cout<<"               **************************************************\n";
					cout<<"               *                                                *\n";
					cout<<"               *         1.��������ְ������                     *\n";
					cout<<"               *         2.������һĿ¼                         *\n";
					cout<<"               *         3.�˳���Ϣ����ϵͳ                     *\n";
					cout<<"               *                                                *\n";
					cout<<"               *                 ��������Ӧ��ţ�               *\n";
					cout<<"               *                                                *\n";
					cout<<"               **************************************************\n";
					cout<<"                                   �������ţ�";
					int x;
					cin>>x;
					switch(x)
					{
					case 1:*nnn=6;break;
					case 2:*nnn=0;break;
					case 3:*nnn=9;break;
					default:*nnn=0;
					}
			}
			break;

		}
	case 7:
		{
			int l;
			ifstream infile("fffffff.txt",ios::in);
            if(!infile)
			{
				cout<<"���ļ�����";
				exit(1);
			}
			r=head;
			while(1)
			{
	    		infile>>l;
				if(l==0)break;
		        //�ո�ͻس�����������Ȼ�������һ����Ϣ��
		    	switch(l)
		    	{
	            case 0:break;
		    	case 1:
					{
						p=new salesman;
						infile>>p->num>>p->name>>p->sex>>p->age>>p->department>>p->date.year>>p->date.month>>p->date.day>>p->job>>p->relation>>p->bonus>>p->deductwage>>p->basicwage>>p->saleroom;break;
					break;
					}
		    	case 2:
					{
						p=new technician;
						infile>>p->num>>p->name>>p->sex>>p->age>>p->department>>p->date.year>>p->date.month>>p->date.day>>p->job>>p->relation>>p->bonus>>p->deductwage>>p->basicwage>>p->hours;break;
					break;
					}
		    	case 3:
					{
						p=new manager;
						infile>>p->num>>p->name>>p->sex>>p->age>>p->department>>p->date.year>>p->date.month>>p->date.day>>p->job>>p->relation>>p->bonus>>p->deductwage>>p->basicwage>>p->grade>>p->subsidy;break;
					break;
					}
		    	case 4:
					{
						p=new salesmanager;
						infile>>p->num>>p->name>>p->sex>>p->age>>p->department>>p->date.year>>p->date.month>>p->date.day>>p->job>>p->relation>>p->bonus>>p->deductwage>>p->basicwage>>p->grade>>p->subsidy>>p->saleroom;break;
					break;
					}
				case 5:
					{
						p=new techmanager;
						infile>>p->num>>p->name>>p->sex>>p->age>>p->department>>p->date.year>>p->date.month>>p->date.day>>p->job>>p->relation>>p->bonus>>p->deductwage>>p->basicwage>>p->grade>>p->subsidy>>p->hours;break;
					break;
					}
		    	}
				p->l=l;
				p->next=0;
				r->next=p;
				r=p;
				
			}
			cout<<"�ļ������У�\n";
			for(int i=0;i<30;i++)
			{
				
				cout<<"��";
				_sleep(100);
			}
			system("cls");
			system("color fd");
			cout<<"                                  �q����r"<<endl;
			cout<<"                                  {/ .  . /}"<<endl;
			cout<<"                                   ( (oo) )  "<<endl;
			cout<<"                                    ���� "<<endl;
			cout<<"                                 �ļ�����ɹ���  "<<endl;
        *nnn=0;
		break;
		}
	case 8:
		{
			p=head;
			ofstream outfile("fffffff.txt",ios::out);
			if(!outfile)
			{
				cout<<"���ļ�����";
				exit(1);
			}
			while(1)
			{
		    	p=p->next;
		    	outfile<<p->l<<" "<<p->num<<"\n"<<p->name<<"\n"<<p->sex<<"\n"<<p->age<<"\n"<<p->department<<"\n"<<p->date.year<<"\n"<<p->date.month<<"\n"<<p->date.day<<"\n"<<p->job<<"\n"<<p->relation<<"\n"<<p->bonus<<"\n"<<p->deductwage<<"\n"<<p->basicwage<<endl;
		    	switch(p->l)
				{
		    	case 1:outfile<<p->saleroom<<"\n"<<endl;break;
		       	case 2:outfile<<p->hours<<"\n"<<endl;break;
		    	case 3:outfile<<p->grade<<"\n"<<p->subsidy<<"\n"<<endl;break;
		    	case 4:outfile<<p->grade<<"\n"<<p->subsidy<<"\n"<<p->saleroom<<"\n"<<endl;break;
		    	case 5:outfile<<p->grade<<"\n"<<p->subsidy<<"\n"<<p->hours<<"\n"<<endl;break;
				}
				if(p->next==0){outfile<<0;break;}
			}
			cout<<"                                  �q����r"<<endl;
			cout<<"                                  {/ ��� /}"<<endl;
			cout<<"                                   ( (oo) ) "<<endl;
			cout<<"                                    ����  "<<endl;
			cout<<"                                 �ļ�����ɹ���  "<<endl;

		outfile.close();
		*nnn=0;
        break;
		}
	}
}
void error()
{
	        system("color 47");//��ɫ��������������
			cout<<"                                  �q����r"<<endl;
			cout<<"                                  {/ -  - /}"<<endl;
			cout<<"                                   ( (..) ) "<<endl;
			cout<<"                                    ��Ц�  "<<endl;
			cout<<"                                     ���� "<<endl;
			_sleep(30);
}
void main()
{
	int nnn;
	control c;
	while(1)
	{
	   	 cout<<"\n\n\n\n";
		 cout<<"                ._______________________________________________."<<endl;
		 cout<<"                | _____________________________________________ |"<<endl;
		 cout<<"                | I                                           I |"<<endl;
		 cout<<"                | I         ��ӭʹ�ñ�ְ����Ϣ����ϵͳ        I |"<<endl;
		 cout<<"                | I     1.�޸�ְ����Ϣ      2.��ѯְ����Ϣ    I |"<<endl;
		 cout<<"                | I     3.ɾ��ְ����Ϣ      4.���ְ����Ϣ    I |"<<endl;
		 cout<<"                | I     5.��ʾ����ְ����Ϣ  6.����Ա������    I |"<<endl;
		 cout<<"                | I     7.����ְ����Ϣ      8.����Ա����Ϣ    I |"<<endl;
		 cout<<"                | I                 9.�˳�ϵͳ                I |"<<endl;
		 cout<<"                | I                                           I |"<<endl;
		 cout<<"                | I               ��������Ӧ��ţ�            I |"<<endl;
		 cout<<"                | I___________________________________________I |"<<endl;
		 cout<<"                !_______________________________________________!"<<endl;
		 cout<<"                              ._[_______________]_.              "<<endl;
		 cout<<"                          .___|___________________|___.          "<<endl;
		 cout<<"                          |:::  ____               :::|          "<<endl;
		 cout<<"                          |     ~~~~        [CD-ROM]  |          "<<endl;
		 cout<<"                          |  �� o                     |          "<<endl;
		 cout<<"                          !___________________________!          "<<endl;
		 cout<<"                                   �������ţ�";
	     cin>>nnn;	 
		 cout<<"\n\n\n\n";
		 if(nnn>9)error();
		 while(nnn<9&&nnn>0)
			 c.choose(&nnn);
		 if(nnn==9)
		 {
			 system("cls");//ˢ��
			 system("color f2");

			 cout<<"                                   ��      ��   "<<endl;
             cout<<"                                  ����    ����  "<<endl;
			 cout<<"                                  |  |   /  /   "<<endl;
			 cout<<"                                  |  |  /  /    "<<endl;
			 cout<<"                                  |  | /  /     "<<endl;
			 cout<<"                                  |  |/  ;-._   "<<endl;
			 cout<<"                                  }  ` _/  / ;  "<<endl;
			 cout<<"                                  |  /` ) /  /  "<<endl;
			 cout<<"                                  | /  /_/\_/ |  \n";
			 cout<<"                                  |/  /      |  "<<endl;
			 cout<<"                                  (  ' \ '    | "<<endl;
			 cout<<"                                   (     `. /   "<<endl;
			 cout<<"                                    | С�� |    "<<endl;
			 cout<<"                                    |������|    "<<endl;
			 cout<<"                                    | С�� |    "<<endl;
			 cout<<"                               ��л��ʹ�ñ�����ϵͳ��  "<<endl;
			 break;
		 }
	}
}
 