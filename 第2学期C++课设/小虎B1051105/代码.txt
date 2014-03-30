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
	cout<<"请按年、月、日输入：";
	cin>>d.year>>d.month>>d.day;
	if((d.year%4==0&&d.year%100!=0)||(d.year%400==0))
		a[1]=29;
	while(1)
	{
	   if(d.year<=0||d.month<=0||d.day<=0||d.month>12||d.day>a[d.month-1])
	   {
		   error();
   		  cout<<"输入错误，请重新输入：";
	   	  cin>>d.year>>d.month>>d.day;
		  system("color bd");
	   } 
	   else break;
	}
}

void display(Date&d)
{
	cout<<d.year<<"年"<<d.month<<"月"<<d.day<<"日"<<endl;
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
	cout<<"请输入员工信息\n";
	cout<<"编号：";
	cin>>num;
	cout<<"姓名：";
	cin>>name;
	cout<<"性别(man或者woman)：";
	cin>>sex;
	while(1)
	{
	    if((sex>"mam"&&sex<"mao")||(sex>"womam"&&sex<"womao")){break;}
    	else
		{
			error();
	    	cout<<"输入错误，请重新输入：";
	    	cin>>sex;
			system("color bd");
		}
	}
	cout<<"年龄：";
	cin>>age;
	while(1)
	{
		if(age>0)break;
		else
		{
			error();
		    cout<<"输入错误，请重新输入：";
	    	cin>>age;
		}
	}
	cout<<"部门:";
	cin>>department;
	cout<<"参加工作时间：";
	set(date);
	cout<<"职务：";
	cin>>job;
	cout<<"联系方式：";
	cin>>relation;
	cout<<"奖金：";
	cin>>bonus;
	while(1)
	{
    	if(bonus<0)
		{
			error();
		    cout<<"输入错误，请重新输入：";
		    cin>>bonus;
		}
		else break;
	}
	cout<<"扣发工资：";
	cin>>deductwage;
	while(1)
	{
    	if(deductwage<0)
		{
			error();
		    cout<<"输入错误，请重新输入：";
		    cin>>deductwage;
		}
		else break;
	}
	cout<<"基本工资";
	cin>>basicwage;
	while(1)
	{
    	if(basicwage<0)
		{
			error();
		    cout<<"输入错误，请重新输入：";
		    cin>>basicwage;
		}
		else break;
	}
}

void staff::Display()
{
	cout<<"\n\n员工的基本信息如下：";
	cout<<"\n编号："<<num;
	cout<<"\n姓名："<<name;
	cout<<"\n性别："<<sex;
	cout<<"\n年龄："<<age;
	cout<<"\n部门:"<<department;
	cout<<"\n参加工作时间：";
	display(date);
	cout<<"职务："<<job;
	cout<<"\n联系方式："<<relation;
	cout<<"\n奖金："<<bonus;
	cout<<"\n扣发工资："<<deductwage;
	cout<<"\n基本工资"<<basicwage<<endl;
}
double staff::wages()
{
	return basicwage+bonus-deductwage;
}
/////////////////////////////////////////《《经理类》》///////////////////////////////////////////////////
class manager:virtual public staff
{	
public:
	friend istream & operator<<(istream & in,manager &m);
    friend ostream & operator>>(ostream & out,manager &m);
	void SET();
	void DISPLAY();
	void WAGE(){cout<<"实发工资为："<<Wage()<<endl;}
	double Wage(){return wages()+subsidy;}
};
istream & operator>>(istream & in,manager &m)
{
	m.Set();
	cout<<"请输入级别：";
	in>>m.grade;
	cout<<"请输入职务津贴：";
	in>>m.subsidy;
	return in;
}
ostream & operator<<(ostream & out,manager &m)
{
	m.Display();
	out<<"级别："<<m.grade<<endl;
	out<<"职务津贴："<<m.subsidy<<endl;
	return out;
}
void manager::SET(){l=3;cin>>*this;}              //要想在本类中调用本类的某个函数，必须在这个被调用的函数完全写完后在调用这个函数所以把左边这个函数用了类外定义，并且写在运算符重载的后面。
void manager::DISPLAY(){cout<<*this;}
///////////////////////////////////////《《销售人员类》》////////////////////////////////////////////
class salesman:virtual public staff
{
protected:
	double ticheng;
public:                     //如果以后用到运算符重载可以就像基类那样之久调用set函数或者display函数。
	void SET();
	void DISPLAY();
	void WAGE(){cout<<"实发工资为："<<wages()+wage()<<endl;}
	double wage();
};
void salesman::SET()
{
	l=1;
	Set();
	cout<<"请输入销售额："<<endl;
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
	cout<<"销售额为："<<saleroom<<endl;
	cout<<"实发工资为："<<wages()+wage()<<endl;
}
////////////////////////////////////////《《技术人员类》》///////////////////////////////////////////
class technician:virtual public staff
{
protected:
	int money;
public:
	void SET();
	void DISPLAY();
    void WAGE(){cout<<"实发工资为："<<wages()+wage()<<endl;}
	double wage();
};
void technician::SET()
{
	l=2;
	Set();
	cout<<"请输入工作时数(时/月):"<<endl;
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
	cout<<"工作时数为："<<hours<<"时/月"<<endl;
	cout<<"实发工资为："<<wages()+wage()<<endl;
}
/////////////////////////////////////////《《销售经理类》》////////////////////////////////////////
class salesmanager:public manager,public salesman
{
public:
	void SET();
	void DISPLAY();
	void WAGE(){cout<<"实发工资为："<<Wage()+wage()<<endl;}
};
void salesmanager::SET()
{
	l=4;
	cin>>*this;
	cout<<"请输入销售额："<<endl;
	cin>>saleroom;
}
void salesmanager::DISPLAY()
{
	cout<<*this;
	cout<<"销售额为："<<saleroom<<endl;
	cout<<"实发工资为："<<Wage()+wage()<<endl;
}
//////////////////////////////////////////《《技术总监类》》////////////////////////////////////////
class techmanager:public manager,public technician
{
public:
	void SET();
	void DISPLAY();
	void WAGE(){cout<<"实发工资为："<<Wage()+wage()<<endl;}
};
void techmanager::SET()
{
	l=5;
	cin>>*this;
	cout<<"请输入工作时数(时/月):"<<endl;
	cin>>hours;
}
void techmanager::DISPLAY()
{
	cout<<*this;
	cout<<"工作时数为："<<hours<<"时/月"<<endl;
	cout<<"实发工资为："<<Wage()+wage()<<endl;
}
////////////////////////////////////////////《《管理类》》//////////////////////////////////////////////////////////////////
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
//	p=head=new staff;///终于明白了是这里每次都会变成新的。所以这这个不能放这里。所以放在构造函数中最合适嘿嘿。
	switch(a)
	{
	case 4:
		{
			p=head;
			while(p->next!=0)////////////用来把p指针指向链表的末尾。
			{
				p=p->next;
			}
			int n;
			system("cls");
			system("color bd");
                  cout<<"               **************************************************\n";
                  cout<<"               *                                                *\n";
                  cout<<"               *            请选择要添加员工的职务              *\n";
                  cout<<"               *        1.销售人员          2.技术人员          *\n";
                  cout<<"               *                    3.经理                      *\n";
                  cout<<"               *        4.销售经理          5.技术总监          *\n";
                  cout<<"               *                                                *\n";
                  cout<<"               *                 请输入相应编号：               *\n";
                  cout<<"               *                                                *\n";
                  cout<<"               **************************************************\n";
		          cout<<"                                   请输入编号：";
	              cin>>n;
		          cout<<"\n\n\n\n";
				  switch(n)
				  {
                   case 1:///////////////////////////////后来教别人的时候的新的灵感，新的好想法。这样就可以不用goto语句了。
					   {
						  p=head;
                     	  r=new salesman;  
	             		  r->SET();
						  while(p->next!=0)/////要想连接链表，必须用指向最后一个成员的指针来连接，不能用指向最后一个成员的next的指针连接。
						  {
							  p=p->next;
							  if(r->num==p->num)
							  {
								  error();
								  cout<<"员工编号重复，请重新输入\n";
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
								  cout<<"员工编号重复，请重新输入\n";
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
								  cout<<"员工编号重复，请重新输入\n";
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
								  cout<<"员工编号重复，请重新输入\n";
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
								  cout<<"员工编号重复，请重新输入\n";
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
					cout<<"               *         1.继续添加职工信息                     *\n";
					cout<<"               *         2.返回上一目录                         *\n";
					cout<<"               *         3.退出信息管理系统                     *\n";
					cout<<"               *                                                *\n";
					cout<<"               *                 请输入相应编号：               *\n";
					cout<<"               *                                                *\n";
					cout<<"               **************************************************\n";
					cout<<"                                    请输入编号：";
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
				cout<<"还未存入员工数据。请先添加。\n";
				*nnn=0;
				break;
			}
			        cout<<"               **************************************************\n";
					cout<<"               *                                                *\n";
					cout<<"               *         1.按编号查询          2.按姓名查询     *\n";
					cout<<"               *         3.按部门查询          4.按职务查询     *\n";
					cout<<"               *                                                *\n";
					cout<<"               *                 请输入相应编号：               *\n";
					cout<<"               *                                                *\n";
					cout<<"               **************************************************\n";
					cout<<"                                   请输入编号：";
			cin>>m;
			cout<<"\n\n\n\n";
			switch(m)
			{
			case(1):
				{
				cout<<"\n请输入查询的编号：";
		    	cin>>n;
			    while(1)
				{
	    			p=p->next;
	     			if(p->num==n)
					{
			    		p->DISPLAY();
			    		break;          //这里的break只能打断while语句，没有打断case语句。所以后面得加上break。
					}
		    		if(p->next==0)//来防止死循环下去，就会停止工作。记得只能是写p->next而不是p。
					{
						error();
						string x;
		    			cout<<"输入数据错误。重新输入?(y/n)";
						cin>>x;
						if(x=="y")
						{
						cout<<"\n请输入查询的编号：";
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
				cout<<"\n请输入查询的姓名：";
		    	cin>>n;
			    while(1)
				{
	    			p=p->next;
	     			if(p->name==n)
					{
			    		p->DISPLAY();
			    	//	break;          //这里的break只能打断while语句，没有打断case语句。所以后面得加上break。
						//取消break的原因是如果用重名的，就只能显示编号在前面的人，只有取消了break才能都显示出来。
						k=1;
					}
                    if(p->next==0&&k)
						break;
		    		if(p->next==0&&!k)//来防止死循环下去，就会停止工作。记得只能是写p->next而不是p。
					{
						error();
						string x;
		    			cout<<"输入数据错误。重新输入?(y/n)";
						cin>>x;
						if(x=="y")
						{
							cout<<"\n请输入查询的姓名：";
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
				cout<<"\n请输入查询的部门：";
		    	cin>>n;
			    while(1)
				{
	    			p=p->next;
	     			if(p->department==n)
					{
			    		p->DISPLAY();
			    		break;          //这里的break只能打断while语句，没有打断case语句。所以后面得加上break。
					}
		    		if(p->next==0)//来防止死循环下去，就会停止工作。记得只能是写p->next而不是p。
					{
						error();
						string x;
		    			cout<<"输入数据错误。重新输入?(y/n)";
						cin>>x;
						if(x=="y")
						{
							cout<<"\n请输入查询的部门：";
		    			cin>>n;
		    			p=head;
						}
						else break;					}
				}
				break;
				}
			case(4):
				{
				cout<<"\n请输入查询的职务：";
		    	cin>>n;
			    while(1)
				{
	    			p=p->next;
	     			if(p->job==n)
					{
			    		p->DISPLAY();
			    		break;          //这里的break只能打断while语句，没有打断case语句。所以后面得加上break。
					}
		    		if(p->next==0)//来防止死循环下去，就会停止工作。记得只能是写p->next而不是p。
					{
						error();
						string x;
		    			cout<<"输入数据错误。重新输入?(y/n)";
						cin>>x;
						if(x=="y")
						{
							cout<<"\n请输入查询的职务：";
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
					cout<<"               *         1.继续查询职工信息                     *\n";
					cout<<"               *         2.返回上一目录                         *\n";
					cout<<"               *         3.退出信息管理系统                     *\n";
					cout<<"               *                                                *\n";
					cout<<"               *                 请输入相应编号：               *\n";
					cout<<"               *                                                *\n";
					cout<<"               **************************************************\n";
					cout<<"                                   请输入编号：";
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
				cout<<"还未存入员工数据。请先添加。\n";
				*nnn=0;
				break;
			}
            string n;


			        cout<<"               **************************************************\n";
					cout<<"               *                                                *\n";
					cout<<"               *         1.按编号删除          2.按姓名删除     *\n";
					cout<<"               *         3.按部门删除          4.按职务删除     *\n";
					cout<<"               *                                                *\n";
					cout<<"               *                 请输入相应编号：               *\n";
					cout<<"               *                                                *\n";
					cout<<"               **************************************************\n";
					cout<<"                                   请输入编号：";
			cin>>d;
			cout<<"\n\n\n\n";
           switch(d)
			{
			case 1:
				{
        			cout<<"\n请输入需要删除人员的编号：";
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
							cout<<"               *                  是否确认删除？                *\n";					
							cout<<"               *                                                *\n";
							cout<<"               *           Y.确认删除       N.取消删除          *\n";
							cout<<"               *                                                *\n";
							cout<<"               *                                                *\n";
							cout<<"               *                 请输入相应字母：               *\n";
							cout<<"               *                                                *\n";
							cout<<"               **************************************************\n";
							cout<<"                                   请输入字母：";
							cin>>m;
							cout<<"\n\n\n\n";
							if(m=='y')
							{
							    r->next=p->next;
				//		    	delete p;           //////////////////////这里为什么不能运行呢？为什么会终止呢?
							    cout<<"删除成功!\n";
							    break;
							}
							else if(m=='n')  {cout<<"已取消删除\n";break;}
							else cout<<"输入错误已取消删除\n";
						}
						if(p->next==0)//来防止死循环下去，就会停止工作。记得只能是写p->next而不是p。
						{
						error();
						string x;
		    			cout<<"输入数据错误。重新输入?(y/n)";
						cin>>x;
						if(x=="y")
						{
						cout<<"\n请输入需要删除人员的编号：";
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
        			cout<<"\n请输入需要删除人员的姓名：";
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
							cout<<"               *                  是否确认删除？                *\n";					
							cout<<"               *                                                *\n";
							cout<<"               *           Y.确认删除       N.取消删除          *\n";
							cout<<"               *                                                *\n";
							cout<<"               *                                                *\n";
							cout<<"               *                 请输入相应字母：               *\n";
							cout<<"               *                                                *\n";
							cout<<"               **************************************************\n";
							cout<<"                                   请输入字母：";
							cin>>m;
							cout<<"\n\n\n\n";
							if(m=='y')
							{
							    r->next=p->next;
				//		    	delete p;           //////////////////////这里为什么不能运行呢？为什么会终止呢?
							    cout<<"删除成功!\n";
				//			    break;//取消的目的同样是为了查全所有的姓名，防止重名情况出现时漏掉人员。
							}
							else if(m=='n')  {cout<<"已取消删除\n";}
							else cout<<"输入错误已取消删除\n";
						}
						if(p->next==0&&k)
							break;
						if(p->next==0&&!k)//来防止死循环下去，就会停止工作。记得只能是写p->next而不是p。
						{
						error();
						string x;
		    			cout<<"输入数据错误。重新输入?(y/n)";
						cin>>x;
						if(x=="y")
						{
						cout<<"\n请输入需要删除人员的姓名：";
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
        			cout<<"\n请输入需要删除的部门：";
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
								cout<<"               *                  是否确认删除？                *\n";					
								cout<<"               *                                                *\n";
								cout<<"               *           Y.确认删除       N.取消删除          *\n";
								cout<<"               *                                                *\n";
								cout<<"               *                                                *\n";
								cout<<"               *                 请输入相应字母：               *\n";
								cout<<"               *                                                *\n";
								cout<<"               **************************************************\n";
								cout<<"                                   请输入字母：";
								cin>>m;
								cout<<"\n\n\n\n";
								if(m=='y')
								{
								     k=0;
								}
								else if(m=='n')  {cout<<"已取消删除\n";break;}
								else {cout<<"输入错误,已取消删除\n";break;}
							}
							r->next=p->next;
							cout<<"删除一个。\n";
					//		p=p->next;        /////////加上这句，就能继续删除同部门的人了。如果不加这句随着循环上去开头有个r=p.就会又把p连接回来了。这也解释了下面的delete p为什么出问题了。因为删除后，r=p就无法运行了。把这句再放delete后面就能用delete了。还是不行啊。
					 //       delete p;////////////////这里为什么不能运行呢？为什么会终止呢?厄，第一次能用，之后就不能用了呢？
							p=r;       //////////记得这里应该为p=r因为再循环回去的时候需要r=p的。以后画一下链表的图就清楚啦。

						}

////这里加入的k是个好想法。判断该执行谁。什么情况下该执行谁，
						if((p->next==0)&&(1-k))///////////这个if语句不能放在上一个里面啊。
						{
							cout<<"删除成功!\n";
							break;
						}
						if((p->next==0)&&k)//来防止死循环下去，就会停止工作。记得只能是写p->next而不是p。
						{
						error();
						string x;
		    			cout<<"输入数据错误。重新输入?(y/n)";
						cin>>x;
						if(x=="y")
						{
						cout<<"\n请输入需要删除的部门：";
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
        			cout<<"\n请输入需要删除的职务：";
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
								cout<<"               *                  是否确认删除？                *\n";					
								cout<<"               *                                                *\n";
								cout<<"               *           Y.确认删除       N.取消删除          *\n";
								cout<<"               *                                                *\n";
								cout<<"               *                                                *\n";
								cout<<"               *                 请输入相应字母：               *\n";
								cout<<"               *                                                *\n";
								cout<<"               **************************************************\n";
								cout<<"                                   请输入字母：";
								cin>>m;
								cout<<"\n\n\n\n";
								if(m=='y')
								{
								     k=0;
								}
								else if(m=='n')  {cout<<"已取消删除\n";break;}
								else {cout<<"输入错误,已取消删除\n";break;}
							}
							r->next=p->next;
							cout<<"删除一个。\n";
							p=r;       /////////////////记得这里应该为p=r因为再循环回去的时候需要r=p的。以后画一下链表的图就清楚啦。

						}

////这里加入的k是个好想法。判断该执行谁。什么情况下该执行谁，
						if((p->next==0)&&(1-k))////////////////////////这个if语句不能放在上一个里面啊。
						{
							cout<<"删除成功!\n";
							break;
						}
						if((p->next==0)&&k)//来防止死循环下去，就会停止工作。记得只能是写p->next而不是p。
						{
						error();
						string x;
		    			cout<<"输入数据错误。重新输入?(y/n)";
						cin>>x;
						if(x=="y")
						{
						cout<<"\n请输入需要删除的职务：";
		    			cin>>n;
		    			p=head;
						}
						else break;
						}
					}		
				break;
				}
			default:cout<<"输入编号错误！！！";
		   }    
			        cout<<"               **************************************************\n";
					cout<<"               *                                                *\n";
					cout<<"               *         1.继续删除职工信息                     *\n";
					cout<<"               *         2.返回上一目录                         *\n";
					cout<<"               *         3.退出信息管理系统                     *\n";
					cout<<"               *                                                *\n";
					cout<<"               *                 请输入相应编号：               *\n";
					cout<<"               *                                                *\n";
					cout<<"               **************************************************\n";
					cout<<"                                   请输入编号：";
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
				cout<<"还未存入员工数据。请先添加。\n";
				*nnn=0;
				break;
			}
			string n;
			int k=1;
			cout<<"\n请输入需要修改人员的编号：";
			cin>>n;
			while(1)
			{
				p=p->next;
				if(p->num==n)
				{
					int m;
					cout<<"               **************************************************\n";
					cout<<"               *                                                *\n";
					cout<<"               *         1.修改姓名          2.修改部门         *\n";
					cout<<"               *         3.修改职务          4.修改联系电话     *\n";
					cout<<"               *         5.修改奖金          6.修改扣发工资     *\n";
					cout<<"               *         7.修改基本工资      8.返回上级菜单     *\n";
					cout<<"               *                                                *\n";
					cout<<"               *                 请输入相应编号：               *\n";
					cout<<"               *                                                *\n";
					cout<<"               **************************************************\n";
					cout<<"                                   请输入编号：";
					cin>>m;
					cout<<"\n\n\n\n";
					switch(m)
					{
					case 1:
						{
							cout<<"请输入修改后姓名：";
							cin>>p->name;
							break;
						}
					case 2:
						{
							cout<<"请输入修改后部门：";
							cin>>p->department;
							break;
						}
					case 3:
						{
							cout<<"请输入修改后职务：";
							cin>>p->job;
							break;
						}
					case 4:
						{
							cout<<"请输入修改后联系电话：";
							cin>>p->relation;
							break;
						}
					case 5:
						{
							cout<<"请输入修改后奖金：";
							cin>>p->bonus;
							break;
						}
					case 6:
						{
							cout<<"请输入修改后扣发工资：";
							cin>>p->deductwage;
							break;
						}
					case 7:
						{
							cout<<"请输入修改后基本工资：";
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
				if(p->next==0)//来防止死循环下去，就会停止工作。记得只能是写p->next而不是p。
				{
						error();
						string x;
		    			cout<<"输入数据错误。重新输入?(y/n)";
						cin>>x;
						if(x=="y")
						{
						cout<<"\n请输入需要修改人员的编号：";
		    			cin>>n;
		    			p=head;
						}
						else break;
				}
			}
			if(k)
			{
			        cout<<"修改成功！\n";
			        cout<<"               **************************************************\n";
					cout<<"               *                                                *\n";
					cout<<"               *         1.继续修改职工信息                     *\n";
					cout<<"               *         2.返回上一目录                         *\n";
					cout<<"               *         3.退出信息管理系统                     *\n";
					cout<<"               *                                                *\n";
					cout<<"               *                 请输入相应编号：               *\n";
					cout<<"               *                                                *\n";
					cout<<"               **************************************************\n";
					cout<<"                                   请输入编号：";
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
				cout<<"还未存入员工数据。请先添加。\n";
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
					cout<<"               *         1.返回上一目录                         *\n";
					cout<<"               *         2.退出信息管理系统                     *\n";
					cout<<"               *                                                *\n";
					cout<<"               *                 请输入相应编号：               *\n";
					cout<<"               *                                                *\n";
					cout<<"               **************************************************\n";
					cout<<"                                   请输入编号：";
					int x;
					cin>>x;
					switch(x)
					{
					case 1:*nnn=0;break;
					case 2:*nnn=9;break;
					default:cout<<"输入错误编号已自动返回上一目录。\n";*nnn=0;
					}
			break;
		}
	case 6:
		{
			p=head;
			if(head->next==0)
			{
				cout<<"还未存入员工数据。请先添加。\n";
				*nnn=0;
				break;
			}
			string n;
			int k=1;
			cout<<"\n请输入需要计算工资人员的编号：";
			cin>>n;
			while(1)
			{
				p=p->next;
				if(p->num==n)
				{
					p->WAGE();
					break;
				}
				if(p->next==0)//来防止死循环下去，就会停止工作。记得只能是写p->next而不是p。
				{
						error();
						string x;
		    			cout<<"输入数据错误。重新输入?(y/n)";
						cin>>x;
						if(x=="y")
						{
						cout<<"\n请输入需要计算工资人员的编号：";
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
					cout<<"               *         1.继续计算职工工资                     *\n";
					cout<<"               *         2.返回上一目录                         *\n";
					cout<<"               *         3.退出信息管理系统                     *\n";
					cout<<"               *                                                *\n";
					cout<<"               *                 请输入相应编号：               *\n";
					cout<<"               *                                                *\n";
					cout<<"               **************************************************\n";
					cout<<"                                   请输入编号：";
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
				cout<<"打开文件错误。";
				exit(1);
			}
			r=head;
			while(1)
			{
	    		infile>>l;
				if(l==0)break;
		        //空格和回车都会间隔开，然后读入下一条信息。
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
			cout<<"文件读入中：\n";
			for(int i=0;i<30;i++)
			{
				
				cout<<"█";
				_sleep(100);
			}
			system("cls");
			system("color fd");
			cout<<"                                  ╭︿︿︿╮"<<endl;
			cout<<"                                  {/ .  . /}"<<endl;
			cout<<"                                   ( (oo) )  "<<endl;
			cout<<"                                    ︶︶︶ "<<endl;
			cout<<"                                 文件读入成功！  "<<endl;
        *nnn=0;
		break;
		}
	case 8:
		{
			p=head;
			ofstream outfile("fffffff.txt",ios::out);
			if(!outfile)
			{
				cout<<"打开文件错误。";
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
			cout<<"                                  ╭︿︿︿╮"<<endl;
			cout<<"                                  {/ ︿︿ /}"<<endl;
			cout<<"                                   ( (oo) ) "<<endl;
			cout<<"                                    ︶︶︶  "<<endl;
			cout<<"                                 文件保存成功！  "<<endl;

		outfile.close();
		*nnn=0;
        break;
		}
	}
}
void error()
{
	        system("color 47");//红色背景。。。。。
			cout<<"                                  ╭︿︿︿╮"<<endl;
			cout<<"                                  {/ -  - /}"<<endl;
			cout<<"                                   ( (..) ) "<<endl;
			cout<<"                                    ︶⌒︶  "<<endl;
			cout<<"                                     错误！ "<<endl;
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
		 cout<<"                | I         欢迎使用本职工信息管理系统        I |"<<endl;
		 cout<<"                | I     1.修改职工信息      2.查询职工信息    I |"<<endl;
		 cout<<"                | I     3.删除职工信息      4.添加职工信息    I |"<<endl;
		 cout<<"                | I     5.显示所有职工信息  6.计算员工工资    I |"<<endl;
		 cout<<"                | I     7.读入职工信息      8.保存员工信息    I |"<<endl;
		 cout<<"                | I                 9.退出系统                I |"<<endl;
		 cout<<"                | I                                           I |"<<endl;
		 cout<<"                | I               请输入相应编号：            I |"<<endl;
		 cout<<"                | I___________________________________________I |"<<endl;
		 cout<<"                !_______________________________________________!"<<endl;
		 cout<<"                              ._[_______________]_.              "<<endl;
		 cout<<"                          .___|___________________|___.          "<<endl;
		 cout<<"                          |:::  ____               :::|          "<<endl;
		 cout<<"                          |     ~~~~        [CD-ROM]  |          "<<endl;
		 cout<<"                          |  ⊙ o                     |          "<<endl;
		 cout<<"                          !___________________________!          "<<endl;
		 cout<<"                                   请输入编号：";
	     cin>>nnn;	 
		 cout<<"\n\n\n\n";
		 if(nnn>9)error();
		 while(nnn<9&&nnn>0)
			 c.choose(&nnn);
		 if(nnn==9)
		 {
			 system("cls");//刷屏
			 system("color f2");

			 cout<<"                                   ﹦      ﹦   "<<endl;
             cout<<"                                  〞〝    〞〝  "<<endl;
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
			 cout<<"                                    | 小猪 |    "<<endl;
			 cout<<"                                    |工作室|    "<<endl;
			 cout<<"                                    | 小虎 |    "<<endl;
			 cout<<"                               感谢您使用本管理系统！  "<<endl;
			 break;
		 }
	}
}
 