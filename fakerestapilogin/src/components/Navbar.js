import React from "react";
import "./Navbar.css";
function Navbar({ loggedInUsername, MailAdress }) {
  return (
    <div className="navbar">
      <div>
        <p className="denemep">Hoş geldiniz, {loggedInUsername}!</p>
        <br />
        {/* <p className="denemep">Mail adresiniz : {null}</p> */}
      </div>
    </div>
  );
}

export default Navbar;
