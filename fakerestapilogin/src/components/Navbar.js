import React from "react";
import "./Navbar.css";
function Navbar({ loggedInUsername, MailAdress, admininfo, logininfo }) {
  return (
    <div className="navbar">
      <div>
        {logininfo ? (
          <div>
            <p className="denemep">Hoş geldiniz, {loggedInUsername}!</p>
          </div>
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
