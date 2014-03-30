using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using MarketManage;

namespace WindowsFormsApplication1
{
    public partial class guanliyisheng : Form
    {
        
        SqlConnect s = new SqlConnect();
        int i = 0;//用来记录查找出来的表中共有多少条信息
        int b = 0;//用来标记是否信息是修改的或者新建的.新建的为1.修改的为2
        int num;
        string name;
        string sex;
        int age;
        string telephone;
     //   int guahao;
        int keshihao;
        public guanliyisheng()
        {
            InitializeComponent();
            getyisheng ();
        }
        
        public void getyisheng()//显示全部患者信息
        {
            s.Open();
            string sql = "select num 编号,name 医生姓名,sex 性别,age 年龄,telephone 联系方式,keshihao 科室号 from yy_yisheng";
            DataTable dt = s.GetDataTable(sql);
            dataGridView1.DataSource = dt;
            i = dt.Rows.Count;
            s.Close();
        }

        //获取每一行的消息信息到textBox中
        private void dataGridView1_CellMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            textBox1.Text = dataGridView1.SelectedRows[0].Cells[0].Value.ToString();
            textBox2.Text = dataGridView1.SelectedRows[0].Cells[1].Value.ToString();
            comboBox1.Text = dataGridView1.SelectedRows[0].Cells[2].Value.ToString();
            textBox4.Text = dataGridView1.SelectedRows[0].Cells[3].Value.ToString();
            textBox5.Text = dataGridView1.SelectedRows[0].Cells[4].Value.ToString();
    //        textBox6.Text = dataGridView1.SelectedRows[0].Cells[5].Value.ToString();
            textBox7.Text = dataGridView1.SelectedRows[0].Cells[5].Value.ToString();

            yuanshinum = zhuanhuan(textBox1.Text);//保存一下更改之前的num值
        }
    
        public void chongzhi()//重置所有信息
        {
            textBox1.Text = null;
            textBox2.Text = null;
            comboBox1.Text = null;
            textBox4.Text = null;
            textBox5.Text = null;
     //       textBox6.Text = null;
            textBox7.Text = null;
        }
        int zhuanhuan(string s)//用来把string类型的数据转换成int类型.防止空字符串的时候int.parse无法运行.
        {
            int i;
            if (s == "")
                i = 0;
            else
                i = int.Parse(s);
            return i;
        }
        void getmassage()//获取文本框上的信息
        {
            num = zhuanhuan(textBox1.Text);
            name = textBox2.Text;
            sex = comboBox1.Text;
            age=zhuanhuan(textBox4.Text);
            telephone = textBox5.Text;
        //    guahao=zhuanhuan(textBox6.Text);
            keshihao=zhuanhuan(textBox7.Text);
        }

        public void baocun()
        {

            getmassage();
            s.Open();
            string chazhao = "select num from yy_yisheng where num='"+num+"'";
            if (s.GetDataTable(chazhao).Rows.Count == 0)
            {
                string sql = "insert into yy_yisheng(num,name,sex,age,telephone,keshihao,password) values('" + num + "','" + name + "','" + sex + "','" + age + "','" + telephone + "','" + keshihao + "','1')";//密码默认为1
                int n = s.ExecuteNonQuery(sql);
                if (n < 0)
                {
                    MessageBox.Show("保存失败！");
                }
                else
                {
                    MessageBox.Show("保存成功！");
                    sql = "select num 编号,name 医生姓名,sex 性别,age 年龄,telephone 联系方式,keshihao 科室号 from yy_yisheng where num='" + num + "'";
                    DataTable dt = s.GetDataTable(sql);
                    dataGridView1.DataSource = dt;
                }
            }
            else
            {
                MessageBox.Show("编号重复,请重新输入！");
            }
            s.Close();
        }
        void chaxun()//查询函数
        {
            getmassage();
            s.Open ();
            string sql = "select num 编号,name 医生姓名,sex 性别,age 年龄,telephone 联系方式,keshihao 科室号 from yy_yisheng where password='1' ";//编写sql语句,通过一些if语句来实现输入信息越多,查询范围越少
           
            string snum = "and num='" + num + "' ";
            string sname = "and name='"+name+"' ";
            string ssex = "and sex='" + sex + "' ";
            string sage = "and age='" + age + "' ";
            string stelephone = "and telephone='" + telephone + "' ";
     //       string sguahao = "and guahao='" + guahao + "' ";
            string skeshihao = "and keshihao='" + keshihao + "' ";
            if (num != 0)
                sql = sql + snum;
            if (name != "")
                sql = sql + sname;
            if (sex != "")
                sql = sql + ssex;
            if (age != 0)
                sql = sql + sage;
            if (telephone != "")
                sql = sql + stelephone;
      //      if (guahao != 0)
       //         sql = sql + sguahao;
            if (keshihao != 0)
                sql = sql + skeshihao;
            DataTable dt = s.GetDataTable(sql);
            if (dt.Rows.Count == 0)
            {
                MessageBox.Show("查无此人,请重新输入查询信息.");
                chongzhi();
            }
            else 
            {  
                dataGridView1.DataSource = dt;
            }
            s.Close();
        }
        private void button5_Click(object sender, EventArgs e)//新建按钮
        {
            b = 1;
            chongzhi();
        }
        private void button4_Click_1(object sender, EventArgs e)//保存按钮
        {
            if(b==1)
                baocun();
            if (b == 2)
                xiugai();
        }

        private void button1_Click_1(object sender, EventArgs e)//查询按钮
        {
            b = 0;
            yuanshinum = zhuanhuan(textBox1.Text);//保存一下更改之前的num值
            chaxun();
        }

        private void button6_Click(object sender, EventArgs e)//重置按钮
        {
            chongzhi();
        }
        void xiugai()           //修改函数
        {
            getmassage();
            s.Open();
            if (num == yuanshinum)
            {
                string sql = "update yy_yisheng set name='" + name + "',sex='" + sex + "',age='" + age + "',telephone='" + telephone + "',keshihao='" + keshihao + "' where num='"+num+"'" ;
                int n = s.ExecuteNonQuery(sql);
                if (n == 0)
                {
                    MessageBox.Show("修改失败！");
                }
                else
                {
                    MessageBox.Show("修改成功！");
                    sql = "select num 编号,name 医生姓名,sex 性别,age 年龄,telephone 联系方式,keshihao 科室号 from yy_yisheng where num='" + num + "'";
                    DataTable dt = s.GetDataTable(sql);
                    dataGridView1.DataSource = dt;
                }
            }
            else
            {
                MessageBox.Show("请勿修改编号！");
                textBox1.Text = yuanshinum.ToString();
            }
            s.Close();
 
        }


        int yuanshinum;//用来记录修改前的num.  num不能修改.
        private void button2_Click_1(object sender, EventArgs e)//修改按钮
        {
            b = 2;
        }

        private void button3_Click_1(object sender, EventArgs e)//删除按钮
        {
            b = 0;
            shanchu();
        }
        void shanchu()        //删除函数
        {
            getmassage();
            s.Open();
            if (num == yuanshinum)
            {
                queren q = new queren();//弹出确认窗口.并判断
                q.ShowDialog();
                if (q.b)
                {
                    string sql = "delete from yy_yisheng  where num='" + num + "'";
                    int n = s.ExecuteNonQuery(sql);
                    if (n == 0)
                    {
                        MessageBox.Show("删除失败！");
                    }
                    else
                    {
                        MessageBox.Show("删除成功！");
                        getyisheng();
                    }
                }
            }
            else
            {
                MessageBox.Show("请勿修改编号！");
                textBox1.Text = yuanshinum.ToString();
            }
            s.Close();
        }

        private void button7_Click_1(object sender, EventArgs e)
        {
            this.Close();
        }

    }
}
