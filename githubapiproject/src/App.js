import { useState } from "react";
import axios from "axios";
import SearchItem from "./Compenent/SearchItem";

function App() {
  const [searchData, setSearchData] = useState([]);
  const [inputValue, setInputValue] = useState();

  const baseURL = "https://api.github.com/search/users?q=";

  function searchButton() {
    axios.get(baseURL + inputValue).then((res) => {
      setSearchData(res.data.items);
    });
  }
  return (
    <div>
      <h1>Github Search</h1>
      <input
        type="text"
        onChange={(e) => {
          setInputValue(e.target.value);
        }}
        value={inputValue}
        name=""
        id=""
        placeholder="Type Username..."
      />
      <button onClick={searchButton}>Search</button>

      {searchData.map((item) => (
        <SearchItem username={item.login} htmlLink={item.html_url}></SearchItem>
      ))}
    </div>
  );
}

export default App;
