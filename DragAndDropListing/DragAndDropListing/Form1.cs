using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Windows.Forms;

namespace DragAndDropListing
{
    public partial class Form1 : Form
    {

        int appendixIndex = 0;

        public Form1()
        {
            InitializeComponent();
        }

        interface IPdfCreator
        {
            

        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void panel1_DragDrop(object sender, DragEventArgs e)
        {
            string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);
            foreach (string file in files) copyFile(file);
        }

        private void panel1_DragEnter(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop)) e.Effect = DragDropEffects.Copy;
        }

        private void label1_Click(object sender, EventArgs e)
        {
            OpenFileDialog fileDialog = new OpenFileDialog();
            fileDialog.Multiselect = true;
            fileDialog.ShowDialog();
            foreach(string fileName in fileDialog.FileNames) copyFile(fileName);
        }

        private void copyFile(string path)
        {
            try
            {
                string[] splitPath = path.Split('\\');
                string targetPath = tbBrowse.Text + "\\[" + appendixIndex++ + "] " + splitPath.Last<string>();
                COM
                File.Copy(path, targetPath, true);
                File.SetAttributes(targetPath, FileAttributes.Normal);
            }
            catch (DirectoryNotFoundException) {}
            catch (UnauthorizedAccessException){}
        }

        private void btBrowse_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog browserDialog = new FolderBrowserDialog();
            browserDialog.ShowDialog();
            tbBrowse.Text = browserDialog.SelectedPath;
        }
    }
}
