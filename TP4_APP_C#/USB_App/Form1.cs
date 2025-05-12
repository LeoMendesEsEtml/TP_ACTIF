using System;
using System.IO;
using System.IO.Ports;
using System.Windows.Forms;
using System.Collections.Generic;
using System.Linq;

namespace USB_App
{
    public partial class Form1 : Form // Déclaration de la classe Form1 héritant de Form (Windows Forms)
    {
        /* ================= Champs & init : inchangés ================= */
        private readonly SerialPort serialPort = new SerialPort(); // Objet SerialPort pour la communication série
        private readonly Receive_Signal reception = new Receive_Signal(); // Objet de réception basé sur la classe Receive_Signal
        private readonly Timer cyclicTimer = new Timer { Interval = 25 }; // Timer configuré pour déclencher toutes les 25 ms
        private bool isCyclicSending = false; // Booléen pour indiquer si l’envoi cyclique est actif
        private bool userAdjusting = false;   // vrai quand la souris est tenue sur un TrackBar
        private string lastSentCore = string.Empty; // trame sans W

        public Form1() // Constructeur de la classe Form1
        {
            cyclicTimer.Tick += CyclicTimer_Tick; // L’événement Tick du timer appelle CyclicTimer_Tick
            InitializeComponent(); // Initialise les composants graphiques du formulaire
            LoadAvailableComPorts(); // Charge les ports COM disponibles dans la liste

            gbRealParameter.Enabled = false; // Désactive le groupe d’affichage des paramètres reçus
            gbSendParameter.Enabled = false; // Désactive le groupe d’envoi des paramètres

            cbNewShape.Items.AddRange(new[] { "Sinus (S)", "Triangle (T)", "Carré (C)", "Dent de scie (D)" }); // Ajoute les formes disponibles dans la ComboBox
            cbNewShape.SelectedIndex = 0; // Sélectionne la première forme par défaut (Sinus)

            trBFreq.Minimum = 20; trBFreq.Maximum = 2000; trBFreq.TickFrequency = 100; // Paramètre le TrackBar de fréquence
            trBAmp.Minimum = 0; trBAmp.Maximum = 10000; trBAmp.TickFrequency = 100; // Paramètre le TrackBar d'amplitude
            trBOffset.Minimum = -5000; trBOffset.Maximum = 5000; trBOffset.TickFrequency = 100; // Paramètre le TrackBar d'offset

            trBFreq.Value = trBFreq.Minimum; // Initialise la fréquence au minimum
            trBAmp.Value = trBAmp.Minimum; // Initialise l’amplitude au minimum
            trBOffset.Value = 0; // Initialise l’offset à 0

            /* Handlers habillés (identiques) */
            bOpen.Click += bOpen_Click; // Associe le clic du bouton d'ouverture à la fonction bOpen_Click
            bclose.Click += bClose_Click; // Associe le clic du bouton de fermeture à la fonction bClose_Click
            bSending.Click += bSending_Click; // Associe le clic du bouton d’envoi à la fonction bSending_Click
            brefresh.Click += brefresh_Click; // Associe le clic du bouton de rafraîchissement à la fonction brefresh_Click

            cbNewShape.SelectedIndexChanged += (s, e) => { UpdateTramePreview(s, e); }; // Met à jour la trame quand on change la forme
            trBFreq.Scroll += (s, e) => { UpdateFreqText(s, e); UpdateTramePreview(s, e); }; // Met à jour texte + trame lors du scroll sur fréquence
            trBAmp.Scroll += (s, e) => { UpdateAmpText(s, e); UpdateTramePreview(s, e); }; // Met à jour texte + trame lors du scroll sur amplitude
            trBOffset.Scroll += (s, e) => { UpdateOffsetText(s, e); UpdateTramePreview(s, e); }; // Met à jour texte + trame lors du scroll sur offset
            chbSauvegarde.CheckedChanged += UpdateTramePreview; // Met à jour la trame quand la case de sauvegarde change

            trBFreq.MouseDown += Slider_MouseDown; // Détecte l’appui souris sur le TrackBar de fréquence
            trBFreq.MouseUp += Slider_MouseUp; // Détecte le relâchement souris sur le TrackBar de fréquence
            trBAmp.MouseDown += Slider_MouseDown; // Détecte l’appui souris sur le TrackBar d’amplitude
            trBAmp.MouseUp += Slider_MouseUp; // Détecte le relâchement souris sur le TrackBar d’amplitude
            trBOffset.MouseDown += Slider_MouseDown; // Détecte l’appui souris sur le TrackBar d’offset
            trBOffset.MouseUp += Slider_MouseUp; // Détecte le relâchement souris sur le TrackBar d’offset

            UpdateFreqText(null, null); // Initialise l’affichage de la fréquence
            UpdateAmpText(null, null); // Initialise l’affichage de l’amplitude
            UpdateOffsetText(null, null); // Initialise l’affichage de l’offset
            UpdateTramePreview(null, null); // Met à jour la prévisualisation initiale de la trame
            bCyclicSending.Enabled = false; // Désactive le bouton d’envoi cyclique au lancement
        }

        /* ================= Connexion ================= */
        private void bOpen_Click(object sender, EventArgs e) // Gestion du clic sur le bouton d'ouverture de connexion
        {
            try // Bloc de traitement avec capture d'erreur
            {
                if (cbComPort.SelectedItem == null) // Vérifie si un port a été sélectionné dans la ComboBox
                {
                    MessageBox.Show("Aucun port sélectionné."); // Affiche un message d'erreur si aucun port sélectionné
                    return; // Interrompt la fonction
                }

                if (!serialPort.IsOpen) // Si le port série n'est pas déjà ouvert
                {
                    serialPort.PortName = cbComPort.SelectedItem.ToString(); // Définit le nom du port sélectionné
                    serialPort.BaudRate = 57600; // Définit la vitesse de transmission (baudrate)
                    serialPort.DataBits = 8; // Définit le nombre de bits de données
                    serialPort.Parity = Parity.None; // Définit la parité (aucune)
                    serialPort.StopBits = StopBits.One; // Définit le nombre de bits de stop (1)
                    serialPort.DataReceived += SerialPort_DataReceived; // Associe la méthode de réception des données
                    serialPort.Open(); // Ouvre la connexion série

                    gbRealParameter.Enabled = true; // Active le groupe des paramètres reçus
                    gbSendParameter.Enabled = true; // Active le groupe des paramètres à envoyer
                    bOpen.Enabled = false; // Désactive le bouton d'ouverture
                    cbComPort.Enabled = false; // Désactive la sélection du port COM
                    bclose.Enabled = true; // Active le bouton de fermeture
                    bSending.Enabled = true; // Active le bouton d'envoi manuel
                    bCyclicSending.Enabled = true; // Active le bouton d'envoi cyclique
                    brefresh.Enabled = false; // Désactive le bouton de rafraîchissement
                }
            }
            catch (Exception ex) // Capture toute exception levée pendant la tentative d'ouverture
            {
                MessageBox.Show("Erreur connexion : " + ex.Message); // Affiche le message d'erreur
            }
        }

        private void Slider_MouseDown(object sender, MouseEventArgs e) // Détection de l’appui souris sur un TrackBar
        {
            if (isCyclicSending) userAdjusting = true;   // on gèle l’envoi si le mode cyclique est actif
        }

        private void Slider_MouseUp(object sender, MouseEventArgs e) // Détection du relâchement souris sur un TrackBar
        {
            if (!isCyclicSending) return; // si l’envoi cyclique est inactif, on quitte la fonction

            userAdjusting = false;       // on libère l’envoi (reprise du timer)

            /* Forcer UNE sauvegarde au prochain tick */
            chbSauvegarde.Checked = true; // coche la case pour forcer une trame avec W=1
            lastSentCore = "";           // vide la dernière trame envoyée pour forcer une mise à jour
        }

        private void bClose_Click(object sender, EventArgs e) // Gestion du clic sur le bouton de fermeture
        {
            try { if (serialPort.IsOpen) serialPort.Close(); } // Tente de fermer le port série s’il est ouvert
            catch { } // Ignore toute exception

            StopCyclic(); // Arrête l’envoi cyclique
            ResetUI(); // Réinitialise l’état de l’interface graphique
            LoadAvailableComPorts(); // Recharge la liste des ports disponibles
        }

        /* ================= Reset complet (UI + états) ================= */
        private void ResetUI() // Réinitialise l’interface utilisateur et les états internes
        {
            cyclicTimer.Stop(); // Arrête le timer d’envoi cyclique
            isCyclicSending = false; // Réinitialise l’état d’envoi cyclique
            bCyclicSending.Text = "Envois cyclique"; // Remet le texte du bouton d’envoi cyclique
            bCyclicSending.Enabled = false; // Désactive le bouton d’envoi cyclique

            cbComPort.Enabled = true; // Réactive la sélection du port COM
            bOpen.Enabled = true; // Réactive le bouton d’ouverture
            bclose.Enabled = false; // Désactive le bouton de fermeture
            bSending.Enabled = false; // Désactive le bouton d’envoi
            brefresh.Enabled = true; // Réactive le bouton de rafraîchissement

            gbRealParameter.Enabled = false; // Désactive le groupe des paramètres reçus
            gbSendParameter.Enabled = false; // Désactive le groupe des paramètres envoyés

            tbShape.Clear(); tbFreq.Clear(); tbAmp.Clear(); tbOffset.Clear(); // Efface tous les champs texte de paramètres
            trBFreq.Value = trBFreq.Minimum; // Réinitialise le TrackBar de fréquence à sa valeur minimale
            trBAmp.Value = trBAmp.Minimum; // Réinitialise le TrackBar d’amplitude à sa valeur minimale
            trBOffset.Value = 0; // Réinitialise le TrackBar d’offset à 0
            chbSauvegarde.Checked = false; // Décoche la case de sauvegarde

            UpdateFreqText(null, null); // Met à jour l’affichage texte de la fréquence
            UpdateAmpText(null, null); // Met à jour l’affichage texte de l’amplitude
            UpdateOffsetText(null, null); // Met à jour l’affichage texte de l’offset
            UpdateTramePreview(null, null); // Met à jour la trame de prévisualisation
        }

        /* ================= Gestion d’erreur série ================= */
        private void HandleSerialError(string message) // Gère les erreurs liées au port série
        {
            MessageBox.Show(message, "USB App", MessageBoxButtons.OK, MessageBoxIcon.Warning); // Affiche un message d’avertissement à l’utilisateur
            try { if (serialPort.IsOpen) serialPort.Close(); } catch { } // Tente de fermer le port série s’il est ouvert (ignore les erreurs)
            ResetUI(); // Réinitialise complètement l’interface et les états
            LoadAvailableComPorts(); // Recharge la liste des ports disponibles
        }

        /* ================= Envoi manuel =================== */
        private void bSending_Click(object sender, EventArgs e) // Gestion du clic sur le bouton d’envoi manuel
        {
            if (!serialPort.IsOpen) return; // Ne fait rien si le port série n’est pas ouvert
            try { serialPort.WriteLine(GenerateTrame()); } // Tente d’envoyer la trame générée via le port série
            catch (Exception ex) { HandleSerialError("Erreur d'envoi : " + ex.Message); } // En cas d’erreur, gère proprement via HandleSerialError
        }

        /* ================ Bouton cyclique ================= */
        private void bCyclicSending_Click(object sender, EventArgs e) // Gestion du clic sur le bouton d’envoi cyclique
        {
            if (!serialPort.IsOpen) // Si le port série n’est pas ouvert
            {
                MessageBox.Show("Le port série n'est pas ouvert."); // Avertit l’utilisateur
                return; // Quitte la fonction
            }

            if (isCyclicSending) StopCyclic(); // Si l’envoi est actif, on l’arrête
            else StartCyclic(); // Sinon, on le démarre
        }

        private void StartCyclic() // Active l’envoi cyclique
        {
            if (isCyclicSending) return; // Ne rien faire si déjà actif
            serialPort.DiscardOutBuffer(); // Vide le tampon de sortie série
            cyclicTimer.Start(); // Démarre le timer cyclique
            isCyclicSending = true; // Indique que l’envoi est actif
            bCyclicSending.Text = "Stop"; // Modifie le texte du bouton
        }

        private void StopCyclic() // Arrête l’envoi cyclique
        {
            cyclicTimer.Stop(); // Stoppe le timer cyclique
            isCyclicSending = false; // Indique que l’envoi est inactif
            bCyclicSending.Text = "Envois cyclique"; // Remet le texte initial du bouton
        }

        private void CyclicTimer_Tick(object sender, EventArgs e) // Fonction appelée à chaque tick du timer cyclique
        {
            if (!serialPort.IsOpen) // Si le port n’est plus ouvert
            {
                StopCyclic(); ResetUI(); LoadAvailableComPorts(); // Réinitialise l’UI
                return; // Quitte
            }

            if (userAdjusting) return;   // Toujours aucun envoi pendant déplacement

            string trame = GenerateTrame(); // Génère la trame actuelle
            int idx = trame.IndexOf("W="); // Cherche la position du champ W=
            string core = idx > -1 ? trame.Substring(0, idx) : trame; // Extrait la trame sans W

            /* ---- NOUVEAUTÉ : si la valeur stabilisée a changé, on force W=1 ---- */
            if (core != lastSentCore) // Si la trame a changé
                chbSauvegarde.Checked = true;   // autorise UNE sauvegarde la prochaine fois
            /* -------------------------------------------------------------------- */

            bool needSend = chbSauvegarde.Checked || core != lastSentCore; // Envoi requis si W=1 ou si changement
            if (!needSend) return;        // rien à envoyer

            try
            {
                serialPort.WriteLine(trame); // Envoie la trame par le port série
                lastSentCore = core;      // mémorise la dernière trame sans W

                if (chbSauvegarde.Checked)
                    chbSauvegarde.Checked = false; // W=1 envoyé → on décoche
            }
            catch (Exception ex) { HandleSerialError("Envoi cyclique : " + ex.Message); } // Gère toute erreur série
        }

        /* ================= Refresh COM =================== */
        private void brefresh_Click(object sender, EventArgs e) => LoadAvailableComPorts(); // Recharge la liste des ports COM disponibles

        private void LoadAvailableComPorts() // Recharge et filtre les ports COM disponibles et valides
        {
            string[] allPorts = SerialPort.GetPortNames();     // tous les noms de ports détectés sur le système
            List<string> validPorts = new List<string>(); // Liste des ports réellement accessibles

            foreach (string port in allPorts) // Parcourt chaque port détecté
            {
                // Teste rapidement si le port répond : s’il n’existe plus ou qu’il est
                // déjà ouvert par un driver zombie, Open() lèvera une exception.
                try
                {
                    using (SerialPort test = new SerialPort(port)) // Crée une instance temporaire du port
                    {
                        test.Open(); // Tente de l’ouvrir
                        test.Close(); // Et de le refermer immédiatement
                        validPorts.Add(port);                 // port réellement présent et utilisable
                    }
                }
                catch
                {
                    /* fantôme => ignoré */ // Ports inaccessibles ignorés silencieusement
                }
            }

            // Nettoie et recharge la ComboBox sans doublons
            string selected = cbComPort.SelectedItem as string; // Sauvegarde l'élément sélectionné, si présent

            cbComPort.BeginUpdate(); // Suspension du rafraîchissement visuel de la ComboBox
            cbComPort.Items.Clear(); // Vide les éléments existants
            foreach (string p in validPorts.Distinct(StringComparer.OrdinalIgnoreCase)) // Ajoute chaque port valide sans doublon
                cbComPort.Items.Add(p);
            cbComPort.EndUpdate(); // Reprise du rafraîchissement visuel

            // Restaure la sélection si possible
            if (selected != null && cbComPort.Items.Contains(selected)) // Si l’élément précédemment sélectionné est toujours présent
                cbComPort.SelectedItem = selected; // Le réapplique
            else if (cbComPort.Items.Count > 0) // Sinon, sélectionne le premier port disponible
                cbComPort.SelectedIndex = 0;
            else
                cbComPort.Text = "Aucun port valide"; // Aucun port détecté : message par défaut
        }

        /* ================== Réception ==================== */
        private void SerialPort_DataReceived(object sender, SerialDataReceivedEventArgs e) // Événement déclenché à la réception de données série
        {
            try
            {
                string data = serialPort.ReadExisting(); // Lit toutes les données disponibles du port série
                this.Invoke(new Action(() => // Invocation sur le thread UI (sécurité thread)
                {
                    if (reception.ReceptionSignalFromString(data) == 1) // Si la trame reçue est valide
                    {
                        tbShape.Text = reception.m_tb_signal[0]; // Affiche la forme du signal
                        tbFreq.Text = reception.m_frequence.ToString(); // Affiche la fréquence reçue
                        tbAmp.Text = reception.m_amplitude.ToString(); // Affiche l’amplitude reçue
                        tbOffset.Text = reception.m_offset.ToString(); // Affiche l’offset reçu
                    }
                }));
            }
            catch (Exception ex) // Si une exception est levée pendant la lecture
            {
                this.Invoke(new Action(() => // Affichage de l’erreur sur le thread UI
                    HandleSerialError("Erreur réception : " + ex.Message)));
            }
        }

        /* =============== Sliders / Preview =============== */
        private void UpdateFreqText(object sender, EventArgs e) // Met à jour l’affichage de la fréquence envoyée
        {
            trBFreq.Value = (trBFreq.Value / 10) * 10; // Arrondi à la dizaine inférieure
            tbSendFreq.Text = trBFreq.Value.ToString(); // Affiche la fréquence dans la TextBox
        }

        private void UpdateAmpText(object sender, EventArgs e) // Met à jour l’affichage de l’amplitude envoyée
        {
            trBAmp.Value = (trBAmp.Value / 100) * 100; // Arrondi à la centaine inférieure
            tbSendAmp.Text = trBAmp.Value.ToString(); // Affiche l’amplitude dans la TextBox
        }

        private void UpdateOffsetText(object sender, EventArgs e) // Met à jour l’affichage de l’offset envoyé
        {
            trBOffset.Value = (trBOffset.Value / 100) * 100; // Arrondi à la centaine inférieure
            tbSendOffset.Text = trBOffset.Value.ToString(); // Affiche l’offset dans la TextBox
        }

        private void UpdateTramePreview(object sender, EventArgs e) // Met à jour la trame affichée dans le champ de prévisualisation
        {
            txtTrameToSend.Text = GenerateTrame(); // Affiche la trame actuelle calculée à partir des sliders
        }

        /* ============== Génération trame ================ */
        private string GenerateTrame() // Construit la trame à envoyer en fonction des valeurs UI
        {
            string forme; // Variable pour stocker la lettre correspondant à la forme sélectionnée
            switch (cbNewShape.SelectedIndex) // Sélection selon l'index de la ComboBox
            {
                case 0: forme = "S"; break; // Sinus
                case 1: forme = "T"; break; // Triangle
                case 2: forme = "C"; break; // Carré
                case 3: forme = "D"; break; // Dent de scie
                default: forme = "X"; break; // Forme inconnue (sécurité)
            }

            string signeOffset = trBOffset.Value >= 0 ? "+" : ""; // Ajoute un + explicite si l’offset est positif

            //  string sauvegarde = chbSauvegarde.Checked ? "1" : "0"; // Ligne commentée inutile ici (non utilisée)

            return $"!S={forme}F={trBFreq.Value}A={trBAmp.Value}O={signeOffset}{trBOffset.Value}W={(chbSauvegarde.Checked ? "1" : "0")}#";
            // Retourne la trame complète au format requis, avec tous les champs concaténés
        }

        /* =============== Classes Signal ================= */
        public class Signal // Classe de base contenant les attributs communs à tous les signaux
        {
            public ushort m_amplitude; // Amplitude du signal
            public ushort m_frequence; // Fréquence du signal
            public short m_offset; // Offset du signal
            public string[] m_tb_signal; // Forme du signal (chaîne descriptive)

            public virtual int EnvoiSignal() => 0; // Méthode virtuelle d’envoi (à surcharger)
            public virtual int ReceptionSignal() => 0; // Méthode virtuelle de réception (à surcharger)
        }

        public class Receive_Signal : Signal // Classe héritée pour réception de trames
        {
            public int ReceptionSignalFromString(string trame) // Convertit une trame texte en paramètres internes
            {
                if (!trame.StartsWith("!") || !trame.EndsWith("#")) return -1; // Vérifie les bornes de la trame
                string contenu = trame.Trim('!', '#'); // Supprime les délimiteurs

                string forme = Extract(contenu, "S="); // Extrait le type de signal
                string freq = Extract(contenu, "F="); // Extrait la fréquence
                string amp = Extract(contenu, "A="); // Extrait l’amplitude
                string offset = Extract(contenu, "O="); // Extrait l’offset

                switch (forme) // Affecte une description selon la forme reçue
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

                if (ushort.TryParse(freq, out ushort f)) m_frequence = f; // Conversion fréquence
                if (ushort.TryParse(amp, out ushort a)) m_amplitude = a; // Conversion amplitude
                if (short.TryParse(offset, out short o)) m_offset = o; // Conversion offset
                return 1; // Indique que la trame a été traitée correctement
            }

            private static string Extract(string src, string tag) // Extrait la valeur associée à un tag dans la trame
            {
                int start = src.IndexOf(tag); // Recherche du début du tag
                if (start == -1) return ""; // Tag non trouvé
                start += tag.Length; // Décale au début de la valeur

                int end = src.IndexOfAny(new[] { 'S', 'F', 'A', 'O', 'W', 'P', '#' }, start); // Cherche le début du prochain champ
                while (end != -1 && (end + 1 >= src.Length || src[end + 1] != '=')) // Vérifie que le caractère trouvé est bien un tag
                    end = src.IndexOfAny(new[] { 'S', 'F', 'A', 'O', 'W', 'P', '#' }, end + 1); // Poursuit la recherche

                if (end == -1) end = src.Length; // Si aucun autre champ trouvé, prendre jusqu’à la fin
                return src.Substring(start, end - start); // Retourne la sous-chaîne extraite
            }
        }
    }
}
