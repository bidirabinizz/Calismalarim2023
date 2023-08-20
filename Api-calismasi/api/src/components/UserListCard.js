import React from "react";
import "./UserListCard.css";
function UserListCard({ loginname, username, mail, location, phone, website }) {
  return (
    <div className="usercardMain">
      <h6 className="usernameh6">Username : {loginname}</h6>
      <h2 className="usercardName">{username}</h2>
      <h5>{mail}</h5>

      <br />
      <label>Location : {location}</label>
      <br />
      <label>Phone : {phone}</label>
      <br />
      <a className="usercardAHref" href={website}>
        {website}
      </a>
    </div>
  );
}

export default UserListCard;
