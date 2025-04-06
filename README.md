# Task Scheduling Simulation (Round Robin)

This is an educational C project simulating a basic **Round Robin scheduler**, inspired by the Linux kernel's process scheduling logic.

**Work in Progress** — This project is still under development and will be improved with more features and refinements.

## About 📚 

The goal of this project is to better understand how task scheduling works under the hood. It simulates how an operating system schedules tasks using a **Round Robin** algorithm with a fixed time quantum.

The design is lightly inspired by the Linux kernel’s process scheduling model, but simplified for educational purposes.

## Features 💡 

- Simulates a CPU scheduler using the Round Robin algorithm.
- Reads task data (`pid` and `duration`) from an input file.
- Keeps track of time and number of running tasks.
- Basic linked-list-based runqueue structure.
- Simplified implementations of `struct task_struct` and `struct rq`.

## Project Structure 🗂️ 
. 
├── include/ 
│ ├── scheduler.h 
│ └── task.h 
├── src/ 
│ ├── scheduler.c 
│ └── main.c 
├── input # Input file for task data 
└── README.md


## Input Format  📥 

Each line in the `input` file should contain a task's PID and duration, separated by a space:


## Usage ▶️ 

To compile just run the command:

```bash
    make
```
And then to run it do:
```bash
    ./bin/scheduler
```
Make sure to have an input file in the same directory as the binary.

## TODO / Future Improvements 🛠️ 

    Support for multiple scheduling algorithms (e.g. FIFO, SJF, Priority).

    Improve logging / output format.

    Unit tests and CI.

## Educational Purpose 🧠 

This project is purely for learning and experimenting with OS concepts — not intended for production use. It's meant to help understand how context switching, task queues, and scheduling algorithms can be implemented from scratch.
