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
  const [showUsers, setShowUsers] = useState(false); // Kullanıcıları göster/gizle kontrolü

  const handleButtonClick = () => {
    setShowUsers(true); // Butona tıklanınca kullanıcıları göster
  };

  return (
    <div>
      <h2>Kullanıcılar Sayfası</h2>
      <button onClick={handleButtonClick}>Kullanıcıları Listele</button>

      {showUsers && (
        <ul>
          {users.length > 0 ? (
            users.map((user) => (
              <li key={user.id}>
                <p>Kullanıcı Adı: {user.username}</p>
                <p>Email: {user.email}</p>
              </li>
            ))
          ) : (
            <p>Kullanıcı bulunamadı.</p>
          )}
        </ul>
      )}
    </div>
  );
}

function Anasayfa() {
  return <h2>Ana Sayfa</h2>;
}

/* Eğer yeni bir router eklemek istersem baş harfleri büyük olmak zorunda */
function Yamanotlari() {
  return <h2>Yama Notları</h2>;
}
