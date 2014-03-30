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
    public partial class yihuan : Form
    {
        SqlConnect s = new SqlConnect();
        int i = 0;//用来记录查找出来的表中共有多少条信息
        int b = 0;//用来标记是否信息是修改的或者新建的.新建的为1.修改的为2
        int hznum;
        int ysnum;
        string hzname;
        string ysname;
        DateTime time;
        bool bool1 = false;//用来记录时间是否被改变过....这时才会加上查询时间的sqlyuju
        int c = 0;//用来区别信息表中显示的是医患关系(0),患者信息(1).医生信息(2);来定义不同的信息表下鼠标点击时,不同的获取信息方式


        public yihuan()//构造函数
        {
            InitializeComponent();
            getyihuan();
        }

   /*     void creatview() //创建医患的视图
        {
            s.Open();
            string sql = "create view yy_yihuanview as select yy_huanzhe.num 患者编号,yy_huanzhe.name 患者姓名,yy_yisheng.num 医生编号,yy_yisheng.name 医生姓名,time 看病时间,yy_huanzhe.password password from yy_yisheng,yy_huanzhe,yy_yihuanguanxi where yy_yisheng.num=yishengnum and yy_huanzhe.num=huanzhenum";//password 用来方便写查找语句
            s.ExecuteNonQuery(sql);
            s.Close();
        }
        void dropview()//删除视图
        {
            s.Open();
            string sql = "drop view yy_quyaoview";
            s.ExecuteNonQuery(sql);
            s.Close();
        }
    * */
        void getyihuan()//显示全部医患关系
        {
            s.Open();
            //     creatview();
            //显示视图
            string sql = "select 患者编号,患者姓名,医生编号,医生姓名,看病时间 from yy_yihuanview";
            DataTable dt = s.GetDataTable(sql);
            dataGridView1.DataSource = dt;
            i = dt.Rows.Count;
            s.Close();
 
        }
        //获取每一行的消息信息到textBox中
        private void dataGridView1_CellMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            if (c == 0)
            {
                textBox5.Text = dataGridView1.SelectedRows[0].Cells[0].Value.ToString();
                textBox1.Text = dataGridView1.SelectedRows[0].Cells[1].Value.ToString();
                textBox6.Text = dataGridView1.SelectedRows[0].Cells[2].Value.ToString();
                textBox2.Text = dataGridView1.SelectedRows[0].Cells[3].Value.ToString();
                dateTimePicker1.Text = dataGridView1.SelectedRows[0].Cells[4].Value.ToString();
            }
            if (c == 1)
            {
                textBox5.Text = dataGridView1.SelectedRows[0].Cells[0].Value.ToString();
                textBox1.Text = dataGridView1.SelectedRows[0].Cells[1].Value.ToString();
                c = 0;
            }
            if (c == 2)
            {
                textBox6.Text = dataGridView1.SelectedRows[0].Cells[0].Value.ToString();
                textBox2.Text = dataGridView1.SelectedRows[0].Cells[1].Value.ToString();
                c = 0;
            }
        }
        public void chongzhi()//重置所有信息
        {
            bool1 = false;
            textBox1.Text = null;
            textBox2.Text = null;           
            textBox5.Text = null;
            textBox6.Text = null;
            dateTimePicker1.Text = null;
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
        DateTime zhuanhuanriqi(string s)//将字符串转换为datetime类型;
        {
            DateTime d;
            if (s == "")
                d = DateTime.Now;
            else
                d = DateTime.Parse(s); //将字符串转换datetime类型
            return d;
        }
        void getmessage()//获取文本框上的信息
        {
            hznum = zhuanhuan(textBox5.Text);
            ysnum = zhuanhuan(textBox6.Text);
            hzname = textBox1.Text;
            ysname = textBox2.Text;         
            time = zhuanhuanriqi(dateTimePicker1.Text);
        }
        public void baocun()//保存函数
        {
            getmessage();
            s.Open();
            string sql = "insert into yy_yihuanguanxi(huanzhenum,yishengnum,time) values('" + hznum + "','" + ysnum + "','" + time + "')";
            int n = s.ExecuteNonQuery(sql);
            if (n <= 0)
            {
                MessageBox.Show("保存失败！");
            }
            else
            {
                MessageBox.Show("保存成功！");
                sql = "select 患者编号,患者姓名,医生编号,医生姓名,看病时间 from yy_yihuanview";
                DataTable dt = s.GetDataTable(sql);
                dataGridView1.DataSource = dt;
            }

            s.Close();
        }
        void chaxun()//查询函数
        {
            getmessage();
            s.Open();
            string sql = "select 患者编号,患者姓名,医生编号,医生姓名,看病时间 from yy_yihuanview where password='1' ";//编写sql语句,通过一些if语句来实现输入信息越多,查询范围越少

            string shznum = "and 患者编号='" + hznum + "' ";
            string sypnum = "and 医生编号='" + ysnum + "' ";
            string shzname = "and 患者姓名='" + hzname + "' ";
            string sypname = "and 医生姓名='" + ysname + "' ";
            string stime = "and 看病时间='" + time + "' ";
            if (hznum != 0)
                sql = sql + shznum;
            if (ysnum != 0)
                sql = sql + sypnum;
            if (hzname != "")
                sql = sql + shzname;
            if (ysname != "")
                sql = sql + sypname;
            //     if (bool1)
            //        sql = sql + stime;            
            DataTable dt = s.GetDataTable(sql);
            if (dt.Rows.Count == 0)
            {
                MessageBox.Show("查无此信息,请重新输入查询信息.");
                chongzhi();
            }
            else
            {
                dataGridView1.DataSource = dt;
            }
            s.Close();
        }

        private void button4_Click(object sender, EventArgs e)//保存按钮
        {
            if (b == 1)
                baocun();
            b = 0;
        }

        private void button1_Click(object sender, EventArgs e)//查询按钮
        {
            b = 0;
            chaxun();
        }

        private void button6_Click(object sender, EventArgs e)//重置按钮
        {
            chongzhi();
        }

        void shanchu()        //删除函数
        {
            getmessage();
            s.Open();
            queren q = new queren();//弹出确认窗口.并判断
            q.ShowDialog();
            if (q.b)
            {
                string sql = "delete from yy_yihuanguanxi  where huanzhenum='" + hznum + "' and yishengnum='" + ysnum + "'";
                int n = s.ExecuteNonQuery(sql);
                if (n == 0)
                {
                    MessageBox.Show("删除失败！");
                }
                else
                {
                    MessageBox.Show("删除成功！");
                    getyihuan();
                }
            }

            s.Close();
        }

        private void button3_Click(object sender, EventArgs e)//删除按钮
        {
            b = 0;
            shanchu();
        }

        private void button5_Click(object sender, EventArgs e)//新建按钮
        {
            b = 1;
            chongzhi();
        }

        private void textBox5_TextChanged(object sender, EventArgs e)//点击更改患者编号文本框的时候触发的操作
        {
            if (textBox5.Text != "" && b == 1)//在文本框值不是空的时候,并且是点击新建按钮之后才调用此函数
            {
                hznum = zhuanhuan(textBox5.Text);
                s.Open();
                //显示此患者编号的信息
                string sql = "select num 编号,name 患者姓名,sex 性别,age 年龄,telephone 联系方式,guahao 挂号,keshihao 科室号 from yy_huanzhe where num='" + hznum + "'";
                if (s.GetDataTable(sql).Rows.Count == 0)
                {
                    MessageBox.Show("无此患者编号.请重新输入");
                    c = 1;
                    sql = "select num 编号,name 患者姓名,sex 性别,age 年龄,telephone 联系方式,guahao 挂号,keshihao 科室号 from yy_huanzhe";
                }
                DataTable dt = s.GetDataTable(sql);
                dataGridView1.DataSource = dt;

                textBox1.Text = dataGridView1.SelectedRows[0].Cells[1].Value.ToString();

                s.Close();
            }
        }

        private void textBox6_TextChanged(object sender, EventArgs e)//点击更改医生编号文本框时触发的操作
        {
            if (textBox6.Text != "" && b == 1)
            {
                ysnum = zhuanhuan(textBox6.Text);
                s.Open();
                //显示此医生编号的信息
                string sql = "select num 编号,name 医生姓名,sex 性别,age 年龄,telephone 联系方式,keshihao 科室号 from yy_yisheng where num='" + ysnum + "'";
                if (s.GetDataTable(sql).Rows.Count == 0) //当输入的编号,在数据库中没有的时候出现警告提示.
                {
                    MessageBox.Show("无此医生编号.请重新输入");
                    c = 2;
                    sql = "select num 编号,name 医生姓名,sex 性别,age 年龄,telephone 联系方式,keshihao 科室号 from yy_yisheng";
                }
                DataTable dt = s.GetDataTable(sql);
                dataGridView1.DataSource = dt;

                textBox2.Text = dataGridView1.SelectedRows[0].Cells[1].Value.ToString();

                s.Close();
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void textBox1_Leave(object sender, EventArgs e)//输入完患者姓名离开文本框时触发的操作
        {
            if (textBox1.Text != "" && b == 1)//在文本框值不是空的时候,并且是点击新建按钮之后才调用此函数
            {
                hzname = textBox1.Text;
                s.Open();
                //显示此患者的信息
                string sql = "select num 编号,name 患者姓名,sex 性别,age 年龄,telephone 联系方式,guahao 挂号,keshihao 科室号 from yy_huanzhe where name='" + hzname + "'";
                if (s.GetDataTable(sql).Rows.Count == 0)
                {
                    MessageBox.Show("无此患者.请重新输入");
                    c = 1;
                    sql = "select num 编号,name 患者姓名,sex 性别,age 年龄,telephone 联系方式,guahao 挂号,keshihao 科室号 from yy_huanzhe";
                }
                DataTable dt = s.GetDataTable(sql);
                dataGridView1.DataSource = dt;

                textBox5.Text = dataGridView1.SelectedRows[0].Cells[0].Value.ToString();

                s.Close();
            }
        }

        private void textBox2_Leave(object sender, EventArgs e)//输入完医生姓名离开文本框时触发的操作
        {
            if (textBox2.Text != "" && b == 1)
            {
                ysname = textBox2.Text;
                s.Open();
                //显示此医生的信息
                string sql = "select num 编号,name 医生姓名,sex 性别,age 年龄,telephone 联系方式,keshihao 科室号 from yy_yisheng where name='" + ysname + "'";
                if (s.GetDataTable(sql).Rows.Count == 0) //当输入的编号,在数据库中没有的时候出现警告提示.
                {
                    MessageBox.Show("无此医生.请重新输入");
                    c = 2;
                    sql = "select num 编号,name 医生姓名,sex 性别,age 年龄,telephone 联系方式,keshihao 科室号 from yy_yisheng";
                }
                DataTable dt = s.GetDataTable(sql);
                dataGridView1.DataSource = dt;

                textBox6.Text = dataGridView1.SelectedRows[0].Cells[0].Value.ToString();

                s.Close();
            }
        }
    }
}
