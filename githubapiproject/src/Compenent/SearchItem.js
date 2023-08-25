import React from "react";

function searchItem({ htmlLink, username }) {
  return (
    <div>
      <a href={htmlLink}>{username}</a>
    </div>
  );
}

export default searchItem;
