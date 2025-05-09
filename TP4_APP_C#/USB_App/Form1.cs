using System;
using System.IO;
using System.IO.Ports;
using System.Windows.Forms;
using System.Collections.Generic;
using System.Linq;

namespace USB_App
{
    public partial class Form1 : Form
    {
        private SerialPort serialPort = new SerialPort();
        private readonly Receive_Signal reception = new Receive_Signal();

        /* -------- Envoi cyclique 25 ms -------- */
        private readonly System.Windows.Forms.Timer cyclicTimer =
            new System.Windows.Forms.Timer { Interval = 25 };
        private bool isCyclicSending = false;
        /* -------------------------------------- */

        /* -------- User-adjust logic -------- */
        private bool userAdjusting = false;   // vrai pendant que la souris est enfoncée
        private string lastSentCore = "";     // trame sans W
        /* ----------------------------------- */

        public Form1()
        {
            cyclicTimer.Tick += CyclicTimer_Tick;        // handler avant Init
            InitializeComponent();

            LoadAvailableComPorts();

            gbRealParameter.Enabled = false;
            gbSendParameter.Enabled = false;

            cbNewShape.Items.Clear();
            cbNewShape.Items.AddRange(new[] { "Sinus (S)", "Triangle (T)", "Carré (C)", "Dent de scie (D)" });
            cbNewShape.SelectedIndex = 0;

            bOpen.Click += bOpen_Click;
            bclose.Click += bClose_Click;
            bSending.Click += bSending_Click;
            brefresh.Click += brefresh_Click;            // bCyclicSending déjà relié via Designer

            /* sliders */
            trBFreq.Minimum = 20; trBFreq.Maximum = 2000; trBFreq.TickFrequency = 100;
            trBAmp.Minimum = 0; trBAmp.Maximum = 10000; trBAmp.TickFrequency = 100;
            trBOffset.Minimum = -5000; trBOffset.Maximum = 5000; trBOffset.TickFrequency = 100;

            trBFreq.Value = trBFreq.Minimum;
            trBAmp.Value = trBAmp.Minimum;
            trBOffset.Value = 0;

            /* handlers sliders */
            cbNewShape.SelectedIndexChanged += UpdateTramePreview;
            trBFreq.Scroll += UpdateFreqText; trBFreq.Scroll += UpdateTramePreview;
            trBAmp.Scroll += UpdateAmpText; trBAmp.Scroll += UpdateTramePreview;
            trBOffset.Scroll += UpdateOffsetText; trBOffset.Scroll += UpdateTramePreview;
            chbSauvegarde.CheckedChanged += UpdateTramePreview;

            /* affichage initial */
            UpdateFreqText(null, null);
            UpdateAmpText(null, null);
            UpdateOffsetText(null, null);
            UpdateTramePreview(null, null);

            bCyclicSending.Enabled = false;       // actif après connexion
        }

        /* ================ Connexion ================= */
        private void bOpen_Click(object sender, EventArgs e)
        {
            try
            {
                if (cbComPort.SelectedItem == null)
                {
                    MessageBox.Show("Aucun port sélectionné.");
                    return;
                }

                if (!serialPort.IsOpen)
                {
                    serialPort.PortName = cbComPort.SelectedItem.ToString();
                    serialPort.BaudRate = 57600;
                    serialPort.DataBits = 8;
                    serialPort.Parity = Parity.None;
                    serialPort.StopBits = StopBits.One;
                    serialPort.DataReceived += SerialPort_DataReceived;
                    serialPort.Open();

                    gbRealParameter.Enabled = true;
                    gbSendParameter.Enabled = true;
                    bOpen.Enabled = false;
                    cbComPort.Enabled = false;
                    bclose.Enabled = true;
                    bSending.Enabled = true;
                    bCyclicSending.Enabled = true;
                    brefresh.Enabled = false;   // refresh indispo pendant connexion
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Erreur connexion : " + ex.Message);
            }
        }

        private void Slider_MouseDown(object sender, MouseEventArgs e)
        {
            if (isCyclicSending) userAdjusting = true;   // on gèle l’envoi
        }

        private void Slider_MouseUp(object sender, MouseEventArgs e)
        {
            if (!isCyclicSending) return;

            userAdjusting = false;       // on libère l’envoi

            /* Forcer UNE sauvegarde au prochain tick */
            chbSauvegarde.Checked = true;
            lastSentCore = "";           // pour être sûr de détecter le changement
        }

        private void bClose_Click(object sender, EventArgs e)
        {
            try { if (serialPort.IsOpen) serialPort.Close(); }
            catch { }

            StopCyclic();
            ResetUI();
            LoadAvailableComPorts();
        }

        /* ------------- Reset complet (UI + états) ------------- */
        private void ResetUI()
        {
            cyclicTimer.Stop();
            isCyclicSending = false;
            bCyclicSending.Text = "Envois cyclique";
            bCyclicSending.Enabled = false;

            cbComPort.Enabled = true;
            bOpen.Enabled = true;
            bclose.Enabled = false;
            bSending.Enabled = false;
            brefresh.Enabled = true;

            gbRealParameter.Enabled = false;
            gbSendParameter.Enabled = false;

            tbShape.Clear(); tbFreq.Clear(); tbAmp.Clear(); tbOffset.Clear();
            trBFreq.Value = trBFreq.Minimum;
            trBAmp.Value = trBAmp.Minimum;
            trBOffset.Value = 0;
            chbSauvegarde.Checked = false;

            UpdateFreqText(null, null);
            UpdateAmpText(null, null);
            UpdateOffsetText(null, null);
            UpdateTramePreview(null, null);
        }

        /* ------------- Gestion d’erreur série ------------- */
        private void HandleSerialError(string message)
        {
            MessageBox.Show(message, "USB App", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            try { if (serialPort.IsOpen) serialPort.Close(); } catch { }
            ResetUI();
            LoadAvailableComPorts();
        }

        /* ================= Envoi manuel =================== */
        private void bSending_Click(object sender, EventArgs e)
        {
            if (!serialPort.IsOpen) return;
            try { serialPort.WriteLine(GenerateTrame()); }
            catch (Exception ex) { HandleSerialError("Erreur d'envoi : " + ex.Message); }
        }

        /* ================ Bouton cyclique ================= */
        private void bCyclicSending_Click(object sender, EventArgs e)
        {
            if (!serialPort.IsOpen)
            {
                MessageBox.Show("Le port série n'est pas ouvert.");
                return;
            }

            if (isCyclicSending) StopCyclic();
            else StartCyclic();
        }

        private void StartCyclic()
        {
            if (isCyclicSending) return;
            serialPort.DiscardOutBuffer();
            cyclicTimer.Start();
            isCyclicSending = true;
            bCyclicSending.Text = "Stop";
        }

        private void StopCyclic()
        {
            cyclicTimer.Stop();
            isCyclicSending = false;
            bCyclicSending.Text = "Envois cyclique";
        }

        private void CyclicTimer_Tick(object sender, EventArgs e)
        {
            if (!serialPort.IsOpen)
            {
                StopCyclic(); ResetUI(); LoadAvailableComPorts();
                return;
            }

            if (userAdjusting) return;       // gel complet tant que la souris est enfoncée

            string trame = GenerateTrame();
            string core = trame.Substring(0, trame.IndexOf("W="));   // sans W, sans #

            /* ------ ENVOI SEULEMENT SI : ------ 
               1) l’utilisateur n’est plus en train d’ajuster
               2) ET (la valeur a changé  OU  W=1 demandé)        */
            bool needSend = chbSauvegarde.Checked || core != lastSentCore;
            if (!needSend) return;

            try
            {
                serialPort.WriteLine(trame);
                lastSentCore = core;

                if (chbSauvegarde.Checked)
                    chbSauvegarde.Checked = false;     // W=1 envoyé une fois puis décoché
            }
            catch (Exception ex)
            {
                HandleSerialError("Envoi cyclique : " + ex.Message);
            }
        }


        /* ================= Refresh COM =================== */
        private void brefresh_Click(object sender, EventArgs e) => LoadAvailableComPorts();

        private void LoadAvailableComPorts()
        {
            string[] allPorts = SerialPort.GetPortNames();     // tous les noms
            List<string> validPorts = new List<string>();

            foreach (string port in allPorts)
            {
                // Teste rapidement si le port répond : s’il n’existe plus ou qu’il est
                // déjà ouvert par un driver zombie, Open() lèvera une exception.
                try
                {
                    using (SerialPort test = new SerialPort(port))
                    {
                        test.Open();
                        test.Close();
                        validPorts.Add(port);                 // port réellement présent
                    }
                }
                catch
                {
                    /* fantôme => ignoré */
                }
            }

            // Nettoie et recharge la ComboBox sans doublons
            string selected = cbComPort.SelectedItem as string;

            cbComPort.BeginUpdate();
            cbComPort.Items.Clear();
            foreach (string p in validPorts.Distinct(StringComparer.OrdinalIgnoreCase))
                cbComPort.Items.Add(p);
            cbComPort.EndUpdate();

            // Restaure la sélection si possible
            if (selected != null && cbComPort.Items.Contains(selected))
                cbComPort.SelectedItem = selected;
            else if (cbComPort.Items.Count > 0)
                cbComPort.SelectedIndex = 0;
            else
                cbComPort.Text = "Aucun port valide";
        }


        /* ================== Réception ==================== */
        private void SerialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                string data = serialPort.ReadExisting();
                this.Invoke(new Action(() =>
                {
                    if (reception.ReceptionSignalFromString(data) == 1)
                    {
                        tbShape.Text = reception.m_tb_signal[0];
                        tbFreq.Text = reception.m_frequence.ToString();
                        tbAmp.Text = reception.m_amplitude.ToString();
                        tbOffset.Text = reception.m_offset.ToString();
                    }
                }));
            }
            catch (Exception ex)
            {
                this.Invoke(new Action(() =>
                    HandleSerialError("Erreur réception : " + ex.Message)));
            }
        }

        /* =============== Sliders / Preview =============== */
        private void UpdateFreqText(object sender, EventArgs e)
        {
            trBFreq.Value = (trBFreq.Value / 10) * 10;
            tbSendFreq.Text = trBFreq.Value.ToString();
        }
        private void UpdateAmpText(object sender, EventArgs e)
        {
            trBAmp.Value = (trBAmp.Value / 100) * 100;
            tbSendAmp.Text = trBAmp.Value.ToString();
        }
        private void UpdateOffsetText(object sender, EventArgs e)
        {
            trBOffset.Value = (trBOffset.Value / 100) * 100;
            tbSendOffset.Text = trBOffset.Value.ToString();
        }
        private void UpdateTramePreview(object sender, EventArgs e)
        {
            txtTrameToSend.Text = GenerateTrame();
        }

        /* ============== Génération trame ================ */
        private string GenerateTrame()
        {
            string forme;
            switch (cbNewShape.SelectedIndex)
            {
                case 0: forme = "S"; break;
                case 1: forme = "T"; break;
                case 2: forme = "C"; break;
                case 3: forme = "D"; break;
                default: forme = "X"; break;
            }

            string signeOffset = trBOffset.Value >= 0 ? "+" : "";
            //  string sauvegarde = chbSauvegarde.Checked ? "1" : "0";

            return $"!S={forme}F={trBFreq.Value}A={trBAmp.Value}O={signeOffset}{trBOffset.Value}W={(chbSauvegarde.Checked ? "1" : "0")}#";
        }

        /* =============== Classes Signal ================= */
        public class Signal
        {
            public ushort m_amplitude;
            public ushort m_frequence;
            public short m_offset;
            public string[] m_tb_signal;
            public virtual int EnvoiSignal() => 0;
            public virtual int ReceptionSignal() => 0;
        }

        public class Receive_Signal : Signal
        {
            public int ReceptionSignalFromString(string trame)
            {
                if (!trame.StartsWith("!") || !trame.EndsWith("#")) return -1;
                string contenu = trame.Trim('!', '#');

                string forme = Extract(contenu, "S=");
                string freq = Extract(contenu, "F=");
                string amp = Extract(contenu, "A=");
                string offset = Extract(contenu, "O=");

                switch (forme)
                {
                    case "S": 
                        m_tb_signal = new[] { "Sinus" }; 
                        break;
                    case "T": 
                        m_tb_signal = new[] { "Triangle" }; 
                        break;
                    case "C": 
                        m_tb_signal = new[] { "Carré" }; 
                        break;
                    case "D": 
                        m_tb_signal = new[] { "Dent de scie" }; 
                        break;
                    default: 
                        m_tb_signal = new[] { "Inconnu" }; 
                        break;
                }

                if (ushort.TryParse(freq, out ushort f)) m_frequence = f;
                if (ushort.TryParse(amp, out ushort a)) m_amplitude = a;
                if (short.TryParse(offset, out short o)) m_offset = o;
                return 1;
            }

            private static string Extract(string src, string tag)
            {
                int start = src.IndexOf(tag);
                if (start == -1) return "";
                start += tag.Length;

                int end = src.IndexOfAny(new[] { 'S', 'F', 'A', 'O', 'W', 'P', '#' }, start);
                while (end != -1 && (end + 1 >= src.Length || src[end + 1] != '='))
                    end = src.IndexOfAny(new[] { 'S', 'F', 'A', 'O', 'W', 'P', '#' }, end + 1);

                if (end == -1) end = src.Length;
                return src.Substring(start, end - start);
            }
        }
    }
}
