import React, { useEffect, useState } from "react";
import {
  BrowserRouter as Router,
  Routes,
  Route,
  Link
} from "react-router-dom";

/* Scroll Reveal animasyon eklentisi */
import ScrollReveal from "scrollreveal";
import "./adminpanel.css";

export default function Adminpanel() {
  const userURL = "http://localhost:3000/kullanici";
  const [users, setUsers] = useState([]); // Kullanıcıları tutmak için state

  useEffect(() => {
    // Verileri sayfa yüklenirken çekiyoruz
    fetch(userURL)
      .then((res) => res.json())
      .then((data) => {
        setUsers(data);
      });
  }, []);

  return (
    <Router>
      <nav className="adminPanelLink">
        <ul>
          <li>
            <Link to="/gonderikontrol">Gönderi Kontrol</Link>
          </li>
          <li>
            <Link to="/kullanicilar">Kullanıcılar</Link>
          </li>
          <li>
            <Link to="/yamanotlari">Yama Notları</Link>
          </li>
          <li>
            <Link to="/">Anasayfa</Link>
          </li>
        </ul>
      </nav>

      <Routes>
        <Route path="/gonderikontrol" element={<GonderiKontrol />} />
        <Route path="/kullanicilar" element={<Kullanicilar users={users} />} />
        <Route path="/yamanotlari" element={<Yamanotlari />} />
        <Route path="/" element={<Anasayfa />} />
      </Routes>
    </Router>
  );
}

 // ScrollReveal ile sağdan sola kaydırma efekti
 ScrollReveal().reveal('.denemeparagraf', {
  delay: 100,
  duration: 800,
  origin: 'right', // Sağdan
  distance: '100px', // 100px sağdan sola kayacak
  easing: 'ease-in-out',
  reset: true
});


/* Admin Gönderi Kontrol Paneli - Gönderilen Gönderileri Kontrol Etmek için */
function GonderiKontrol() {
  return (
    <>
      <h2>Gönderi Kontrol Sayfası</h2>
    </>
  );
}

/* Kullanıcı Ekleme Silme Güncelleme Sıralama gibi işlemleri buradan yapmak için oluşturuldu */
function Kullanicilar({ users }) {
  const [showUsers, setShowUsers] = useState(false); // Kullanıcıları göster/gizle kontrolünn yapıldığı yer

  const handleButtonClick = () => {
    setShowUsers(true); // Butona tıklanınca kullanıcıları göstermek için yaptım
  };

  console.log(users);

  return (
    <div>
      <h2>Kullanıcılar Sayfası</h2>
      <button onClick={handleButtonClick}>Kullanıcıları Listele</button>

      {showUsers && (
        <ul className="KullanicilarListelemeDuzen">
          {users.length > 0 ? (
            users.map((user) => (
              <li key={user.id}>
                <p>Adı Soyadı : {user.fullname}</p>
                <p>Kullanıcı Adı: {user.username}</p>
                <p>Email: {user.mail}</p>
                <p>Bilinen Diller : {" "+ user.language} </p>
                
              </li>
             
            ))
          
          ) : (
            <p>Kayıtlı Kullanıcı Bulunamadı.</p>
            
          )}
        </ul>
      )}
    </div>
  );
}

function Anasayfa() {
  return <div>
    <h2>Ana Sayfa</h2>
    <p className="denemeparagraf"> Deneme Paragraf </p>
  </div>;
}

/* Eğer yeni bir router eklemek istersem baş harfleri büyük olmak zorunda */
function Yamanotlari() {
  return <h2>Yama Notları</h2>;
}
