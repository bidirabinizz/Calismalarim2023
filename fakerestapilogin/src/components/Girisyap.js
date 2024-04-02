import { useState, useEffect } from "react";
import axios from "axios";
import Navbar from "./Navbar";
import girisyapmatheme from "./girisyaptheme.css"

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
        }
      }
    });
  }

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
          <div>
          
          <Navbar
            loggedInUsername={LoggedInUsername}
            MailAdress={mailAdress}
            logininfo={login}
          />
          
          
          <h1 className="denemeh1">Deneme</h1>
          
          </div>
        )}
     
  </div>
  );
  
}

export default Girisyap;
