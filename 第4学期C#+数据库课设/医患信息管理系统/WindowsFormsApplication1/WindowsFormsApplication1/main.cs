using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using MarketManage;
using System.Data.SqlClient;      //连接SQL数据库

namespace WindowsFormsApplication1
{
    public partial class main : Form
    {
        SqlConnect s = new SqlConnect();
        public main()
        {
            InitializeComponent();
    //        this.BackgroundImage = Image.FromFile("D:/网页默认下载的/医院信息系统图片素材/65.jpg");
            s.Open();
            string sql = "select num 编号,name 患者姓名,sex 性别,age 年龄,telephone 联系方式,guahao 挂号,keshihao 科室号 from yy_huanzhe";
            DataTable dt = s.GetDataTable(sql);
            dataGridView1.DataSource = dt;
            s.Close();
        }

        private void 病人信息ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            s.Open();
            string sql = "select num 编号,name 患者姓名,sex 性别,age 年龄,telephone 联系方式,guahao 挂号,keshihao 科室号 from yy_huanzhe";
            DataTable dt = s.GetDataTable(sql);
            dataGridView1.DataSource = dt;
            s.Close();
        }

        private void 药品信息ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            s.Open();
            string sql = "select num 编号,name 药品名,price 价格,changshang 生产厂商,youxiaoqi 有效期,kucunshu 库存数,zhuzhi 主治功能 from yy_yaopin";
            DataTable dt = s.GetDataTable(sql);
            dataGridView1.DataSource = dt;
            s.Close();
        }

        private void 医生信息ToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            s.Open();
            string sql = "select num 编号,name 医生姓名,sex 性别,age 年龄,telephone 联系方式,keshihao 科室号 from yy_yisheng";
            DataTable dt = s.GetDataTable(sql);
            dataGridView1.DataSource = dt;
            s.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            guanlihuanzhe glhuanzhe = new guanlihuanzhe();
            glhuanzhe.ShowDialog();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            guanliyisheng glyisheng = new guanliyisheng();
            glyisheng.ShowDialog();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            guanliyaopin glyaopin = new guanliyaopin();
            glyaopin.ShowDialog();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            quyao quyao = new quyao();
            quyao.ShowDialog();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            yihuan yihuan = new yihuan();
            yihuan.ShowDialog();
        }

        private void 管理患者信息ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            guanlihuanzhe glhuanzhe = new guanlihuanzhe();
            glhuanzhe.ShowDialog();
        }

        private void 管理医生信息ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            guanliyisheng glyisheng = new guanliyisheng();
            glyisheng.ShowDialog();
        }

        private void 管理药品信息ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            guanliyaopin glyaopin = new guanliyaopin();
            glyaopin.ShowDialog();
        }

        private void 管理患者取药信息ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            quyao quyao = new quyao();
            quyao.ShowDialog();
        }

        private void 管理医患关系信息ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            yihuan yihuan = new yihuan();
            yihuan.ShowDialog();
        }

        private void 患者取药信息ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            s.Open();
            string sql = "select 患者编号,患者姓名,药品编号,药品名称, 取药数量, 药品单价,取药时间 from yy_quyaoview";
            DataTable dt = s.GetDataTable(sql);
            dataGridView1.DataSource = dt;
            s.Close();
        }

        private void 医患关系信息ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            s.Open();
            string sql = "select 患者编号,患者姓名,医生编号,医生姓名,看病时间 from yy_yihuanview";
            DataTable dt = s.GetDataTable(sql);
            dataGridView1.DataSource = dt;
            s.Close();
        }
    }
}
