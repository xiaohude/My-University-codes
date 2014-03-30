namespace WindowsFormsApplication1
{
    partial class quyao
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
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.dateTimePicker1 = new System.Windows.Forms.DateTimePicker();
            this.label8 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.textBox4 = new System.Windows.Forms.TextBox();
            this.textBox5 = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.textBox6 = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
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
            // dataGridView1
            // 
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Location = new System.Drawing.Point(1, 1);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.ReadOnly = true;
            this.dataGridView1.RowTemplate.Height = 27;
            this.dataGridView1.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridView1.Size = new System.Drawing.Size(1039, 393);
            this.dataGridView1.TabIndex = 1;
            this.dataGridView1.CellMouseClick += new System.Windows.Forms.DataGridViewCellMouseEventHandler(this.dataGridView1_CellMouseClick);
            // 
            // dateTimePicker1
            // 
            this.dateTimePicker1.AllowDrop = true;
            this.dateTimePicker1.Location = new System.Drawing.Point(830, 465);
            this.dateTimePicker1.Name = "dateTimePicker1";
            this.dateTimePicker1.Size = new System.Drawing.Size(200, 25);
            this.dateTimePicker1.TabIndex = 39;
            this.dateTimePicker1.ValueChanged += new System.EventHandler(this.dateTimePicker1_ValueChanged);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("宋体", 10F);
            this.label8.Location = new System.Drawing.Point(699, 473);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(25, 17);
            this.label8.TabIndex = 38;
            this.label8.Text = "元";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("宋体", 10F);
            this.label5.Location = new System.Drawing.Point(756, 473);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(85, 17);
            this.label5.TabIndex = 37;
            this.label5.Text = "取药时间:";
            // 
            // textBox3
            // 
            this.textBox3.Location = new System.Drawing.Point(485, 465);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(46, 25);
            this.textBox3.TabIndex = 34;
            this.textBox3.TextChanged += new System.EventHandler(this.textBox3_TextChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("宋体", 10F);
            this.label3.Location = new System.Drawing.Point(394, 473);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(85, 17);
            this.label3.TabIndex = 33;
            this.label3.Text = "取药数量:";
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(278, 465);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(110, 25);
            this.textBox2.TabIndex = 32;
            this.textBox2.Leave += new System.EventHandler(this.textBox2_Leave);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("宋体", 10F);
            this.label2.Location = new System.Drawing.Point(187, 470);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(85, 17);
            this.label2.TabIndex = 31;
            this.label2.Text = "药品名称:";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(117, 465);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(71, 25);
            this.textBox1.TabIndex = 30;
            this.textBox1.Leave += new System.EventHandler(this.textBox1_Leave);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("宋体", 10F);
            this.label1.Location = new System.Drawing.Point(31, 470);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(85, 17);
            this.label1.TabIndex = 29;
            this.label1.Text = "患者姓名:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("宋体", 10F);
            this.label4.Location = new System.Drawing.Point(537, 473);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(85, 17);
            this.label4.TabIndex = 40;
            this.label4.Text = "药品单价:";
            // 
            // textBox4
            // 
            this.textBox4.Location = new System.Drawing.Point(628, 465);
            this.textBox4.Name = "textBox4";
            this.textBox4.Size = new System.Drawing.Size(65, 25);
            this.textBox4.TabIndex = 41;
            // 
            // textBox5
            // 
            this.textBox5.Location = new System.Drawing.Point(327, 415);
            this.textBox5.Name = "textBox5";
            this.textBox5.Size = new System.Drawing.Size(71, 25);
            this.textBox5.TabIndex = 43;
            this.textBox5.TextChanged += new System.EventHandler(this.textBox5_TextChanged);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("宋体", 10F);
            this.label6.Location = new System.Drawing.Point(241, 420);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(85, 17);
            this.label6.TabIndex = 42;
            this.label6.Text = "患者编号:";
            // 
            // textBox6
            // 
            this.textBox6.Location = new System.Drawing.Point(635, 415);
            this.textBox6.Name = "textBox6";
            this.textBox6.Size = new System.Drawing.Size(71, 25);
            this.textBox6.TabIndex = 45;
            this.textBox6.TextChanged += new System.EventHandler(this.textBox6_TextChanged);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("宋体", 10F);
            this.label7.Location = new System.Drawing.Point(549, 420);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(85, 17);
            this.label7.TabIndex = 44;
            this.label7.Text = "药品编号:";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::WindowsFormsApplication1.Properties.Resources._3D_hospital_26;
            this.pictureBox1.Location = new System.Drawing.Point(759, 1);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(281, 393);
            this.pictureBox1.TabIndex = 47;
            this.pictureBox1.TabStop = false;
            // 
            // button7
            // 
            this.button7.Image = global::WindowsFormsApplication1.Properties.Resources.undo_32x32;
            this.button7.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.button7.Location = new System.Drawing.Point(868, 513);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(79, 43);
            this.button7.TabIndex = 46;
            this.button7.Text = "返回";
            this.button7.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.button7.UseVisualStyleBackColor = true;
            this.button7.Click += new System.EventHandler(this.button7_Click);
            // 
            // button6
            // 
            this.button6.Image = global::WindowsFormsApplication1.Properties.Resources.loop_32x32;
            this.button6.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.button6.Location = new System.Drawing.Point(424, 513);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(82, 43);
            this.button6.TabIndex = 27;
            this.button6.Text = "重置";
            this.button6.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.button6.UseVisualStyleBackColor = true;
            this.button6.Click += new System.EventHandler(this.button6_Click);
            // 
            // button5
            // 
            this.button5.Image = global::WindowsFormsApplication1.Properties.Resources.plus_alt_32x32;
            this.button5.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.button5.Location = new System.Drawing.Point(117, 513);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(81, 43);
            this.button5.TabIndex = 26;
            this.button5.Text = "新建";
            this.button5.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // button4
            // 
            this.button4.Image = global::WindowsFormsApplication1.Properties.Resources.folder_stroke_32x32;
            this.button4.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.button4.Location = new System.Drawing.Point(722, 513);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(80, 43);
            this.button4.TabIndex = 25;
            this.button4.Text = "保存";
            this.button4.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // button3
            // 
            this.button3.Image = global::WindowsFormsApplication1.Properties.Resources.document_stroke_32x32;
            this.button3.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.button3.Location = new System.Drawing.Point(573, 513);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(82, 43);
            this.button3.TabIndex = 24;
            this.button3.Text = "删除";
            this.button3.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // button1
            // 
            this.button1.Image = global::WindowsFormsApplication1.Properties.Resources.magnifying_glass_32x32;
            this.button1.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.button1.Location = new System.Drawing.Point(269, 513);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(81, 43);
            this.button1.TabIndex = 22;
            this.button1.Text = "查询";
            this.button1.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // quyao
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
            this.Controls.Add(this.textBox4);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.dateTimePicker1);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.textBox3);
            this.Controls.Add(this.label3);
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
            this.Name = "quyao";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "患者取药管理";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.DateTimePicker dateTimePicker1;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBox4;
        private System.Windows.Forms.TextBox textBox5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox textBox6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button button7;
        private System.Windows.Forms.PictureBox pictureBox1;
    }
}