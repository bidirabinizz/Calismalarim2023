import React from "react";
import "./ListOfSearch.css";
function ListOfSearch({ title, imgURL }) {
  return (
    <div className="SearchMainClass">
      <div className="title">
        <label htmlFor="">{title}</label>
      </div>
      <img src={imgURL} alt="" />
    </div>
  );
}

export default ListOfSearch;
