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
    public partial class denglu : Form
    {
        SqlConnect s = new SqlConnect();
        int num;//用来查询出登录者的编号,并当做参数传递下去
        string name = null;
        string password = null;
        int i = 1;//判断选中的是患者还是医生还是管理员。默认为患者。（1，2，3）

        public denglu()
        {
            InitializeComponent();
        }
        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            name = textBox1.Text;
        }
       
        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            password = textBox2.Text;
        }
        
        
        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            i = 1;//选中了患者（初始状态）
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            i = 2;//选中了医生
        }

        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
            i = 3;//选中了管理员
        }

        private void button1_Click(object sender, EventArgs e)
        {
            DengLu();
        }
        public void DengLu()
        {
            switch (i)
            {
                case 1:
                    {
                        s.Open();
                        string sql = "select * from yy_huanzhe where name='" + name + "' and password='" + password + "'";
                        DataTable dt = s.GetDataTable(sql);
                        
                        if (dt.Rows.Count == 0)
                        {
                            MessageBox.Show("登录失败");
                        }
                        else
                        {
                            num = int.Parse(dt.Rows[0][0].ToString());
                            MessageBox.Show("登录成功");
                            huanzhe hz = new huanzhe(num);
                            hz.ShowDialog();
                        }
                        s.Close();
                    }
                    break;
                case 2:
                    {
                        s.Open();
                        string sql = "select * from yy_yisheng where name='" + name + "' and password='" + password + "'";
                        DataTable dt = s.GetDataTable(sql);
                        
                        if (dt.Rows.Count == 0)
                        {
                            MessageBox.Show("登录失败");
                        }
                        else
                        {
                            num = int.Parse(dt.Rows[0][0].ToString());
                            MessageBox.Show("登录成功");
                            yisheng ys = new yisheng(num);
                            ys.ShowDialog();
                        }
                        s.Close();
                    }
                    break;
                case 3:
                    {
                        s.Open();
                        string sql = "select * from yy_admin where adminname='" + name + "' and password='" + password + "'";
                        if (s.GetDataTable(sql).Rows.Count == 0)
                        {
                            MessageBox.Show("登录失败");
                        }
                        else
                        {
                            MessageBox.Show("登录成功");
                               main m = new main();
                               m.ShowDialog();
                        }
                        s.Close();
                    }
                    break;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Application.Exit();//直接退出整个程序
        }


    }
}
