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
    public partial class kanyisheng : Form
    {
        SqlConnect s = new SqlConnect();
        int hznum;
        int ysnum;
        string hzname;
        string ysname;
        DateTime time;
        bool b=false;//用来记录文本框是否被点击过

        public kanyisheng(int i)
        {
            hznum = i;
            InitializeComponent();
            xianshihuanzhe();
            xianshiyisheng();
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
        void xianshihuanzhe()//将患者的信息显示到文本框上,并且不能更改.
        {
            s.Open();
            string sql = "select num 编号,name 患者姓名 from yy_huanzhe where num='" + hznum + "'";
            DataTable dt = s.GetDataTable(sql);
            textBox5.Text = dt.Rows[0][0].ToString();
            textBox1.Text = dt.Rows[0][1].ToString();

            s.Close(); 
        }
        void xianshiyisheng()//显示所有医生信息
        {
            s.Open();
            string sql = "select num 编号,name 医生姓名,sex 性别,age 年龄,telephone 联系方式,keshihao 科室号 from yy_yisheng";
            DataTable dt = s.GetDataTable(sql);
            dataGridView1.DataSource = dt;
            s.Close();
        }
        void getmessage()//获取文本框上的信息
        {
            hznum = zhuanhuan(textBox5.Text);
            ysnum = zhuanhuan(textBox6.Text);
            hzname = textBox1.Text;
            ysname = textBox2.Text;
            time = zhuanhuanriqi(dateTimePicker1.Text);
        }

        private void dataGridView1_CellMouseClick(object sender, DataGridViewCellMouseEventArgs e)//单击表格时获取医生信息到文本框上
        {
            textBox6.Text = dataGridView1.SelectedRows[0].Cells[0].Value.ToString();
            textBox2.Text = dataGridView1.SelectedRows[0].Cells[1].Value.ToString();
        }
        void baocun()//保存预约
        {
            getmessage();
            s.Open();
            if (textBox6.Text == "")
            {
                string sql1 = "select 医生编号,医生姓名,患者编号,患者姓名,看病时间 from yy_yihuanview where 患者编号='" + hznum + "'";
                DataTable dt = s.GetDataTable(sql1);
                dataGridView1.DataSource = dt;
            }
            else
            {
                string sql = "insert into yy_yihuanguanxi(huanzhenum,yishengnum,time) values('" + hznum + "','" + ysnum + "','" + time + "')";
                int n = s.ExecuteNonQuery(sql);
                if (n <= 0)
                {
                    MessageBox.Show("预约失败！");
                }
                else
                {
                    MessageBox.Show("预约成功！");
                    sql = "select 医生编号,医生姓名,患者编号,患者姓名,看病时间 from yy_yihuanview where 患者编号='" + hznum + "'";
                    DataTable dt = s.GetDataTable(sql);
                    dataGridView1.DataSource = dt;
                }
                textBox2.Enabled = false;
                textBox6.Enabled = false;
            }
            
            s.Close();
        }

        private void button7_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button4_Click(object sender, EventArgs e)//预约按钮
        {
            baocun();
        }

        private void textBox6_TextChanged(object sender, EventArgs e)//点击更改医生编号文本框时触发的操作
        {
            if (textBox6.Text != "" &&b)
            {
                ysnum = zhuanhuan(textBox6.Text);
                s.Open();
                //显示此医生编号的信息
                string sql = "select num 编号,name 医生姓名,sex 性别,age 年龄,telephone 联系方式,keshihao 科室号 from yy_yisheng where num='" + ysnum + "'";
                if (s.GetDataTable(sql).Rows.Count == 0) //当输入的编号,在数据库中没有的时候出现警告提示.
                {
                    MessageBox.Show("无此医生编号.请重新输入");
                    sql = "select num 编号,name 医生姓名,sex 性别,age 年龄,telephone 联系方式,keshihao 科室号 from yy_yisheng";
                }
                DataTable dt = s.GetDataTable(sql);
                dataGridView1.DataSource = dt;

                textBox2.Text = dataGridView1.SelectedRows[0].Cells[1].Value.ToString();
              //  textBox2.Text = dt.Rows[0][1].ToString();

                s.Close();
            }
        }

        private void textBox2_Leave(object sender, EventArgs e)//输入完医生姓名离开文本框时触发的操作
        {
            if (textBox2.Text != "" )
            {
                ysname = textBox2.Text;
                s.Open();
                //显示此医生的信息
                string sql = "select num 编号,name 医生姓名,sex 性别,age 年龄,telephone 联系方式,keshihao 科室号 from yy_yisheng where name='" + ysname + "'";
                if (s.GetDataTable(sql).Rows.Count == 0) //当输入的编号,在数据库中没有的时候出现警告提示.
                {
                    MessageBox.Show("无此医生.请重新输入");
                    sql = "select num 编号,name 医生姓名,sex 性别,age 年龄,telephone 联系方式,keshihao 科室号 from yy_yisheng";
                }
                DataTable dt = s.GetDataTable(sql);
                dataGridView1.DataSource = dt;

                textBox6.Text = dataGridView1.SelectedRows[0].Cells[0].Value.ToString();

                s.Close();
            }
        }

        private void textBox6_Click(object sender, EventArgs e)
        {
            b = true;
        }
    }
}
