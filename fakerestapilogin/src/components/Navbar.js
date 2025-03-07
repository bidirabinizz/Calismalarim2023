import React from "react";
import "./Navbar.css";
import logoGorsel from "../img/baynosatisLogo.png";
import {BrowserRouter as Router,
  Routes,
  Route,
  Link
} from "react-router-dom"

function Navbar({ loggedInUsername, MailAdress, admininfo, logininfo, setLogin, setUsername, setPassword }) {
  const handleLogout = () => {
    localStorage.removeItem("username");
    localStorage.removeItem("password");
  
    // Login durumunu sıfırla
    setLogin(false);
    setUsername("");
    setPassword("");
  };
  

  return (
    <div className="navbar">
   
      <div>
        
        {logininfo ? (
          <>
          
            <p className="denemep">Hoş geldiniz, {loggedInUsername}!</p>
            <span className="navbarLogo">
              <img src={logoGorsel} className="logoGorsel" alt="Logo" />
            </span>
            {/* Çıkış yap butonu */}
          <div className="logoutNavigation">
            <img src={logoGorsel} className="logoutImage" />
            <div onClick={handleLogout} className="logoutButton">
              Çıkış Yap
            </div>
          </div>
          
          </>
        ) : (
          <p>Sayfayı Lütfen Tekrar Yükleyiniz ve Giriş yapınız</p>
        )}
        <br />
      </div>
    </div>
  );
}

export default Navbar; 
