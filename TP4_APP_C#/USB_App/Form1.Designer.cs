namespace USB_App
{
    partial class Form1
    {
        /// <summary>
        /// Variable nécessaire au concepteur.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Nettoyage des ressources utilisées.
        /// </summary>
        /// <param name="disposing">true si les ressources managées doivent être supprimées ; sinon, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Code généré par le Concepteur Windows Form

        /// <summary>
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            this.gbParameter = new System.Windows.Forms.GroupBox();
            this.brefresh = new System.Windows.Forms.Button();
            this.bclose = new System.Windows.Forms.Button();
            this.bOpen = new System.Windows.Forms.Button();
            this.lComport = new System.Windows.Forms.Label();
            this.cbComPort = new System.Windows.Forms.ComboBox();
            this.gbRealParameter = new System.Windows.Forms.GroupBox();
            this.lOffset = new System.Windows.Forms.Label();
            this.lAmplitude = new System.Windows.Forms.Label();
            this.lFreq = new System.Windows.Forms.Label();
            this.lShape = new System.Windows.Forms.Label();
            this.tbOffset = new System.Windows.Forms.TextBox();
            this.tbAmp = new System.Windows.Forms.TextBox();
            this.tbFreq = new System.Windows.Forms.TextBox();
            this.tbShape = new System.Windows.Forms.TextBox();
            this.gbSendParameter = new System.Windows.Forms.GroupBox();
            this.bCyclicSending = new System.Windows.Forms.Button();
            this.txtTrameToSend = new System.Windows.Forms.TextBox();
            this.tbSendOffset = new System.Windows.Forms.TextBox();
            this.tbSendAmp = new System.Windows.Forms.TextBox();
            this.tbSendFreq = new System.Windows.Forms.TextBox();
            this.trBOffset = new System.Windows.Forms.TrackBar();
            this.trBAmp = new System.Windows.Forms.TrackBar();
            this.cbNewShape = new System.Windows.Forms.ComboBox();
            this.trBFreq = new System.Windows.Forms.TrackBar();
            this.bSending = new System.Windows.Forms.Button();
            this.chbSauvegarde = new System.Windows.Forms.CheckBox();
            this.gbParameter.SuspendLayout();
            this.gbRealParameter.SuspendLayout();
            this.gbSendParameter.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trBOffset)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trBAmp)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trBFreq)).BeginInit();
            this.SuspendLayout();
            // 
            // gbParameter
            // 
            this.gbParameter.Controls.Add(this.brefresh);
            this.gbParameter.Controls.Add(this.bclose);
            this.gbParameter.Controls.Add(this.bOpen);
            this.gbParameter.Controls.Add(this.lComport);
            this.gbParameter.Controls.Add(this.cbComPort);
            this.gbParameter.Location = new System.Drawing.Point(12, 12);
            this.gbParameter.Name = "gbParameter";
            this.gbParameter.Size = new System.Drawing.Size(499, 44);
            this.gbParameter.TabIndex = 0;
            this.gbParameter.TabStop = false;
            this.gbParameter.Text = "Paramètre de communication";
            // 
            // brefresh
            // 
            this.brefresh.Location = new System.Drawing.Point(458, 14);
            this.brefresh.Name = "brefresh";
            this.brefresh.Size = new System.Drawing.Size(25, 25);
            this.brefresh.TabIndex = 4;
            this.brefresh.Text = "⟳";
            this.brefresh.UseVisualStyleBackColor = true;
            this.brefresh.Click += new System.EventHandler(this.brefresh_Click);
            // 
            // bclose
            // 
            this.bclose.Location = new System.Drawing.Point(358, 15);
            this.bclose.Name = "bclose";
            this.bclose.Size = new System.Drawing.Size(75, 23);
            this.bclose.TabIndex = 3;
            this.bclose.Text = "Fermer";
            this.bclose.UseVisualStyleBackColor = true;
            // 
            // bOpen
            // 
            this.bOpen.Location = new System.Drawing.Point(277, 15);
            this.bOpen.Name = "bOpen";
            this.bOpen.Size = new System.Drawing.Size(75, 23);
            this.bOpen.TabIndex = 2;
            this.bOpen.Text = "Ouvrir";
            this.bOpen.UseVisualStyleBackColor = true;
            // 
            // lComport
            // 
            this.lComport.AutoSize = true;
            this.lComport.Location = new System.Drawing.Point(23, 20);
            this.lComport.Name = "lComport";
            this.lComport.Size = new System.Drawing.Size(68, 13);
            this.lComport.TabIndex = 1;
            this.lComport.Text = "Quelle Port ?";
            // 
            // cbComPort
            // 
            this.cbComPort.FormattingEnabled = true;
            this.cbComPort.Location = new System.Drawing.Point(97, 17);
            this.cbComPort.Name = "cbComPort";
            this.cbComPort.Size = new System.Drawing.Size(174, 21);
            this.cbComPort.TabIndex = 0;
            // 
            // gbRealParameter
            // 
            this.gbRealParameter.Controls.Add(this.lOffset);
            this.gbRealParameter.Controls.Add(this.lAmplitude);
            this.gbRealParameter.Controls.Add(this.lFreq);
            this.gbRealParameter.Controls.Add(this.lShape);
            this.gbRealParameter.Controls.Add(this.tbOffset);
            this.gbRealParameter.Controls.Add(this.tbAmp);
            this.gbRealParameter.Controls.Add(this.tbFreq);
            this.gbRealParameter.Controls.Add(this.tbShape);
            this.gbRealParameter.Location = new System.Drawing.Point(16, 82);
            this.gbRealParameter.Name = "gbRealParameter";
            this.gbRealParameter.Size = new System.Drawing.Size(231, 143);
            this.gbRealParameter.TabIndex = 2;
            this.gbRealParameter.TabStop = false;
            this.gbRealParameter.Text = "Paramètre Actuel Reçu";
            // 
            // lOffset
            // 
            this.lOffset.AutoSize = true;
            this.lOffset.Location = new System.Drawing.Point(6, 115);
            this.lOffset.Name = "lOffset";
            this.lOffset.Size = new System.Drawing.Size(35, 13);
            this.lOffset.TabIndex = 8;
            this.lOffset.Text = "Offset";
            // 
            // lAmplitude
            // 
            this.lAmplitude.AutoSize = true;
            this.lAmplitude.Location = new System.Drawing.Point(6, 89);
            this.lAmplitude.Name = "lAmplitude";
            this.lAmplitude.Size = new System.Drawing.Size(53, 13);
            this.lAmplitude.TabIndex = 7;
            this.lAmplitude.Text = "Amplitude";
            // 
            // lFreq
            // 
            this.lFreq.AutoSize = true;
            this.lFreq.Location = new System.Drawing.Point(6, 63);
            this.lFreq.Name = "lFreq";
            this.lFreq.Size = new System.Drawing.Size(58, 13);
            this.lFreq.TabIndex = 6;
            this.lFreq.Text = "Fréquence";
            // 
            // lShape
            // 
            this.lShape.AutoSize = true;
            this.lShape.Location = new System.Drawing.Point(6, 34);
            this.lShape.Name = "lShape";
            this.lShape.Size = new System.Drawing.Size(81, 13);
            this.lShape.TabIndex = 5;
            this.lShape.Text = "Forme du signal";
            // 
            // tbOffset
            // 
            this.tbOffset.Location = new System.Drawing.Point(112, 112);
            this.tbOffset.Name = "tbOffset";
            this.tbOffset.ReadOnly = true;
            this.tbOffset.Size = new System.Drawing.Size(113, 20);
            this.tbOffset.TabIndex = 3;
            // 
            // tbAmp
            // 
            this.tbAmp.Location = new System.Drawing.Point(112, 86);
            this.tbAmp.Name = "tbAmp";
            this.tbAmp.ReadOnly = true;
            this.tbAmp.Size = new System.Drawing.Size(113, 20);
            this.tbAmp.TabIndex = 2;
            // 
            // tbFreq
            // 
            this.tbFreq.Location = new System.Drawing.Point(112, 60);
            this.tbFreq.Name = "tbFreq";
            this.tbFreq.ReadOnly = true;
            this.tbFreq.Size = new System.Drawing.Size(113, 20);
            this.tbFreq.TabIndex = 1;
            // 
            // tbShape
            // 
            this.tbShape.Location = new System.Drawing.Point(112, 34);
            this.tbShape.Name = "tbShape";
            this.tbShape.ReadOnly = true;
            this.tbShape.Size = new System.Drawing.Size(113, 20);
            this.tbShape.TabIndex = 0;
            // 
            // gbSendParameter
            // 
            this.gbSendParameter.Controls.Add(this.bCyclicSending);
            this.gbSendParameter.Controls.Add(this.txtTrameToSend);
            this.gbSendParameter.Controls.Add(this.tbSendOffset);
            this.gbSendParameter.Controls.Add(this.tbSendAmp);
            this.gbSendParameter.Controls.Add(this.tbSendFreq);
            this.gbSendParameter.Controls.Add(this.trBOffset);
            this.gbSendParameter.Controls.Add(this.trBAmp);
            this.gbSendParameter.Controls.Add(this.cbNewShape);
            this.gbSendParameter.Controls.Add(this.trBFreq);
            this.gbSendParameter.Controls.Add(this.bSending);
            this.gbSendParameter.Controls.Add(this.chbSauvegarde);
            this.gbSendParameter.Location = new System.Drawing.Point(253, 82);
            this.gbSendParameter.Name = "gbSendParameter";
            this.gbSendParameter.Size = new System.Drawing.Size(258, 241);
            this.gbSendParameter.TabIndex = 3;
            this.gbSendParameter.TabStop = false;
            this.gbSendParameter.Text = "Paramètre A Envoyé";
            // 
            // bCyclicSending
            // 
            this.bCyclicSending.Location = new System.Drawing.Point(117, 212);
            this.bCyclicSending.Name = "bCyclicSending";
            this.bCyclicSending.Size = new System.Drawing.Size(125, 23);
            this.bCyclicSending.TabIndex = 17;
            this.bCyclicSending.Text = "Envois cyclique";
            this.bCyclicSending.UseVisualStyleBackColor = true;
            this.bCyclicSending.Click += new System.EventHandler(this.bCyclicSending_Click);
            // 
            // txtTrameToSend
            // 
            this.txtTrameToSend.Location = new System.Drawing.Point(36, 182);
            this.txtTrameToSend.Name = "txtTrameToSend";
            this.txtTrameToSend.ReadOnly = true;
            this.txtTrameToSend.Size = new System.Drawing.Size(206, 20);
            this.txtTrameToSend.TabIndex = 9;
            // 
            // tbSendOffset
            // 
            this.tbSendOffset.Location = new System.Drawing.Point(185, 112);
            this.tbSendOffset.Name = "tbSendOffset";
            this.tbSendOffset.ReadOnly = true;
            this.tbSendOffset.Size = new System.Drawing.Size(57, 20);
            this.tbSendOffset.TabIndex = 16;
            // 
            // tbSendAmp
            // 
            this.tbSendAmp.Location = new System.Drawing.Point(185, 86);
            this.tbSendAmp.Name = "tbSendAmp";
            this.tbSendAmp.ReadOnly = true;
            this.tbSendAmp.Size = new System.Drawing.Size(57, 20);
            this.tbSendAmp.TabIndex = 15;
            // 
            // tbSendFreq
            // 
            this.tbSendFreq.Location = new System.Drawing.Point(185, 57);
            this.tbSendFreq.Name = "tbSendFreq";
            this.tbSendFreq.ReadOnly = true;
            this.tbSendFreq.Size = new System.Drawing.Size(57, 20);
            this.tbSendFreq.TabIndex = 9;
            // 
            // trBOffset
            // 
            this.trBOffset.Location = new System.Drawing.Point(6, 115);
            this.trBOffset.Name = "trBOffset";
            this.trBOffset.Size = new System.Drawing.Size(173, 45);
            this.trBOffset.TabIndex = 14;
            // 
            // trBAmp
            // 
            this.trBAmp.Location = new System.Drawing.Point(6, 89);
            this.trBAmp.Name = "trBAmp";
            this.trBAmp.Size = new System.Drawing.Size(173, 45);
            this.trBAmp.TabIndex = 5;
            // 
            // cbNewShape
            // 
            this.cbNewShape.FormattingEnabled = true;
            this.cbNewShape.Location = new System.Drawing.Point(6, 33);
            this.cbNewShape.Name = "cbNewShape";
            this.cbNewShape.Size = new System.Drawing.Size(236, 21);
            this.cbNewShape.TabIndex = 3;
            // 
            // trBFreq
            // 
            this.trBFreq.Location = new System.Drawing.Point(6, 57);
            this.trBFreq.Maximum = 2000;
            this.trBFreq.Name = "trBFreq";
            this.trBFreq.Size = new System.Drawing.Size(173, 45);
            this.trBFreq.TabIndex = 4;
            // 
            // bSending
            // 
            this.bSending.Location = new System.Drawing.Point(36, 212);
            this.bSending.Name = "bSending";
            this.bSending.Size = new System.Drawing.Size(75, 23);
            this.bSending.TabIndex = 3;
            this.bSending.Text = "Envoyer";
            this.bSending.UseVisualStyleBackColor = true;
            // 
            // chbSauvegarde
            // 
            this.chbSauvegarde.AutoSize = true;
            this.chbSauvegarde.Location = new System.Drawing.Point(95, 159);
            this.chbSauvegarde.Name = "chbSauvegarde";
            this.chbSauvegarde.Size = new System.Drawing.Size(84, 17);
            this.chbSauvegarde.TabIndex = 13;
            this.chbSauvegarde.Text = "Sauvegarde";
            this.chbSauvegarde.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.ClientSize = new System.Drawing.Size(521, 327);
            this.Controls.Add(this.gbSendParameter);
            this.Controls.Add(this.gbRealParameter);
            this.Controls.Add(this.gbParameter);
            this.Name = "Form1";
            this.Text = "USB GENERATEUR";
            this.gbParameter.ResumeLayout(false);
            this.gbParameter.PerformLayout();
            this.gbRealParameter.ResumeLayout(false);
            this.gbRealParameter.PerformLayout();
            this.gbSendParameter.ResumeLayout(false);
            this.gbSendParameter.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trBOffset)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trBAmp)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trBFreq)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox gbParameter;
        private System.Windows.Forms.Button bOpen;
        private System.Windows.Forms.Label lComport;
        private System.Windows.Forms.ComboBox cbComPort;
        private System.Windows.Forms.GroupBox gbRealParameter;
        private System.Windows.Forms.Label lOffset;
        private System.Windows.Forms.Label lAmplitude;
        private System.Windows.Forms.Label lFreq;
        private System.Windows.Forms.Label lShape;
        private System.Windows.Forms.TextBox tbOffset;
        private System.Windows.Forms.TextBox tbAmp;
        private System.Windows.Forms.TextBox tbFreq;
        private System.Windows.Forms.TextBox tbShape;
        private System.Windows.Forms.GroupBox gbSendParameter;
        private System.Windows.Forms.ComboBox cbNewShape;
        private System.Windows.Forms.Button bSending;
        private System.Windows.Forms.CheckBox chbSauvegarde;
        private System.Windows.Forms.TrackBar trBFreq;
        private System.Windows.Forms.TrackBar trBAmp;
        private System.Windows.Forms.TrackBar trBOffset;
        private System.Windows.Forms.TextBox tbSendOffset;
        private System.Windows.Forms.TextBox tbSendAmp;
        private System.Windows.Forms.TextBox tbSendFreq;
        private System.Windows.Forms.Button bclose;
        private System.Windows.Forms.TextBox txtTrameToSend;
        private System.Windows.Forms.Button brefresh;
        private System.Windows.Forms.Button bCyclicSending;
    }
}

