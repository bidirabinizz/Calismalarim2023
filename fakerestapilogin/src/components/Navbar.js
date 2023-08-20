import React from "react";
import "./Navbar.css";
function Navbar({ loggedInUsername, MailAdress }) {
  return (
    <div className="navbar">
      <p className="denemep">Hoş geldiniz, {loggedInUsername}!</p>
      <p className="denemep">Mail adresiniz : {MailAdress}</p>
    </div>
  );
}

export default Navbar;
