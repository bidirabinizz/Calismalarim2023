import { useState } from "react";
import axios from "axios";
import ListOfSearch from "../compenent/ListOfSearch";
import "../index.css";
function Home() {
  const [input1value, setinput1value] = useState("");
  const [searhResoult, setsearhResoult] = useState([]);
  const [searchNotFound, setsearchNotFound] = useState(false);

  const userURL = "https://www.thecocktaildb.com/api/json/v1/1/search.php?s=";
  const searchClick = () => {
    axios
      .get(userURL + input1value)
      .then((item) => {
        if (item.data.drinks == null) {
          setsearhResoult([]);
          setsearchNotFound(true);
        } else {
          setsearhResoult(item.data.drinks);
          setsearchNotFound(false);
        }
      })
      .catch((error) => {
        console.log(error);
      });
  };
  return (
    <>
      <h3>Search Coctails</h3>
      <input
        type="text"
        name=""
        id=""
        onChange={(e) => setinput1value(e.target.value)}
        value={input1value}
        placeholder="Kokteyl Ara"
      />
      <button onClick={searchClick}>Search</button>
      <br />
      {searchNotFound && <h1>Search Not Found</h1>}
      {searhResoult.map((res, index) => (
        <ListOfSearch
          key={index}
          title={res.strDrink}
          imgURL={res.strDrinkThumb}
        />
      ))}
    </>
  );
}

export default Home;
