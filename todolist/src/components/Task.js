import React from "react";
import "./TaskStyle.css";

function Task({ taskName, done = false, id, func }) {
  function checkBoxChange(e) {
    console.log(e.target.checked);
    func(e.target.checked, id);
  }
  return (
    <div className="taskMain">
      <input
        onChange={checkBoxChange}
        className="inputCheckBox1"
        type="checkbox"
        defaultChecked={done}
        id={id}
      />
      <label className={done ? "underStrike" : "de"} htmlFor={id}>
        {taskName}
      </label>
    </div>
  );
}

export default Task;
