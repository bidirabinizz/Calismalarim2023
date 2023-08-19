import "./App.css";
import { useState, useEffect } from "react";
import axios from "axios";
import UserListCard from "./components/UserListCard";

function App() {
  const [users, setUsers] = useState([]);
  const [error, setError] = useState(false);
  const [loading, setLoading] = useState(true);

  let userURL = "https://jsonplaceholder.typicode.com/users";

  useEffect(() => {
    veriYukle();
  }, []);

  function veriYukle() {
    axios
      .get(userURL)
      .then((item) => {
        console.log(item.data);
        setUsers(item.data);
      })
      .catch(() => {
        setError(true);
      })
      .finally(() => {
        setLoading(false);
      });
  }

  return (
    <div className="mainDiv1">
      <h1>Kullanıcılar</h1>
      {error && <h2>Sayfa Yüklenemedi...</h2>}
      {loading && <h2>Yükleniyor...</h2>}
      {users.map((item) => (
        <UserListCard
          username={item.name}
          mail={item.email}
          company={item.company.name}
          location={item.address.street}
          phone={item.phone}
          loginname={item.username}
          website={item.website}
        ></UserListCard>
      ))}
    </div>
  );
}

export default App;
