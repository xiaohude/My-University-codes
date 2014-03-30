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
    public partial class changsuotongji : Form
    {
        public changsuotongji()
        {
            InitializeComponent();
            tongjichangsuo();
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
        
        public void tongjichangsuo()
        {
            readData rd = new readData();
            string sql = "select xian as 县（市、区）,jb as 教别,count(jb) as 场所数 from changsuo group by xian,jb ";

            DataTable dt = rd.getDataString(sql);
            dataGridView1.DataSource = dt;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Application.Exit();//直接退出了整个程序
        }

        private void button1_Click(object sender, EventArgs e)
        {
            tongjichangsuo();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            readData rd = new readData();
            string sql = "select xian as 县（市、区）,count(xian) as 场所总数 from changsuo group by xian";

            DataTable dt = rd.getDataString(sql);
            dataGridView1.DataSource = dt;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            readData rd = new readData();
            string sql = "select xian as 县（市、区）,jb as 教别,count(jb) as 场所数 from changsuo group by xian,jb order by jb";

            DataTable dt = rd.getDataString(sql);
            dataGridView1.DataSource = dt;
        }

        private void changsuotongji_Load_1(object sender, EventArgs e)
        {

        }

        private void button5_Click(object sender, EventArgs e)
        {
            readData rd = new readData();
            string sql = "select jb as 教别,count(jb) as 场所总数 from changsuo group by jb";

            DataTable dt = rd.getDataString(sql);
            dataGridView1.DataSource = dt;
        }
    }
}
