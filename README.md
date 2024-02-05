# Project 1: Process Management Simulation

## Overview

This project simulates basic process management using two programs, `oss` (Operating System Simulator) and `user`, to demonstrate the creation and management of processes in a UNIX-like environment. 
The `oss` executable manages multiple `user` child processes, controlling their execution based on command-line arguments.

## Getting Started

### Prerequisites

- GCC compiler
- GNU Make
- A Unix-like environment (Linux, macOS, Cygwin)

### Installation

Clone the repository to your local machine:

```bash
git clone https://github.com/masfm8/Project_1.git
cd Project_1

Compile the programs:
make
Usage
To run the Operating System Simulator:
./oss -n <number_of_processes> -s <simultaneous_processes> -t <iterations>

-n: Total number of child processes to launch.
-s: Maximum number of child processes running simultaneously.
-t: Number of iterations each user process performs.
Example:
./oss -n 5 -s 3 -t 10
