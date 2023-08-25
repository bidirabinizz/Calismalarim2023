import React from "react";

function App() {
  let apiURL = "https://api.myip.com/";
  axios.get(apiURL).then((data) => {
    console.log(data.items);
  });
  return <div>App</div>;
}

export default App;
