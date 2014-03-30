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
    public partial class quyao : Form
    {
        SqlConnect s = new SqlConnect();
        int i = 0;//用来记录查找出来的表中共有多少条信息
        int b = 0;//用来标记是否信息是修改的或者新建的.新建的为1.修改的为2
        int hznum;
        int ypnum;
        string hzname;
        string ypname;
        int shuliang;
        float price;
        DateTime time;
        bool bool1 = false;//用来记录时间是否被改变过....这时才会加上查询时间的sqlyuju
        int c = 0;//用来区别信息表中显示的是医患关系(0),患者信息(1).药品信息(2);来定义不同的信息表下鼠标点击时,不同的获取信息方式


        public quyao()
        {
            InitializeComponent();
            getquyao();
            s.Open();
        }
        //这里创建删除视图的时候,多重复几次会出现 ConnectionString 属性尚未初始化 的问题.所以最后觉得,视图直接事先创建好.那样也方便查询.
    /*    void creatview() //创建取药的视图
        {
     //       s.Open();
            string sql = "create view yy_quyaoview as select yy_huanzhe.num 患者编号,yy_huanzhe.name 患者姓名,yy_yaopin.num 药品编号,yy_yaopin.name 药品名称,shuliang 取药数量,price 药品单价,time 取药时间,yy_huanzhe.password password from yy_yaopin,yy_huanzhe,yy_huanzhequyao where yy_yaopin.num=yaopinnum and yy_huanzhe.num=huanzhenum";
            s.ExecuteNonQuery(sql);                   
     //       s.Close();
        }
        void dropview()//删除视图
        {
     //       s.Open();     
            string sql = "drop view yy_quyaoview";
            s.ExecuteNonQuery(sql);          
     //       s.Close();
        }
  * */
        void getquyao()  //显示全部取药信息
        {
     //       s.Open();
      //      creatview();
            //显示视图
            string sql = "select 患者编号,患者姓名,药品编号,药品名称, 取药数量, 药品单价,取药时间 from yy_quyaoview";
            DataTable dt = s.GetDataTable(sql);
            dataGridView1.DataSource = dt;
            i = dt.Rows.Count;
       //     s.Close();

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
                textBox3.Text = dataGridView1.SelectedRows[0].Cells[4].Value.ToString();
                textBox4.Text = dataGridView1.SelectedRows[0].Cells[5].Value.ToString();
                dateTimePicker1.Text = dataGridView1.SelectedRows[0].Cells[6].Value.ToString();
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
                textBox4.Text = dataGridView1.SelectedRows[0].Cells[2].Value.ToString();
                c = 0;
            }
        }
        public void chongzhi()//重置所有信息
        {
            bool1 = false;
            textBox1.Text = null;
            textBox2.Text = null;
            textBox3.Text = null;
            textBox4.Text = null;
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
        DateTime datetimenow = DateTime.Now;//获取现在的时间;当时间的默认值.也用来判断时间是否被修改过.是在查询的时候用的.
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
            hznum = zhuanhuan(textBox5.Text);
            ypnum = zhuanhuan(textBox6.Text); 
            hzname = textBox1.Text;
            ypname = textBox2.Text;
            shuliang = zhuanhuan(textBox3.Text);
            price = zhuanhuan(textBox4.Text);
            time = zhuanhuanriqi(dateTimePicker1.Text);
        }
        public void baocun()
        {

            getmassage();
     //       s.Open();        
                string sql = "insert into yy_huanzhequyao(huanzhenum,yaopinnum,shuliang,time) values('" + hznum + "','" + ypnum + "','" + shuliang + "','" + time + "')"+"update yy_yaopin set kucunshu = kucunshu -'" + shuliang + "' where num='"+ypnum+"'";
                int n = s.ExecuteNonQuery(sql);
                if (n <= 0)
                {
                    MessageBox.Show("保存失败！");
                }
                else
                {
                    MessageBox.Show("保存成功！");
                    sql = "select 患者编号,患者姓名,药品编号,药品名称,取药数量,药品单价,取药时间 from yy_quyaoview";
                    DataTable dt = s.GetDataTable(sql);
                    dataGridView1.DataSource = dt;
                }
            
    //        s.Close();
        }
        void chaxun()//查询函数
        {
            getmassage();
      //      s.Open();
            string sql = "select 患者编号,患者姓名,药品编号,药品名称,取药数量,药品单价,取药时间 from yy_quyaoview where password='1' ";//编写sql语句,通过一些if语句来实现输入信息越多,查询范围越少

            string shznum = "and 患者编号='" + hznum + "' ";
            string sypnum = "and 药品编号='" + ypnum + "' ";
            string shzname = "and 患者姓名='" + hzname + "' ";
            string sypname = "and 药品名称='" + ypname + "' ";
            string sprice = "and 药品单价='" + price + "' ";
            string sshuliang = "and 取药数量='" + shuliang + "' ";
            string stime = "and 取药时间='" + time + "' ";
            if (hznum != 0)
                sql = sql + shznum;
            if (ypnum != 0)
                sql = sql + sypnum;
            if (hzname != "")
                sql = sql + shzname;
            if (ypname != "")
                sql = sql + sypname;
            if (shuliang != 0)
                sql = sql + sshuliang;
            if (price != 0)
                sql = sql + sprice;        
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
      //      s.Close();
        }

        private void button4_Click(object sender, EventArgs e)//保存按钮
        {
            if(b==1)
                baocun();
            b = 0;
        }

        private void button1_Click(object sender, EventArgs e)//查询按钮
        {
        //    datetimenow = zhuanhuanriqi(dateTimePicker1.Text);
            b = 0;
            chaxun();
        }

        private void button6_Click(object sender, EventArgs e)//重置按钮
        {
            chongzhi();
        }
       /* void xiugai()           //修改函数
        {
            getmassage();
            s.Open();
                string sql = "update yy_huanzhequyao set huanzhenum='" + hznum + "',yaopinnum='" + ypnum + "',shuliang='" + shuliang + "',time='" + time + "' where huanzhenum='" + hznum + "' and yaopinnum='" + ypnum + "'";
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
            s.Close();

        }*/
        void shanchu()        //删除函数
        {
            getmassage();
       //     s.Open();
                queren q = new queren();//弹出确认窗口.并判断
                q.ShowDialog();
                if (q.b)
                {
                    string sql = "delete from yy_huanzhequyao  where huanzhenum='" + hznum + "' and yaopinnum='" + ypnum + "'";
                    int n = s.ExecuteNonQuery(sql);
                    if (n == 0)
                    {
                        MessageBox.Show("删除失败！");
                    }
                    else
                    {
                        MessageBox.Show("删除成功！");
                        getquyao();
                    }
                }
           
     //       s.Close();
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
            textBox3.Text = "1";//默认数量为1;
            label4.Text = "药品总价:";//新建时药品单价变成药品总价,并在改变数量值的时候,计算出总价
            textBox4.Enabled = false;//新建时价格文本框不能输入
        }

        private void textBox5_TextChanged(object sender, EventArgs e)//新建时,点击患者编号文本框的时候,显此药品信息.并把相应信息放到相应文本框中
        {
            if (textBox5.Text != ""&&b==1)//在文本框值不是空的时候,并且是点击新建按钮之后才调用此函数
            {
                c = 1;
                hznum = zhuanhuan(textBox5.Text);
       //         s.Open();
                //显示此患者编号的信息
                string sql = "select num 编号,name 患者姓名,sex 性别,age 年龄,telephone 联系方式,guahao 挂号,keshihao 科室号 from yy_huanzhe where num='" + hznum + "'";
                if (s.GetDataTable(sql).Rows.Count == 0)
                {
                    MessageBox.Show("无此患者编号.请重新输入");
                    sql = "select num 编号,name 患者姓名,sex 性别,age 年龄,telephone 联系方式,guahao 挂号,keshihao 科室号 from yy_huanzhe";
                }
                DataTable dt = s.GetDataTable(sql);
                dataGridView1.DataSource = dt;

                textBox1.Text = dataGridView1.SelectedRows[0].Cells[1].Value.ToString();

        //        s.Close();
            }
        }
/*
        private void textBox1_TextChanged(object sender, EventArgs e)//点击更改患者姓名文本框时触发的操作.显示患者信息到相应文本框上
        {
            if (textBox1.Text != "" && b == 1)//在文本框值不是空的时候,并且是点击新建按钮之后才调用此函数
            {
                c = 1;
                hzname = textBox1.Text;
                //         s.Open();
                //显示此患者编号的信息
                string sql = "select num 编号,name 患者姓名,sex 性别,age 年龄,telephone 联系方式,guahao 挂号,keshihao 科室号 from yy_huanzhe where name='" + hzname + "'";
                if (s.GetDataTable(sql).Rows.Count == 0)
                {
                    MessageBox.Show("无此患者姓名.请重新输入");
                    sql = "select num 编号,name 患者姓名,sex 性别,age 年龄,telephone 联系方式,guahao 挂号,keshihao 科室号 from yy_huanzhe";
                }
                DataTable dt = s.GetDataTable(sql);
                dataGridView1.DataSource = dt;

                textBox5.Text = dataGridView1.SelectedRows[0].Cells[0].Value.ToString();

                //        s.Close();
            }

        }
*/
        private void textBox6_TextChanged(object sender, EventArgs e)//新建时.点击药品编号文本框的时候,显此药品信息.并把相应信息放到相应文本框中
        {
            if (textBox6.Text != ""&&b==1)
            {
                c = 2;
                ypnum = zhuanhuan(textBox6.Text);
      //          s.Open();
                //显示此药品编号的信息
                string sql = "select num 编号,name 药品名称,price 药品单价,changshang 生产厂商,youxiaoqi 有效期,kucunshu 库存数,zhuzhi 主治功能 from yy_yaopin where num='" + ypnum + "'";
                if (s.GetDataTable(sql).Rows.Count == 0) //当输入的编号,在数据库中没有的时候出现警告提示.
                {
                    MessageBox.Show("无此药品编号.请重新输入");
                    sql = "select num 编号,name 药品名称,price 药品单价,changshang 生产厂商,youxiaoqi 有效期,kucunshu 库存数,zhuzhi 主治功能 from yy_yaopin";
                }
                DataTable dt = s.GetDataTable(sql);
                dataGridView1.DataSource = dt;

                textBox2.Text = dataGridView1.SelectedRows[0].Cells[1].Value.ToString();
               // textBox3.Text = dataGridView1.SelectedRows[0].Cells[5].Value.ToString();
                textBox4.Text = dataGridView1.SelectedRows[0].Cells[2].Value.ToString();

       //         s.Close();
            }
        }
/*
        private void textBox2_TextChanged(object sender, EventArgs e)//点击更改药品名称时触发的操作
        {
            if (textBox2.Text != "" && b == 1)
            {
                c = 2;
                ypname = textBox2.Text;
                //          s.Open();
                //显示此药品的信息
                string sql = "select num 编号,name 药品名称,price 药品单价,changshang 生产厂商,youxiaoqi 有效期,kucunshu 库存数,zhuzhi 主治功能 from yy_yaopin where name='" + ypname + "'";
                if (s.GetDataTable(sql).Rows.Count == 0) //当输入的编号,在数据库中没有的时候出现警告提示.
                {
                    MessageBox.Show("无此药品编号.请重新输入");
                    sql = "select num 编号,name 药品名称,price 药品单价,changshang 生产厂商,youxiaoqi 有效期,kucunshu 库存数,zhuzhi 主治功能 from yy_yaopin";
                }
                DataTable dt = s.GetDataTable(sql);
                dataGridView1.DataSource = dt;

                textBox6.Text = dataGridView1.SelectedRows[0].Cells[0].Value.ToString();
                // textBox3.Text = dataGridView1.SelectedRows[0].Cells[5].Value.ToString();
                textBox4.Text = dataGridView1.SelectedRows[0].Cells[2].Value.ToString();

                //         s.Close();
            }

        }
*/
        private void textBox3_TextChanged(object sender, EventArgs e)//点击取药数量的时候,出发的函数.应该判断输入的数量应小于此药品的库存数.
        {
            if (textBox3.Text != "" && b == 1 && textBox6.Text != "")
            {
                ypnum = zhuanhuan(textBox6.Text);
                shuliang = zhuanhuan(textBox3.Text);
       //         s.Open();
                //显示此药品编号的信息
                string sql = "select num 编号,name 药品名称,price 药品单价,changshang 生产厂商,youxiaoqi 有效期,kucunshu 库存数,zhuzhi 主治功能 from yy_yaopin where num='" + ypnum + "'";
                DataTable dt = s.GetDataTable(sql);
                dataGridView1.DataSource = dt;

                if (shuliang > zhuanhuan(dataGridView1.SelectedRows[0].Cells[5].Value.ToString()))//如果输入数量大于药品总数
                {
                    MessageBox.Show("库存数不足所取数目,请重新输入.");
                    textBox3.Text = "1";
                }
         //       s.Close();

                //计算药品总价

                price = zhuanhuan(dt.Rows[0][2].ToString());
                price = price * shuliang;
                textBox4.Text = price.ToString();
            }
        }
        private void dateTimePicker1_ValueChanged(object sender, EventArgs e)
        {
            bool1 = true;//用来记录时间被改变过....这时才会加上查询时间的sqlyuju
        }

        private void button7_Click(object sender, EventArgs e)//返回按钮
        {
            s.Close();
            this.Close();
        }

        private void textBox1_Leave(object sender, EventArgs e)//输入完患者姓名,离开时出发的操作.
        {
            if (textBox1.Text != "" && b == 1)//在文本框值不是空的时候,并且是点击新建按钮之后才调用此函数
            {
                c = 1;
                hzname = textBox1.Text;
                //         s.Open();
                //显示此患者的信息
                string sql = "select num 编号,name 患者姓名,sex 性别,age 年龄,telephone 联系方式,guahao 挂号,keshihao 科室号 from yy_huanzhe where name='" + hzname + "'";
                if (s.GetDataTable(sql).Rows.Count == 0)
                {
                    MessageBox.Show("无此患者姓名.请重新输入");
                    sql = "select num 编号,name 患者姓名,sex 性别,age 年龄,telephone 联系方式,guahao 挂号,keshihao 科室号 from yy_huanzhe";
                }
                DataTable dt = s.GetDataTable(sql);
                dataGridView1.DataSource = dt;

                textBox5.Text = dataGridView1.SelectedRows[0].Cells[0].Value.ToString();

                //        s.Close();
            }
        }

        private void textBox2_Leave(object sender, EventArgs e)//输入完药品名称,离开时触发的操作
        {
            if (textBox2.Text != "" && b == 1)
            {
                c = 2;
                ypname = textBox2.Text;
                //          s.Open();
                //显示此药品的信息
                string sql = "select num 编号,name 药品名称,price 药品单价,changshang 生产厂商,youxiaoqi 有效期,kucunshu 库存数,zhuzhi 主治功能 from yy_yaopin where name='" + ypname + "'";
                if (s.GetDataTable(sql).Rows.Count == 0) //当输入的编号,在数据库中没有的时候出现警告提示.
                {
                    MessageBox.Show("无此药品.请重新输入");
                    sql = "select num 编号,name 药品名称,price 药品单价,changshang 生产厂商,youxiaoqi 有效期,kucunshu 库存数,zhuzhi 主治功能 from yy_yaopin";
                }
                DataTable dt = s.GetDataTable(sql);
                dataGridView1.DataSource = dt;

                textBox6.Text = dataGridView1.SelectedRows[0].Cells[0].Value.ToString();
                // textBox3.Text = dataGridView1.SelectedRows[0].Cells[5].Value.ToString();
                textBox4.Text = dataGridView1.SelectedRows[0].Cells[2].Value.ToString();

                //         s.Close();
            }

        }

        

        

       
    }
}
//在编程中不断的出现问题,不断的一步步解决问题,从中收获了好多解决问题的方法.