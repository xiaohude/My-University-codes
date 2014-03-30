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
    public partial class guanliyaopin : Form
    {
        SqlConnect s = new SqlConnect();
        int i = 0;//用来记录查找出来的表中共有多少条信息
        int b = 0;//用来标记是否信息是修改的或者新建的.新建的为1.修改的为2
        int num;
        string name;
        float price;
        string changshang;
        DateTime  youxiaoqi;
        int kucunshu;
        string zhuzhi;

        int yuanshinum;//用来记录修改前的num.num不能修改.

        public guanliyaopin()
        {
            InitializeComponent();
            getyaopin();
        }
        void getyaopin()  //显示全部药品信息
        {
            s.Open();
            string sql = "select num 编号,name 药品名称,price 价格,changshang 生产厂商,youxiaoqi 有效期,kucunshu 库存数,zhuzhi 主治功能 from yy_yaopin";
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
            textBox3.Text = dataGridView1.SelectedRows[0].Cells[2].Value.ToString();
            textBox4.Text = dataGridView1.SelectedRows[0].Cells[3].Value.ToString();
            dateTimePicker1.Text = dataGridView1.SelectedRows[0].Cells[4].Value.ToString();
            textBox6.Text = dataGridView1.SelectedRows[0].Cells[5].Value.ToString();
            textBox7.Text = dataGridView1.SelectedRows[0].Cells[6].Value.ToString();

            yuanshinum = zhuanhuan(textBox1.Text);//保存一下更改之前的num值
        }
        public void chongzhi()//重置所有信息
        {
            textBox1.Text = null;
            textBox2.Text = null;
            textBox3.Text = null;
            textBox4.Text = null;
            dateTimePicker1.Text = null;
            textBox6.Text = null;
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
        DateTime datetimenow=DateTime.Now;//获取现在的时间;当时间的默认值.也用来判断时间是否被修改过.是在查询的时候用的.
        DateTime zhuanhuanriqi(string s)//将字符串转换为datetime类型;
        {
            DateTime d;
            if (s == "")
                 d = datetimenow;
               //  d = DateTime.Now;
            else
                d = DateTime.Parse(s); //将字符串转换datetime类型
            return d;
        }
        void getmassage()//获取文本框上的信息
        {
            num = zhuanhuan(textBox1.Text);
            name = textBox2.Text;
            price = zhuanhuan(textBox3.Text);
            changshang = textBox4.Text;
            youxiaoqi = zhuanhuanriqi(dateTimePicker1.Text);
            kucunshu  = zhuanhuan(textBox6.Text);
            zhuzhi = textBox7.Text;
        }
        public void baocun()
        {

            getmassage();
            s.Open();
            string chazhao = "select num from yy_yaopin where num='" + num + "'";
            if (s.GetDataTable(chazhao).Rows.Count == 0)
            {
                string sql = "insert into yy_yaopin(num,name,price,changshang,youxiaoqi,kucunshu,zhuzhi,password) values('" + num + "','" + name + "','" + price + "','" + changshang + "','" + youxiaoqi + "','" + kucunshu  + "','" + zhuzhi + "','1')";//密码默认为1
                int n = s.ExecuteNonQuery(sql);
                if (n <=0)
                {
                    MessageBox.Show("保存失败！");
                }
                else
                {
                    MessageBox.Show("保存成功！");
                    sql = "select num 编号,name 药品名称,price 价格,changshang 生产厂商,youxiaoqi 有效期,kucunshu 库存数,zhuzhi 主治功能 from yy_yaopin";
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
            s.Open();
            string sql = "select num 编号,name 药品名称,price 价格,changshang 生产厂商,youxiaoqi 有效期,kucunshu 库存数,zhuzhi 主治功能 from yy_yaopin where password='1' ";//编写sql语句,通过一些if语句来实现输入信息越多,查询范围越少

            string snum = "and num='" + num + "' ";
            string sname = "and name='" + name + "' ";
            string sprice = "and price='" + price + "' ";
            string schangshang = "and changshang='" + changshang + "' ";
            string syouxiaoqi = "and youxiaoqi='" + youxiaoqi + "' ";
            string skucunshu = "and kucunshu='" + kucunshu + "' ";
            string szhuzhi = "and zhuzhi='" + zhuzhi + "' ";
            if (num != 0)
                sql = sql + snum;
            if (name != "")
                sql = sql + sname;
            if (price != 0)
                sql = sql + sprice;
            if (changshang != "")
                sql = sql + schangshang;
            if (youxiaoqi != datetimenow)
                sql = sql + syouxiaoqi;
            if (kucunshu != 0)
                sql = sql + skucunshu;
            if (zhuzhi != "")
                sql = sql + szhuzhi;
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

        
        private void button4_Click(object sender, EventArgs e)//保存按钮
        {
            if (b == 1)
                baocun();
            if (b == 2)
                xiugai();
        }

        private void button1_Click(object sender, EventArgs e)//查询按钮
        {
            b = 0;
            yuanshinum = zhuanhuan(textBox1.Text);//保存一下更改之前的num值,防止修改时时乱改num
            datetimenow = zhuanhuanriqi(dateTimePicker1.Text);
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
                string sql = "update yy_yaopin set name='" + name + "',price='" + price + "',changshang='" + changshang + "',youxiaoqi='" + youxiaoqi + "',kucunshu='" + kucunshu + "',zhuzhi='" + zhuzhi + "' where num='" + num + "'";
                int n = s.ExecuteNonQuery(sql);
                if (n == 0)
                {
                    MessageBox.Show("修改失败！");
                }
                else
                {
                    MessageBox.Show("修改成功！");
                    sql = "select num 编号,name 药品名称,price 价格,changshang 生产厂商,youxiaoqi 有效期,kucunshu 库存数,zhuzhi 主治功能 from yy_yaopin where num='" + num + "'";
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

        private void button2_Click(object sender, EventArgs e)//修改按钮
        {
            b = 2;
        }

        private void button3_Click(object sender, EventArgs e)//删除按钮
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
                    string sql = "delete from yy_yaopin  where num='" + num + "'";
                    int n = s.ExecuteNonQuery(sql);
                    if (n == 0)
                    {
                        MessageBox.Show("删除失败！");
                    }
                    else
                    {
                        MessageBox.Show("删除成功！");
                        getyaopin();
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

        private void button5_Click(object sender, EventArgs e)//新建按钮
        {
            b = 1;
            chongzhi();
        }

        private void button7_Click(object sender, EventArgs e)
        {
            this.Close();
        }

    }
}
