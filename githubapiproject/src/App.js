import { useState } from "react";

function App() {
  const [InputValue, setInputValue] = useState();

  function searchButton() {}
  return (
    <div>
      <h1>Github Search</h1>
      <input
        type="text"
        onChange={(e) => {
          setInputValue(e.target.value);
        }}
        value={InputValue}
        name=""
        id=""
        placeholder="Type Username..."
      />
      <button onClick={searchButton}>Search</button>
    </div>
  );
}

export default App;
