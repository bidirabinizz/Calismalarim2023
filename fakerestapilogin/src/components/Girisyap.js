import { useState, useEffect } from "react";
import axios from "axios";
import Navbar from "./Navbar";
import Anasayfa from "./anasayfa";
import girisyapmatheme from "./girisyaptheme.css";
import ScrollReveal from "scrollreveal";

const userURL = "http://localhost:3000/kullanici"; // Fake API'nin URL'si

function Girisyap() {
  const [LoggedInUsername, setLoggedInUsername] = useState("");
  const [mailAdress, setMailAdress] = useState("");
  const [admin, setAdmin] = useState("");
  const [users, setUsers] = useState([]); // Kullanıcıları tutan state
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");
  const [login, setLogin] = useState(false);
  const [rememberMe, setRememberMe] = useState(false); // "Beni hatırla" durumu

  // İlk yükleme, kullanıcıları ve "Beni hatırla" bilgisini al
  useEffect(() => {
    const fetchUsers = async () => {
      try {
        const response = await axios.get(userURL);
        console.log("API'den gelen veri:", response.data);

        if (response.data && Array.isArray(response.data)) {
          setUsers(response.data);
        } else {
          console.error("Beklenen formatta veri gelmedi:", response.data);
        }
      } catch (error) {
        console.error("Kullanıcı verileri alınırken hata oluştu:", error);
      }
    };

    fetchUsers();

    // Sayfa yüklendiğinde "Beni hatırla" verilerini kontrol et
    const savedUsername = localStorage.getItem("username");
    const savedPassword = localStorage.getItem("password");
    const savedLoginStatus = localStorage.getItem("loginStatus");
    const savedLoggedInUsername = localStorage.getItem("loggedInUsername");

    if (savedUsername && savedPassword && savedLoginStatus === "true" && savedLoggedInUsername) {
      setUsername(savedUsername);
      setPassword(savedPassword);
      setLoggedInUsername(savedLoggedInUsername); // localStorage'dan kullanıcı adını al
      setLogin(true); // Otomatik giriş
    }
  }, []);

  // Giriş yap butonuna tıklanma işlemi
  function butonTiklandi() {
    console.log("Mevcut kullanıcılar:", users);
    console.log("Girilen kullanıcı adı:", username);
    console.log("Girilen şifre:", password);

    if (!users || users.length === 0) {
      alert("Kullanıcı verileri yükleniyor veya mevcut değil. Lütfen tekrar deneyin!");
      return;
    }
    
    // Kullanıcıyı doğrulama
    const user = users.find(
      (data) =>
        data.username === username &&
        String(data.password) === String(password)
    );

    if (user) {
      console.log("Giriş başarılı! Kullanıcı:", user);
      setLogin(true);
      setLoggedInUsername(user.fullname);
      setMailAdress(user.mail);
      setAdmin(user.admin);

      // "Beni hatırla" seçeneği aktifse, verileri localStorage'a kaydet
      if (rememberMe) {
        localStorage.setItem("username", username);
        localStorage.setItem("password", password);
        localStorage.setItem("loginStatus", "true");
        localStorage.setItem("loggedInUsername", user.fullname); // Kullanıcı adını da kaydediyoruz
      }
    } else {
      console.log("Giriş başarısız! Kullanıcı adı veya şifre hatalı.");
      alert("Kullanıcı adı veya şifre hatalı!");
    }
  }

  // Sayfa geçişi ve animasyon işlemi
  useEffect(() => {
    ScrollReveal().reveal(".container", {
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
                onChange={(e) => setUsername(e.target.value)}
                value={username}
                type="text"
                placeholder="Kullanıcı adı..."
              />
              <input
                onChange={(e) => setPassword(e.target.value)}
                value={password}
                type="password"
                placeholder="Şifre..."
              />
              <br />
              <label>
              Beni hatırla 
              <input
                  type="checkbox"
                  checked={rememberMe}
                  onChange={() => setRememberMe(!rememberMe)}
                  id="checkboxBeniHatirla"
                />  
              </label>
              <br />
              <button onClick={butonTiklandi} className="button">
                Giriş Yap
              </button>
            </div>
          </div>
        </div>
      ) : (
        <>
          <Navbar
            loggedInUsername={LoggedInUsername}
            MailAdress={mailAdress}
            logininfo={login}
            setLogin={setLogin} // Buraya ekledik
            setUsername={setUsername}
            setPassword={setPassword}
          />

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
