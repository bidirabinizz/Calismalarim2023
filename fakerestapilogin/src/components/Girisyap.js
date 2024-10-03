import { useState, useEffect } from "react";
import axios from "axios";
import Navbar from "./Navbar";
import Anasayfa from "./anasayfa"
import girisyapmatheme from "./girisyaptheme.css"
import ScrollReveal from "scrollreveal";

const userURL = "http://localhost:3000/kullanici";

function Girisyap() {
  const [LoggedInUsername, setLoggedInUsername] = useState("");
  const [mailAdress, setMailAdress] = useState("");
  const [admin, setAdmin] = useState("");
  const [users, setUsers] = useState(null);
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");
  const [login, setLogin] = useState(false);

  useEffect(() => {
    fetch(userURL)
      .then((res) => {
        return res.json();
      })
      .then((data) => {
        setUsers(data);
      });
  }, []);

  function butonTiklandi() {
    users.map((data) => {
      if (data.username == username) {
        if (data.password == password) {
          setLogin(true);
          setLoggedInUsername(data.fullname);
          setMailAdress(data.mail);
          setAdmin(data.admin);

        }
      }
    });
  }

  useEffect(() => {
    ScrollReveal().reveal('.container', {
      delay: 600,
      opacity: 0,
      distance: "20px",
      origin: "top",
      scale: 0.3,
    });
  }, []);

  return (
  <div className="deneme">
    
        {!login ? (
          <div>
            <div className="container">
             <div className="maindiv">
            <h1>Giriş Yap</h1>
            <input
              onChange={(e) => {
                setUsername(e.target.value);
              }}
              value={username}
              type="text"
              name=""
              id=""
              placeholder="kullanıcı adı..."
            />
            <input
              onChange={(e) => {
                setPassword(e.target.value);
              }}
              value={password}
              type="password"
              name=""
              id=""
              placeholder="şifre..."
            />

            <br></br> 
            
            <button onClick={butonTiklandi} className="button">Giriş Yap</button>
          </div>
           </div>
           </div>
          
        ) : (
          <>
          <div>
          <Navbar
            loggedInUsername={LoggedInUsername}
            MailAdress={mailAdress}
            logininfo={login}
          />
          
          
          </div>
          
          <Anasayfa
            loggedInUsername={LoggedInUsername}
            MailAdress={mailAdress}
            Admin={admin}
          />
          
          </>
        )}
     
  </div>
  );
  
}

export default Girisyap;
