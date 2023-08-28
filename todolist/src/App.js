import React from "react";
import Task from "./components/Task";
import { useState } from "react";
import "./App.css";

function App() {
  const [input1Value, setInput1Value] = useState();
  const [tasks, setTasks] = useState([
    {
      id: 1,
      task: "github",
      done: true,
    },
    {
      id: 2,
      task: "asdsad",
      done: false,
    },
    {
      id: 3,
      task: "githqweqweub",
      done: false,
    },
  ]);

  function SaveTask() {
    let geciciObj = { id: tasks.lenght + 1, task: input1Value, done: true };

    setTasks([...tasks, geciciObj]);
  }

  function doneTask(value, id) {
    console.log("changed " + value + " " + id);

    tasks.map((task) => {
      if (task.id == id) {
        console.log(task);
      }
    });
  }

  return (
    <div className="appMain">
      <h1>To-Do List App</h1>
      {tasks.map((item) => (
        <Task
          taskName={item.task}
          done={item.done}
          id={item.id}
          func={doneTask}
        ></Task>
      ))}
      <br />
      <input
        className="input1"
        onChange={(e) => {
          setInput1Value(e.target.value);
        }}
        value={input1Value}
        type="text"
        name=""
        id=""
      />
      <button onClick={SaveTask}>Click</button>
    </div>
  );
}

export default App;
