using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.OleDb;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using 学校管理系统.customerClass;

namespace zjgl
{
    public partial class jiaozhitongji : Form
    {
        public jiaozhitongji()
        {
            InitializeComponent();
            tongjijiaozhi();
        }

        public void tongjijiaozhi()
        {
            readData rd = new readData();
            string sql = "select xian as 县（市、区）,zj as 教别,count(zj) as 教职人员数 from jiaozhirenyuan group by xian,zj";

            DataTable dt = rd.getDataString(sql);
            dataGridView1.DataSource = dt;
        }
        private void button3_Click(object sender, EventArgs e)
        {
            Application.Exit();//直接退出了整个程序
        }

        private void button1_Click(object sender, EventArgs e)
        {
            tongjijiaozhi();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            readData rd = new readData();
            string sql = "select xian as 县（市、区）,zj as 教别,count(zj) as 教职人员数 from jiaozhirenyuan group by xian,zj order by zj";

            DataTable dt = rd.getDataString(sql);
            dataGridView1.DataSource = dt;
        }

        private void button2_Click(object sender, EventArgs e)
        { 
            readData rd = new readData();
            string sql = "select xian as 县（市、区）,count(xian) as 教职人员总数 from jiaozhirenyuan group by xian";

            DataTable dt = rd.getDataString(sql);
            dataGridView1.DataSource = dt;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            readData rd = new readData();
            string sql = "select zj as 教别,count(zj) as 教职人员总数 from jiaozhirenyuan group by zj";

            DataTable dt = rd.getDataString(sql);
            dataGridView1.DataSource = dt;
        }
    }
}
