import React, {useState, useEffect} from 'react'
import "./anasayfa.css"
import ScrollReveal from "scrollreveal";
import axios from "axios";
import Adminpanel from "./adminpanel";





function Anasayfa({loggedInUsername, MailAdress, Admin}) {

    const userURL = "http://localhost:3000/kullanici";

    const [users, setUsers] = useState(null);
    const [adminGirisDurum, setAdminGirisDurum] = useState(null);
    const [adminGiris, setAdminGiris] = useState("Admin Giriş Durumu : ");

    function girisBasarisizFunc(){
        <div>Giriş Başarısız</div>    
    }

    function kullaniciGetir(){
        users.map((data) => {
            console.log(data.username);
        });


    }

    function adminGirisKontrol(Admin) {
        const notification = document.getElementById("adminNotification");

        // Var olan timeout'u temizle
        if (window.notificationTimeout) {
            clearTimeout(window.notificationTimeout);
        }

        // Bildirimi yeniden başlat
        notification.style.opacity = 1;
        notification.style.display = "block";

        if (Admin === true) {
            console.log("başarılı");
            setAdminGiris("Admin Giriş Durumu : Başarılı");

            // Bildirim ayarları (Başarılı)
            notification.textContent = "Admin girişi başarılı.";
            notification.className = "notification success show";

            // Admin Giriş Durumu Başarılıysa Admin Kontrol Paneli Açılır (Başarılı)
            setAdminGirisDurum(true);

            kullaniciGetir()


        } else {
            console.log(Admin)
            setAdminGiris("Admin Giriş Durumu : Başarısız");
            console.log("Admin Giriş Durumu : Başarısız");

            // Bildirim ayarları (Başarısız)
            notification.textContent = "Admin girişi başarısız.";
            notification.className = "notification error show";

            // Admin Giriş Durumu Başarısızsa Admin Kontrol Paneli Açılmaz ve kullanıcı taraflı menü açılır (Başarısız)
            setAdminGirisDurum(false);
        }


        // ScrollReveal ile sağdan sola kaydırma efekti
        ScrollReveal().reveal('#adminNotification', {
            delay: 100,
            duration: 800,
            origin: 'right', // Sağdan
            distance: '100px', // 100px sağdan sola kayacak
            easing: 'ease-in-out',
            reset: true
        });

        // Bildirimi 3 saniye sonra yavaş yavaş gizle
        window.notificationTimeout = setTimeout(() => {
            notification.style.transition = "opacity 1s ease-out"; // Yavaş yavaş kaybolsun
            notification.style.opacity = 0;

            // Opaklık geçişi tamamlandıktan sonra tamamen gizle
            setTimeout(() => {
                notification.style.display = "none";
            }, 1000); // 1 saniyelik geçişten sonra gizle
        }, 3000); // Bildirim 3 saniye sonra kaybolmaya başlayacak
    }



    useEffect(() => {
        ScrollReveal().reveal('.anasayfaortala', {
            delay: 600,
            opacity: 0,
            distance: "20px",
            origin: "top",
            scale: 0.3,
        });
    }, []);


    //Kullanıcılar arkaplanda listelendi
    useEffect(() => {
        fetch(userURL)
            .then((res) => {
                return res.json();
            })
            .then((data) => {
                setUsers(data);
            });
    }, []);

  return (
    <div className='anasayfadeneme'>
        <div className='anasayfaortala'>
            <br></br>
            <span>Hoşgeldiniz, {loggedInUsername} </span>
            <div>Mail Adres, {MailAdress}</div>


            <div>Admin Yetkisi : {Admin ? <span>Admin Girişi Yaptınız</span> : <span>Admin Değilsiniz</span>}</div>
            <button onClick={() => adminGirisKontrol(Admin)}>Admin Girişi Test</button>


            <div id="adminNotification" className="notification" style={{display: 'none'}}></div>

            <div>{adminGiris}</div>

            {adminGirisDurum ? <div>
               
              
                <Adminpanel/>
            </div> : girisBasarisizFunc()}

        </div>
    </div>
  )
}

export default Anasayfa



