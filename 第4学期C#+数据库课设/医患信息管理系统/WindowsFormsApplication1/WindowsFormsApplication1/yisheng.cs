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
    public partial class yisheng : Form
    {
        SqlConnect s = new SqlConnect();
        int num;
        string name;
        string sex;
        int age;
        string telephone;

        public yisheng(int i)
        {
            num = i;
            InitializeComponent();
            getxinxi();
        }
        void getxinxi()
        {
            s.Open();
            string sql = "select num,name,sex,age,telephone from yy_yisheng where num='" + num + "'";
            DataTable dt = s.GetDataTable(sql);

            textBox1.Text = dt.Rows[0][0].ToString();
            textBox2.Text = dt.Rows[0][1].ToString();
            comboBox1.Text = dt.Rows[0][2].ToString();
            textBox4.Text = dt.Rows[0][3].ToString();
            textBox5.Text = dt.Rows[0][4].ToString();

            textBox1.Enabled = false;//锁住信息不能更改
            textBox2.Enabled = false;
            comboBox1.Enabled = false;
            textBox4.Enabled = false;
            textBox5.Enabled = false;

            s.Close();
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
        void getmessage()//获取文本框上的信息
        {
            name = textBox2.Text;
            sex = comboBox1.Text;
            age = zhuanhuan(textBox4.Text);
            telephone = textBox5.Text;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //  textBox1.ReadOnly = false;//解锁信息能更改,但是不能更改编号.
            textBox2.Enabled = true;
            comboBox1.Enabled = true;
            textBox4.Enabled = true;
            textBox5.Enabled = true;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            s.Open();
            getmessage();
            string sql = "update yy_yisheng set name='" + name + "',sex='" + sex + "',age='" + age + "',telephone='" + telephone + "' where num='" + num + "'";
            int n = s.ExecuteNonQuery(sql);
            if (n == 0)
            {
                MessageBox.Show("修改失败！");
            }
            else
            {
                MessageBox.Show("修改成功！");
            }
            s.Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            kanhuanzhe khz =new kanhuanzhe(num);
            khz.ShowDialog();
        }

    }
}
