import { useState, useEffect } from "react";
import axios from "axios";

const userURL = "http://localhost:3000/kullanici";

function veriYukle() {
  axios
    .get(userURL)
    .then((item) => {
      console.log(item.data);
    })
    .catch(() => {})
    .finally(() => {});
}

function Girisyap() {
  const [users, setUsers] = useState([veriYukle()]);
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");
  const [login, setLogin] = useState(false);

  useEffect(() => {
    veriYukle();
  }, []);

  function butonTiklandi() {
    veriYukle();

    users.map((item) => {
      if (item.username == username) {
        if (item.password == password) {
          setLogin(true);
        }
      }
    });
  }

  return (
    <div className="maindiv">
      <h1>Giriş Yap</h1>
      {!login ? (
        <div>
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
          <button onClick={butonTiklandi}>Giriş Yap</button>
        </div>
      ) : (
        <h1>Giriş Yapıldı!</h1>
      )}
    </div>
  );
}

export default Girisyap;
