import "./App.css";
import Task from "./components/Task";
import { useState, useEffect } from "react";

function App() {
  const [input1Value, setInput1Value] = useState("");
  const [completedTasks, setCompletedTasks] = useState(0);

  const [tasks, setTasks] = useState([
    { id: 1, task: "Github'a Proje Ekle", done: true },
    { id: 2, task: "Javascript Öğren", done: false },
    { id: 3, task: "C# Öğren", done: false },
  ]);

  useEffect(() => {
    let tempCounter = 0;
    tasks.map((item) => {
      if (item.done) {
        tempCounter += 1;
      }
    });
    setCompletedTasks(tempCounter);
  }, [tasks]);

  function saveTask() {
    if (input1Value == "") {
      alert("Please write your task!");
    } else {
      let tempTask = { id: tasks.length + 1, task: input1Value, done: false };
      setInput1Value("");
      setTasks([...tasks, tempTask]);
    }
  }

  function doneTask(value, id) {
    // console.log("changed", value, id);

    let tempTask = [];
    tasks.map((task) => {
      if (task.id == id) {
        let temp2 = task;
        temp2.done = value;
        tempTask.push(temp2);
      } else {
        tempTask.push(task);
      }
    });
    setTasks(tempTask);
  }

  return (
    <div className="appMain">
      <h1>To-Do List App</h1>

      {tasks.map((item) => (
        <Task
          key={item.id}
          taskname={item.task}
          done={item.done}
          id={item.id}
          func={doneTask}
        />
      ))}
      <br />

      <input
        onChange={(e) => setInput1Value(e.target.value)}
        value={input1Value}
        type="text"
        name=""
        id=""
        placeholder="write your task..."
        maxLength={25}
      />
      <label
        className={input1Value.length >= 20 ? "warning" : "limit"}
        htmlFor=""
      >
        {input1Value.length}/25
      </label>
      <button onClick={saveTask}>Add Task</button>

      <br />

      <label className="taskCount" htmlFor="">
        Total Tasks: {tasks.length}
      </label>
      <label className="taskCount" htmlFor="">
        {" "}
        --{" "}
      </label>
      <label className="taskCount" htmlFor="">
        Completed Tasks: {completedTasks}
      </label>
      <br />
      <progress value={completedTasks} max={tasks.length}></progress>
    </div>
  );
}

export default App;
