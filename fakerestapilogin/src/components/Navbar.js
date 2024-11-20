import React from "react";
import "./Navbar.css";
import logoGorsel from "../img/baynosatisLogo.png";

function Navbar({ loggedInUsername, MailAdress, admininfo, logininfo }) {
  return (
    <div className="navbar">
      <div>
        {logininfo ? (
          <>
            <p className="denemep">Hoş geldiniz, {loggedInUsername}!</p>
            <span className="navbarLogo">
              <img src={logoGorsel} className="logoGorsel"></img>
            </span>
          </>
      
        ) : (
          console.log("deneme")
        )}

        <br />
        {/* <p className="denemep">Mail adresiniz : {null}</p> */}
      </div>
      {}

        
    </div>
  );
}

export default Navbar;
