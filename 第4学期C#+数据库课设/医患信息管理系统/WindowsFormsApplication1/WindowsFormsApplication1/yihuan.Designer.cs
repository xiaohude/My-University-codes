namespace WindowsFormsApplication1
{
    partial class yihuan
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
            this.textBox6 = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.textBox5 = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.dateTimePicker1 = new System.Windows.Forms.DateTimePicker();
            this.label5 = new System.Windows.Forms.Label();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.button7 = new System.Windows.Forms.Button();
            this.button6 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // textBox6
            // 
            this.textBox6.Location = new System.Drawing.Point(258, 472);
            this.textBox6.Name = "textBox6";
            this.textBox6.Size = new System.Drawing.Size(71, 25);
            this.textBox6.TabIndex = 66;
            this.textBox6.TextChanged += new System.EventHandler(this.textBox6_TextChanged);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("宋体", 10F);
            this.label7.Location = new System.Drawing.Point(172, 477);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(85, 17);
            this.label7.TabIndex = 65;
            this.label7.Text = "医生编号:";
            // 
            // textBox5
            // 
            this.textBox5.Location = new System.Drawing.Point(258, 419);
            this.textBox5.Name = "textBox5";
            this.textBox5.Size = new System.Drawing.Size(71, 25);
            this.textBox5.TabIndex = 64;
            this.textBox5.TextChanged += new System.EventHandler(this.textBox5_TextChanged);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("宋体", 10F);
            this.label6.Location = new System.Drawing.Point(172, 424);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(85, 17);
            this.label6.TabIndex = 63;
            this.label6.Text = "患者编号:";
            // 
            // dateTimePicker1
            // 
            this.dateTimePicker1.AllowDrop = true;
            this.dateTimePicker1.Location = new System.Drawing.Point(780, 443);
            this.dateTimePicker1.Name = "dateTimePicker1";
            this.dateTimePicker1.Size = new System.Drawing.Size(200, 25);
            this.dateTimePicker1.TabIndex = 60;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("宋体", 10F);
            this.label5.Location = new System.Drawing.Point(706, 451);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(85, 17);
            this.label5.TabIndex = 58;
            this.label5.Text = "看病时间:";
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(535, 475);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(84, 25);
            this.textBox2.TabIndex = 55;
            this.textBox2.Leave += new System.EventHandler(this.textBox2_Leave);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("宋体", 10F);
            this.label2.Location = new System.Drawing.Point(444, 480);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(85, 17);
            this.label2.TabIndex = 54;
            this.label2.Text = "医生姓名:";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(530, 416);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(89, 25);
            this.textBox1.TabIndex = 53;
            this.textBox1.Leave += new System.EventHandler(this.textBox1_Leave);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("宋体", 10F);
            this.label1.Location = new System.Drawing.Point(444, 421);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(85, 17);
            this.label1.TabIndex = 52;
            this.label1.Text = "患者姓名:";
            // 
            // dataGridView1
            // 
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Location = new System.Drawing.Point(2, 2);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.ReadOnly = true;
            this.dataGridView1.RowTemplate.Height = 27;
            this.dataGridView1.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridView1.Size = new System.Drawing.Size(1039, 393);
            this.dataGridView1.TabIndex = 46;
            this.dataGridView1.CellMouseClick += new System.Windows.Forms.DataGridViewCellMouseEventHandler(this.dataGridView1_CellMouseClick);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::WindowsFormsApplication1.Properties.Resources.kungfupanda_03;
            this.pictureBox1.Location = new System.Drawing.Point(759, 2);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(282, 393);
            this.pictureBox1.TabIndex = 68;
            this.pictureBox1.TabStop = false;
            // 
            // button7
            // 
            this.button7.Image = global::WindowsFormsApplication1.Properties.Resources.undo_32x32;
            this.button7.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.button7.Location = new System.Drawing.Point(887, 515);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(80, 42);
            this.button7.TabIndex = 67;
            this.button7.Text = "返回";
            this.button7.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.button7.UseVisualStyleBackColor = true;
            this.button7.Click += new System.EventHandler(this.button7_Click);
            // 
            // button6
            // 
            this.button6.Image = global::WindowsFormsApplication1.Properties.Resources.loop_32x32;
            this.button6.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.button6.Location = new System.Drawing.Point(438, 515);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(81, 42);
            this.button6.TabIndex = 51;
            this.button6.Text = "重置";
            this.button6.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.button6.UseVisualStyleBackColor = true;
            this.button6.Click += new System.EventHandler(this.button6_Click);
            // 
            // button5
            // 
            this.button5.Image = global::WindowsFormsApplication1.Properties.Resources.plus_alt_32x32;
            this.button5.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.button5.Location = new System.Drawing.Point(138, 515);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(81, 42);
            this.button5.TabIndex = 50;
            this.button5.Text = "新建";
            this.button5.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // button4
            // 
            this.button4.Image = global::WindowsFormsApplication1.Properties.Resources.folder_stroke_32x32;
            this.button4.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.button4.Location = new System.Drawing.Point(741, 515);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(78, 42);
            this.button4.TabIndex = 49;
            this.button4.Text = "保存";
            this.button4.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // button3
            // 
            this.button3.Image = global::WindowsFormsApplication1.Properties.Resources.document_stroke_32x32;
            this.button3.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.button3.Location = new System.Drawing.Point(591, 515);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(82, 42);
            this.button3.TabIndex = 48;
            this.button3.Text = "删除";
            this.button3.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // button1
            // 
            this.button1.Image = global::WindowsFormsApplication1.Properties.Resources.magnifying_glass_32x32;
            this.button1.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.button1.Location = new System.Drawing.Point(291, 515);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(81, 42);
            this.button1.TabIndex = 47;
            this.button1.Text = "查询";
            this.button1.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // yihuan
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1042, 580);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.button7);
            this.Controls.Add(this.textBox6);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.textBox5);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.dateTimePicker1);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button6);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.dataGridView1);
            this.Name = "yihuan";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "医患关系管理";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox textBox5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.DateTimePicker dateTimePicker1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.Button button7;
        private System.Windows.Forms.PictureBox pictureBox1;
    }
}