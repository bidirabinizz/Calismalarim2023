import React from "react";
import "./TaskStyle.css";

function Task({ taskname, done = false, id, func }) {
  function checkboxChanged(e) {
    // console.log(e.target.checked);
    func(e.target.checked, id);
  }

  return (
    <div className="taskMain">
      <input
        onChange={checkboxChanged}
        defaultChecked={done}
        type="checkbox"
        id={id}
      />
      <label className={done ? "understrike" : ""} htmlFor={id}>
        {taskname}
      </label>
    </div>
  );
}

export default Task;
