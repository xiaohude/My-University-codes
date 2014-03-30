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
    public partial class FrmAddress : Form
    {
        bool infoState = true; //资料完整状态
        public FrmAddress()
        {
            InitializeComponent();
        }

        private void FrmAddress_Load(object sender, EventArgs e)
        {
            //加载 县（市、区）数据
            Getzongjiao();
            GetXian();
            Getchangsuo();
        }
        public void Getchangsuo()
        {
            readData rd = new readData();
            string sql = "select xian as 县（市、区）,xiang as 乡镇,cun as 村（街）,csmc as 场所名称,jb as 教别,jzryxm as 教职人员姓名,cgfzr as 村管小组负责人,czbsj as 村支部书记,csdh as 场所电话,csid from changsuo";
            DataTable dt = rd.getDataString(sql);
            dgvAddress.DataSource = dt;
            dgvAddress.Columns["csid"].Visible = false;

        }
        //教别信息
        private void Getzongjiao()
        {
            OleDbConnection zjConn = new dataInterFace().getODConn();
            OleDbDataAdapter zjAda = new OleDbDataAdapter("select zongjiao from zongjiao", zjConn);

            DataTable dtt = new DataTable();
            zjAda.Fill(dtt);

            DataRow dr = dtt.NewRow(); //index=0处加入一个"--请选择--"
            dr["zongjiao"] = "--请选择--";
            dtt.Rows.InsertAt(dr, 0);

            cbjb.DataSource = dtt;
            cbjb.DisplayMember = "zongjiao";

            zjAda.Dispose();
            zjConn.Dispose();
            zjConn.Close();
            cbjb.Text = "---请选择---";
        }
        /// <summary>
        /// 获取县（市、区）
        /// </summary>
        private void GetXian()
        {
            OleDbConnection xConn = new dataInterFace().getODConn();
            OleDbDataAdapter xAda = new OleDbDataAdapter("select * from xzxian", xConn);

            DataTable dtxian = new DataTable();
            xAda.Fill(dtxian);

            DataRow dr = dtxian.NewRow(); //index=0处加入一个"--请选择--"
            dr["xianname"] = "--请选择--";
            dr["xiancode"] = "-1";
            dtxian.Rows.InsertAt(dr, 0);

            cbxian.DataSource = dtxian;
            cbxian.DisplayMember = "xianname";
            cbxian.ValueMember = "xiancode";

            xAda.Dispose();
            xConn.Dispose();
            xConn.Close();
        }
        /// <summary>
        /// 获取镇 乡 街道
        /// </summary>
        private void GetXian(int xiancode)
        {
           
            OleDbConnection xConn = new dataInterFace().getODConn();
            string strSql = "select * from xzxiangzhen where xiancode=" + xiancode;
            OleDbDataAdapter xAda = new OleDbDataAdapter(strSql, xConn);

            DataTable dtxiang = new DataTable();
            xAda.Fill(dtxiang);

            DataRow dr = dtxiang.NewRow(); //index=0处加入一个"--请选择--"
            dr["xzname"] = "--请选择--";
            dr["xzcode"] = "-1";
            dtxiang.Rows.InsertAt(dr, 0);

            cbxiang.DataSource = dtxiang;
            cbxiang.DisplayMember = "xzname";
            cbxiang.ValueMember = "xzcode";

            xAda.Dispose();
            xConn.Dispose();
            xConn.Close();
        }
        /// <summary>
        /// 获取 村
        /// </summary>
        private void GetCun(int xzcode)
        {

            OleDbConnection xConn = new dataInterFace().getODConn();
            string strSql = "select * from xzcun where xzcode=" + xzcode;
            OleDbDataAdapter xAda = new OleDbDataAdapter(strSql, xConn);

            DataTable dtcun = new DataTable();
            xAda.Fill(dtcun);

            DataRow dr = dtcun.NewRow(); //index=0处加入一个"--请选择--"
            dr["cunname"] = "--请选择或输入--";
            dr["cunid"] = "-1";
            dtcun.Rows.InsertAt(dr, 0);

            cbCun.DataSource = dtcun;
            cbCun.DisplayMember = "cunname";
            cbCun.ValueMember = "cunid";

            xAda.Dispose();
            xConn.Dispose();
            xConn.Close();
        }
        private void cbxian_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cbxian.SelectedIndex > 0)
            {
                int xiancode = Convert.ToInt32(cbxian.SelectedValue);
                GetXian(xiancode);
            }
        }
        /// <summary>
        /// 根据乡镇 获取村 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cbxiang_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cbxiang.SelectedIndex > 0)
            {
                int xzcode = Convert.ToInt32(cbxiang.SelectedValue);
                GetCun(xzcode);
            }
        }
        /// <summary>
        /// 单击某一行时将信息放到详细
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void dgvAddress_CellMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            //clearComBoBox();

            string xian = dgvAddress.SelectedRows[0].Cells[0].Value.ToString();
            for (int i = 0; i < cbxian.Items.Count; i++)
            {
                cbxian.SelectedIndex = i;
                string comboBoxText1 = cbxian.Text.Substring(cbxian.Text.LastIndexOf(":") + 1);
                if (xian.Equals(comboBoxText1))
                {
                    break;
                }
                else
                {
                    cbxian.SelectedIndex = -1;
                }
            }

            string xiang = dgvAddress.SelectedRows[0].Cells[1].Value.ToString();
            for (int i = 0; i < cbxiang.Items.Count; i++)
            {
                cbxiang.SelectedIndex = i;
                string comboBoxText1 = cbxiang.Text.Substring(cbxiang.Text.LastIndexOf(":") + 1);
                if (xiang.Equals(comboBoxText1))
                {
                    break;
                }
                else
                {
                    cbxiang.SelectedIndex = -1;
                }
            }

            string cun = dgvAddress.SelectedRows[0].Cells[2].Value.ToString();
            for (int i = 0; i < cbCun.Items.Count; i++)
            {
                cbCun.SelectedIndex = i;
                string comboBoxText1 = cbCun.Text.Substring(cbCun.Text.LastIndexOf(":") + 1);
                if (cun.Equals(comboBoxText1))
                {
                    break;
                }
                else
                {
                    cbCun.SelectedIndex = -1;
                }
            }

            tbcsmc.Text = dgvAddress.SelectedRows[0].Cells[3].Value.ToString();

            string jb = dgvAddress.SelectedRows[0].Cells[4].Value.ToString();
            for (int i = 0; i < cbjb.Items.Count; i++)
            {
                cbjb.SelectedIndex = i;
                string comboBoxText1 = cbjb.Text.Substring(cbjb.Text.LastIndexOf(":") + 1);
                if (jb.Equals(comboBoxText1))
                {
                    break;
                }
                else
                {
                    cbjb.SelectedIndex = -1;
                }
            }

            tbjzryxm.Text = dgvAddress.SelectedRows[0].Cells[5].Value.ToString();
            tbczbsj.Text = dgvAddress.SelectedRows[0].Cells[6].Value.ToString();
            tbcsdh.Text = dgvAddress.SelectedRows[0].Cells[7].Value.ToString();
            tbcgfzr.Text = dgvAddress.SelectedRows[0].Cells[8].Value.ToString();

            lflag.Text = dgvAddress.SelectedRows[0].Cells[9].Value.ToString();
        }
        /// <summary>
        /// 重置
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnReset_Click(object sender, EventArgs e)
        {
            clearChangsuoInfo();
        }
        //清空资料
        private void clearChangsuoInfo()
        {
            lflag.Text = "";
            cbxian.SelectedIndex = 0;
            cbxiang.SelectedIndex = -1;
            cbCun.SelectedIndex = -1;
            cbCun.Text = "";
            tbcsmc.Text = "";
            cbjb.SelectedIndex = 0;
            tbjzryxm.Text = "";
            tbczbsj.Text = "";
            tbcsdh.Text = "";
            tbcgfzr.Text = "";
        }

        /// <summary>
        /// 保存
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnSave_Click(object sender, EventArgs e)
        {
            if (lflag.Text == "")
            {
                AddInfo();          //添加资料
            }
            else
            {
                ModifyInfo();       //修改资料
            }
        }
        /// <summary>
        /// 添加
        /// </summary>
        private void AddInfo()
        {
            JudgementInfo();    //判断资料

            if (infoState)
            {
                //首先判断村 是选择的 还是新录入的，如果是新录入，则插入 村 表 一条数据
                string strCun = cbCun.Text;
                string strSelect = "select * from xzcun where cunname='" + strCun + "' and xzcode=" + cbxiang.SelectedValue;
                readData rd = new readData();
                DataTable dt = rd.getDataString(strSelect);

                if (dt == null || dt.Rows.Count==0)
                { 
                    //插入村表一条村记录
                    string strInsertCun="insert into xzcun(xzcode,cunname) values ("+cbxiang.SelectedValue+",'"+cbCun.Text+"')";
                    insertData icun = new insertData(strInsertCun);
                    if (!icun.insertDataState())
                    {
                        MessageBox.Show("保存失败!");
                        return;
                    }
                }


                string sql = "insert into changsuo(csmc,jzryxm,czbsj,csdh,cgfzr,jb,xian,xiang,cun) values ('"+tbcsmc.Text.Trim()+
                    "','"+tbjzryxm.Text.Trim()+"','"+tbczbsj.Text.Trim()+"','"+tbcsdh.Text.Trim()+"','"+tbcgfzr.Text.Trim()+
                    "','"+cbjb.Text+"','"+cbxian.Text+"','"+cbxiang.Text.Trim()+"','"+cbCun.Text.Trim()+"')";
                insertData ii = new insertData(sql);
                if (ii.insertDataState())
                {
                    MessageBox.Show("保存成功!");
                    Getchangsuo();
                    clearChangsuoInfo();
                }
                else
                {
                    MessageBox.Show("保存失败!");
                }
               
            }

        }
        private void ModifyInfo()
        {
            JudgementInfo();    //判断资料

            if (infoState)
            {
                //首先判断村 是选择的 还是新录入的，如果是新录入，则插入 村 表 一条数据
                string strCun = cbCun.Text;
                string strSelect = "select * from xzcun where cunname='" + strCun + "' and xzcode=" + cbxiang.SelectedValue;
                readData rd = new readData();
                DataTable dt = rd.getDataString(strSelect);

                if (dt == null || dt.Rows.Count == 0)
                {
                    //插入村表一条村记录
                    string strInsertCun = "insert into xzcun(xzcode,cunname) values (" + cbxiang.SelectedValue + ",'" + cbCun.Text + "')";
                    insertData icun = new insertData(strInsertCun);
                    if (!icun.insertDataState())
                    {
                        MessageBox.Show("保存失败!");
                        return;
                    }
                }



                string sql = "update changsuo set csmc='" + tbcsmc.Text.Trim() + "',jzryxm='" + tbjzryxm.Text.Trim() + "',czbsj='" + tbczbsj.Text.Trim() + "',csdh='" +
                tbcsdh.Text.Trim() + "',cgfzr='" + tbcgfzr.Text.Trim() + "',xian='" + cbxian.Text + "',xiang='" + cbxiang.Text + "',cun='" + cbCun.Text + "' where csid="+lflag.Text;

                insertData ud = new insertData(sql);
                if (ud.insertDataState())
                {
                    MessageBox.Show("修改成功!");
                    Getchangsuo();
                    clearChangsuoInfo();
                }
                else
                {
                    MessageBox.Show("修改失败!");
                }

               
            }
        }
        //判断资料信息
        private void JudgementInfo()
        {
            if (cbxian.Text == "" || cbxian.Text == "--请选择--")
            {
                MessageBox.Show("请选择县（市、区）!");
                cbxian.DroppedDown = true;
                infoState = false;
                return;
            }
            else if (cbxiang.Text == "" || cbxiang.Text == "--请选择--")
            {
                MessageBox.Show("请选择乡镇!");
                cbxiang.DroppedDown = true;
                infoState = false;
                return;
            }
            else if (cbCun.Text == ""||cbCun.Text == "--请选择或输入--")
            {
                MessageBox.Show("请选择村!");
                cbCun.DroppedDown = true;
                infoState = false;
                return;
            }
            else if (tbcsmc.Text == "")
            {
                MessageBox.Show("请填写场所名称!");
                tbcsmc.Focus();
                infoState = false;
                return;
            }
            else if (cbjb.Text == "" || cbjb.Text == "--请选择--")
            {
                MessageBox.Show("请选择教别!");
                cbjb.DroppedDown = true;
                infoState = false;
                return;
            }
            else if (tbjzryxm.Text == "")
            {
                MessageBox.Show("请填写教职人员姓名!");
                tbjzryxm.Focus();
                infoState = false;
                return;
            }
            else if (tbczbsj.Text == "")
            {
                MessageBox.Show("请填写村支部书记!");
                tbczbsj.Focus();
                infoState = false;
                return;
            }
            else if (tbcsdh.Text == "")
            {
                MessageBox.Show("请填写场所电话!");
                tbcsdh.Focus();
                infoState = false;
                return;
            }
            else if (tbcgfzr.Text == "")
            {
                MessageBox.Show("村民管小组负责人!");
                tbcgfzr.Focus();
                infoState = false;
                return;
            }
            else
            {
                infoState = true;
            }
        }
        /// <summary>
        /// 删除信息
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnDel_Click(object sender, EventArgs e)
        {
            if (lflag.Text == "")
            {
                MessageBox.Show("请选择一条记录！");
            }
            else
            {
                string strSql = "delete from changsuo where csid=" + lflag.Text;
                insertData ud = new insertData(strSql);
                if (ud.insertDataState())
                {
                    MessageBox.Show("删除成功!");
                    Getchangsuo();
                    clearChangsuoInfo();
                }
                else
                {
                    MessageBox.Show("删除失败!");
                }
            
            }
        }
        /// <summary>
        /// 根据输入的条件查找记录
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnSearch_Click(object sender, EventArgs e)
        {
            Searchchangsuo();
        }
        /// <summary>
        /// 根据输入条件查找记录
        /// </summary>
        public void Searchchangsuo()
        {
            readData rd = new readData();
            string sql = "select xian as 县（市、区）,xiang as 乡镇,cun as 村（街）,csmc as 场所名称,jb as 教别,jzryxm as 教职人员姓名,cgfzr as 村管小组负责人,czbsj as 村支部书记,csdh as 场所电话,csid from changsuo where 1=1";

            if (cbxian.Text != "" && cbxian.Text != "--请选择--")
            {
                sql += " and xian='" + cbxian.Text+"'";
            }

            if (cbxiang.Text != "" && cbxiang.Text != "--请选择--")
            {
                sql += " and xiang='" + cbxiang.Text + "'";
            }

            if (cbCun.Text.Trim() != "" && cbCun.Text.Trim() != "--请选择或输入--")
            {
                sql += " and cun like '*" + cbCun.Text.Trim() + "*'";
            }

            if (tbcsmc.Text.Trim() != "")
            {
                sql += " and csmc like '*" + tbcsmc.Text.Trim() + "*'";
            }
            
            if (cbjb.Text != "" && cbjb.Text!= "--请选择--")
            {
                sql += " and jb ='" + cbjb.Text + "'";
            }

            if (tbjzryxm.Text.Trim() != "")
            {
                sql += " and jzryxm like '*" + tbjzryxm.Text.Trim() + "*'";
            }

            if (tbczbsj.Text.Trim() != "")
            {
                sql += " and czbsj like '*" + tbczbsj.Text.Trim() + "*'";
            }

            if (tbcsdh.Text.Trim() != "")
            {
                sql += " and csdh like '*" + tbcsdh.Text.Trim() + "*'";
            }

            if (tbcgfzr.Text.Trim() != "")
            {
                sql += " and cgfzr like '*" + tbcgfzr.Text.Trim() + "*'";
            }


            DataTable dt = rd.getDataString(sql);
            dgvAddress.DataSource = dt;
            dgvAddress.Columns["csid"].Visible = false;

        }

        private void dgvAddress_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
    }
}
