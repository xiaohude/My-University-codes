
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;      //连接SQL数据库
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using MarketManage;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        SqlConnect s = new SqlConnect();
        string name = null;
        string password = null;
        public Form1()
        {
            InitializeComponent();
            this.BackgroundImage = Image.FromFile("D:/网页默认下载的/医院信息系统图片素材/yiliaobj_36b.jpg");
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

        private void button1_Click(object sender, EventArgs e)
        { 
            s.Open();
            string sql = "select * from yy_admin where adminname='"+name+"' and password='"+password+"'";
            if (s.GetDataTable(sql).Rows.Count == 0)
            {
                MessageBox.Show("登录失败");
            }
            else
            {
                MessageBox.Show("登录成功");
             //   main m = new main();
            }
            s.Close();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            name=textBox1.Text;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            s.Close();
            Application.Exit();//直接退出整个程序
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            password = textBox2.Text;
        }
    }
}
