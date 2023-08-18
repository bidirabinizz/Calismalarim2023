import { useState, useEffect } from "react";
import axios from "axios";

function App() {
  const [users, setUsers] = useState([]);
  const [error, setError] = useState(false);
  const [loading, setLoading] = useState(true);

  function veriYukle() {
    axios
      .get("https://jsonplaceholder.typicode.com/users")
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
    <div>
      <h1>Kullanıcılar</h1>
      {error && <h2>Sayfa yüklenemedi</h2>}
      {loading && <h2>Yükleniyor ...</h2>}
      {users.map((item) => (
        <h4>{item.name}</h4>
      ))}
    </div>
  );
}

export default App;
