namespace WindowsFormsApplication1
{
    partial class main
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(main));
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.医生信息ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.管理医生信息ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.病人信息ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.管理患者信息ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.药品信息ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.管理药品信息ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.患者取药信息ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.管理患者取药信息ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.医患关系信息ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.管理医患关系信息ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // dataGridView1
            // 
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Location = new System.Drawing.Point(0, 31);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.ReadOnly = true;
            this.dataGridView1.RowTemplate.Height = 27;
            this.dataGridView1.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridView1.Size = new System.Drawing.Size(773, 465);
            this.dataGridView1.TabIndex = 1;
            // 
            // 医生信息ToolStripMenuItem
            // 
            this.医生信息ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.管理医生信息ToolStripMenuItem});
            this.医生信息ToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Red;
            this.医生信息ToolStripMenuItem.Name = "医生信息ToolStripMenuItem";
            this.医生信息ToolStripMenuItem.Size = new System.Drawing.Size(81, 24);
            this.医生信息ToolStripMenuItem.Text = "医生信息";
            this.医生信息ToolStripMenuItem.Click += new System.EventHandler(this.医生信息ToolStripMenuItem_Click_1);
            // 
            // 管理医生信息ToolStripMenuItem
            // 
            this.管理医生信息ToolStripMenuItem.Name = "管理医生信息ToolStripMenuItem";
            this.管理医生信息ToolStripMenuItem.Size = new System.Drawing.Size(168, 24);
            this.管理医生信息ToolStripMenuItem.Text = "管理医生信息";
            this.管理医生信息ToolStripMenuItem.Click += new System.EventHandler(this.管理医生信息ToolStripMenuItem_Click);
            // 
            // 病人信息ToolStripMenuItem
            // 
            this.病人信息ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.管理患者信息ToolStripMenuItem});
            this.病人信息ToolStripMenuItem.Name = "病人信息ToolStripMenuItem";
            this.病人信息ToolStripMenuItem.Size = new System.Drawing.Size(81, 24);
            this.病人信息ToolStripMenuItem.Text = "患者信息";
            this.病人信息ToolStripMenuItem.Click += new System.EventHandler(this.病人信息ToolStripMenuItem_Click);
            // 
            // 管理患者信息ToolStripMenuItem
            // 
            this.管理患者信息ToolStripMenuItem.Name = "管理患者信息ToolStripMenuItem";
            this.管理患者信息ToolStripMenuItem.Size = new System.Drawing.Size(168, 24);
            this.管理患者信息ToolStripMenuItem.Text = "管理患者信息";
            this.管理患者信息ToolStripMenuItem.Click += new System.EventHandler(this.管理患者信息ToolStripMenuItem_Click);
            // 
            // 药品信息ToolStripMenuItem
            // 
            this.药品信息ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.管理药品信息ToolStripMenuItem});
            this.药品信息ToolStripMenuItem.Name = "药品信息ToolStripMenuItem";
            this.药品信息ToolStripMenuItem.Size = new System.Drawing.Size(81, 24);
            this.药品信息ToolStripMenuItem.Text = "药品信息";
            this.药品信息ToolStripMenuItem.Click += new System.EventHandler(this.药品信息ToolStripMenuItem_Click);
            // 
            // 管理药品信息ToolStripMenuItem
            // 
            this.管理药品信息ToolStripMenuItem.Name = "管理药品信息ToolStripMenuItem";
            this.管理药品信息ToolStripMenuItem.Size = new System.Drawing.Size(168, 24);
            this.管理药品信息ToolStripMenuItem.Text = "管理药品信息";
            this.管理药品信息ToolStripMenuItem.Click += new System.EventHandler(this.管理药品信息ToolStripMenuItem_Click);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.病人信息ToolStripMenuItem,
            this.医生信息ToolStripMenuItem,
            this.药品信息ToolStripMenuItem,
            this.患者取药信息ToolStripMenuItem,
            this.医患关系信息ToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1027, 28);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 患者取药信息ToolStripMenuItem
            // 
            this.患者取药信息ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.管理患者取药信息ToolStripMenuItem});
            this.患者取药信息ToolStripMenuItem.Name = "患者取药信息ToolStripMenuItem";
            this.患者取药信息ToolStripMenuItem.Size = new System.Drawing.Size(111, 24);
            this.患者取药信息ToolStripMenuItem.Text = "患者取药信息";
            this.患者取药信息ToolStripMenuItem.Click += new System.EventHandler(this.患者取药信息ToolStripMenuItem_Click);
            // 
            // 管理患者取药信息ToolStripMenuItem
            // 
            this.管理患者取药信息ToolStripMenuItem.Name = "管理患者取药信息ToolStripMenuItem";
            this.管理患者取药信息ToolStripMenuItem.Size = new System.Drawing.Size(198, 24);
            this.管理患者取药信息ToolStripMenuItem.Text = "管理患者取药信息";
            this.管理患者取药信息ToolStripMenuItem.Click += new System.EventHandler(this.管理患者取药信息ToolStripMenuItem_Click);
            // 
            // 医患关系信息ToolStripMenuItem
            // 
            this.医患关系信息ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.管理医患关系信息ToolStripMenuItem});
            this.医患关系信息ToolStripMenuItem.Name = "医患关系信息ToolStripMenuItem";
            this.医患关系信息ToolStripMenuItem.Size = new System.Drawing.Size(111, 24);
            this.医患关系信息ToolStripMenuItem.Text = "医患关系信息";
            this.医患关系信息ToolStripMenuItem.Click += new System.EventHandler(this.医患关系信息ToolStripMenuItem_Click);
            // 
            // 管理医患关系信息ToolStripMenuItem
            // 
            this.管理医患关系信息ToolStripMenuItem.Name = "管理医患关系信息ToolStripMenuItem";
            this.管理医患关系信息ToolStripMenuItem.Size = new System.Drawing.Size(198, 24);
            this.管理医患关系信息ToolStripMenuItem.Text = "管理医患关系信息";
            this.管理医患关系信息ToolStripMenuItem.Click += new System.EventHandler(this.管理医患关系信息ToolStripMenuItem_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(101, 515);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(136, 43);
            this.button1.TabIndex = 2;
            this.button1.Text = "患者信息管理";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(288, 515);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(135, 43);
            this.button2.TabIndex = 3;
            this.button2.Text = "医生信息管理";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(461, 515);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(119, 43);
            this.button3.TabIndex = 4;
            this.button3.Text = "药品信息管理";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(637, 515);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(122, 43);
            this.button4.TabIndex = 5;
            this.button4.Text = "患者取药";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(810, 515);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(104, 43);
            this.button5.TabIndex = 6;
            this.button5.Text = "医生看病";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = global::WindowsFormsApplication1.Properties.Resources._1212;
            this.ClientSize = new System.Drawing.Size(1027, 570);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.dataGridView1);
            this.Controls.Add(this.menuStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "main";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "医院信息管理系统";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.ToolStripMenuItem 医生信息ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 病人信息ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 药品信息ToolStripMenuItem;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.ToolStripMenuItem 管理医生信息ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 管理患者信息ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 管理药品信息ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 患者取药信息ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 管理患者取药信息ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 医患关系信息ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 管理医患关系信息ToolStripMenuItem;
    }
}