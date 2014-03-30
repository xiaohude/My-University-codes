using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class queren : Form
    {
        public bool b=false ;
        public queren()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            b = true;
            this.Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            b = false;
            this.Close();
        }
    }
}
