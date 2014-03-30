using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace zjgl
{
    public partial class MDIZJGL : Form
    {
        private int childFormNumber = 0;

        public MDIZJGL()
        {
            InitializeComponent();
        }

        private void ShowNewForm(object sender, EventArgs e)
        {
            Form childForm = new Form();
            childForm.MdiParent = this;
            childForm.Text = "窗口 " + childFormNumber++;
            childForm.Show();
        }

        private void OpenFile(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.Personal);
            openFileDialog.Filter = "文本文件(*.txt)|*.txt|所有文件(*.*)|*.*";
            if (openFileDialog.ShowDialog(this) == DialogResult.OK)
            {
                string FileName = openFileDialog.FileName;
            }
        }

        private void SaveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.Personal);
            saveFileDialog.Filter = "文本文件(*.txt)|*.txt|所有文件(*.*)|*.*";
            if (saveFileDialog.ShowDialog(this) == DialogResult.OK)
            {
                string FileName = saveFileDialog.FileName;
            }
        }

        private void ExitToolsStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void CutToolStripMenuItem_Click(object sender, EventArgs e)
        {
        }

        private void CopyToolStripMenuItem_Click(object sender, EventArgs e)
        {
        }

        private void PasteToolStripMenuItem_Click(object sender, EventArgs e)
        {
        }


        private void CascadeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LayoutMdi(MdiLayout.Cascade);
        }

        private void TileVerticalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LayoutMdi(MdiLayout.TileVertical);
        }

        private void TileHorizontalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LayoutMdi(MdiLayout.TileHorizontal);
        }

        private void ArrangeIconsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LayoutMdi(MdiLayout.ArrangeIcons);
        }

        private void CloseAllToolStripMenuItem_Click(object sender, EventArgs e)
        {
            foreach (Form childForm in MdiChildren)
            {
                childForm.Close();
            }
        }

        private void toolStripButton3_Click(object sender, EventArgs e)
        {
            //录入宗教场所
            FrmAddress ad = new FrmAddress();
            ad.ShowDialog(this);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            txtDateTime.Text = "当前时间:" + DateTime.Now.ToString();
        }

        private void 退出ToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("廊坊市宗教信息管理系统 V1.0\n\n技术支持: 象王科技\n咨询QQ:95201731\nEmail:95201731@qq.com\n联系电话:15133698682\n官方网址:http://www.corp-partner.com", "关于我们", MessageBoxButtons.OK, MessageBoxIcon.Information, MessageBoxDefaultButton.Button1);

        }

        private void toolStripMenuItem6_Click(object sender, EventArgs e)
        {
            //录入宗教场所
            FrmAddress ad = new FrmAddress();
            ad.ShowDialog(this);
        }

        private void toolStripMenuItem16_Click(object sender, EventArgs e)
        {
            changsuotongji cstj = new changsuotongji();
            cstj.ShowDialog(this);
        }

        private void toolStripButton4_Click(object sender, EventArgs e)
        {

        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {

        }

        private void toolStripButton2_Click(object sender, EventArgs e)
        {

        }

        private void toolStripMenuItem14_Click(object sender, EventArgs e)
        {
            qunzhongtongji f1=new qunzhongtongji();
            f1.ShowDialog();
        }

        private void toolStripMenuItem15_Click(object sender, EventArgs e)
        {
            jiaozhitongji jz = new jiaozhitongji();
            jz.ShowDialog();
        }

        private void MDIZJGL_Load(object sender, EventArgs e)
        {

        }
    }
}
