import React from "react";
import {
  BrowserRouter as Router,
  Routes,
  Route,
  Link
} from "react-router-dom";
import "./adminpanel.css";

export default function Adminpanel() {
  return (
    <Router>
      <nav className="adminPanelLink">
        <ul>
          <li>
            <Link to="/">Ana Sayfa</Link>
          </li>
          <li>
            <Link to="/gonderikontrol">Gönderi Kontrol</Link>
          </li>
          <li>
            <Link to="/kullanicilar">Kullanıcılar</Link>
          </li>
        </ul>
      </nav>

      <Routes>
        <Route path="/gonderikontrol" element={<GonderiKontrol />} />
        <Route path="/kullanicilar" element={<Kullanicilar />} />
        <Route path="/" element={<Anasayfa />} />
      </Routes>
    </Router>
  );
}

function GonderiKontrol() {
  return <h2>Sayfa Yönetimi</h2>;
}

function Kullanicilar() {
  return <h2>Kullanıcılar Sayfası</h2>;
}

function Anasayfa() {
  return <h2>Ana Sayfa</h2>;
}
