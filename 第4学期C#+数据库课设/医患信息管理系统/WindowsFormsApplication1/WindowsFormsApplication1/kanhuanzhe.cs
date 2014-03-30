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
    public partial class kanhuanzhe : Form
    {
        SqlConnect s = new SqlConnect();
        public kanhuanzhe(int i)
        {
            InitializeComponent();
            gethuanzhe(i);
        }
        public void gethuanzhe(int i)//显示和自己有约的患者信息
        {
            s.Open();
            string sql = "select num 编号,name 患者姓名,sex 性别,age 年龄,telephone 联系方式,guahao 挂号,keshihao 科室号,time 预约时间 from yy_huanzhe,yy_yihuanguanxi where huanzhenum=num and yishengnum='"+i+"'";
            DataTable dt = s.GetDataTable(sql);
            dataGridView1.DataSource = dt;
            s.Close();
        }
    }
}
