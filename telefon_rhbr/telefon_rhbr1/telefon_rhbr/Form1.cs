using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace telefon_rhbr
{
    
    public partial class Form1 : Form
    {

        SqlConnection conn;
        SqlCommand cmd;
        SqlDataAdapter da;
        DataTable tablo;

       
        public Form1()
        {
            InitializeComponent();
        }

        void KisiGetir()
        {
            conn = new SqlConnection("Data Source=OGRENCI4\\SQLEXPRESS;Initial Catalog=telefonrehberidb; Integrated Security=True");
            da = new SqlDataAdapter("select * from kisiler", conn);
            tablo = new DataTable();
            conn.Open();
            da.Fill(tablo);
            grdkisiler.DataSource = tablo;
            conn.Close();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void groupBox2_Enter(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            MessageBox.Show("Başarılı bir şekilde açıldı");
        }

        private void ksGetir_Click(object sender, EventArgs e)
        {
            KisiGetir();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            string sorgu = "Insert into kisiler (ad,soyad,tel_no1,tel_no2) values (@ad,@soyad,@tel1,@tel2)";
            cmd = new SqlCommand(sorgu, conn);
            cmd.Parameters.AddWithValue("@ad", txtAd.Text);
            cmd.Parameters.AddWithValue("@soyad", txtSoyad.Text);
            cmd.Parameters.AddWithValue("@tel1", txtNumara1.Text);
            cmd.Parameters.AddWithValue("@tel2", txtNumara2.Text);
            conn.Open();
            cmd.ExecuteNonQuery();
            conn.Close();
            KisiGetir();


        }

        private void button4_Click(object sender, EventArgs e)
        {
            string sorgu = "DELETE kisiler Where kisi_id=@kisi_id";
            cmd = new SqlCommand(sorgu, conn);
            
            cmd.Parameters.AddWithValue("@kisi_id", grdkisiler.CurrentRow.Cells[0].Value);
            conn.Open();
            cmd.ExecuteNonQuery();
            conn.Close();
            KisiGetir();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            string sorgu = "Update Kisiler Set ad=@Ad,soyad=@Soyad,tel_no1=@tel_no1, tel_no2=@tel_no2 Where kisi_id=@kisi_id";
            cmd = new SqlCommand(sorgu, conn);
            cmd.Parameters.AddWithValue("@ad", txtAd.Text);
            cmd.Parameters.AddWithValue("@soyad", txtSoyad.Text);
            cmd.Parameters.AddWithValue("@tel_no1", txtNumara1.Text);
            cmd.Parameters.AddWithValue("@tel_no2", txtNumara2.Text);
            cmd.Parameters.AddWithValue("@kisi_id", grdkisiler.CurrentRow.Cells[0].Value);
            conn.Open();
            cmd.ExecuteNonQuery();
            conn.Close();
            KisiGetir();
        }
    }
}
