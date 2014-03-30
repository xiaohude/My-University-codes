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
    public partial class qunzhongtongji : Form
    {
        public qunzhongtongji()
        {
            InitializeComponent();
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            readData rd = new readData();
            string sql = "select xianname as 县（市、区）,sum(xjrs) as 信教总人数 from xzxian,jujucun where xzxian.xianname=jujucun.xian group by xianname";

            DataTable dt = rd.getDataString(sql);
            dataGridView1.DataSource = dt;
        }

        private void qunzhongtongji_Load(object sender, EventArgs e)
        {
            tongjiqunzhong();
        }
        public void tongjiqunzhong()
        {
            readData rd = new readData();
            string sql = "select xianname as 县（市、区）,jb as 教别,xjrs as 信教人数 from xzxian,jujucun where xzxian.xianname=jujucun.xian";
            
            DataTable dt = rd.getDataString(sql);
            dataGridView1.DataSource = dt;
           // dataGridView1.Columns["csid"].Visible = false;//隐藏不显示csid

        }

        private void button3_Click(object sender, EventArgs e)
        {
            tongjiqunzhong();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Application.Exit();//直接退出了整个程序
        }

        private void button4_Click(object sender, EventArgs e)
        {
            readData rd = new readData();
            string sql = "select xian as 县（市、区）,jb as 教别,xjrs as 信教人数 from jujucun order by jb";

            DataTable dt = rd.getDataString(sql);
            dataGridView1.DataSource = dt;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            readData rd = new readData();
            string sql = "select jb as 教别,sum(xjrs) as 信教总人数 from jujucun  group by jb";

            DataTable dt = rd.getDataString(sql);
            dataGridView1.DataSource = dt;
        }
    }
}
