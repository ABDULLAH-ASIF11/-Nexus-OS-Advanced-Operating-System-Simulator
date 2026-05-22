# 🖥️ Nexus OS: Advanced Operating System Simulator

> A robust, multitasking OS simulation built in C++ using POSIX system calls. Designed to simulate kernel-level resource management, process scheduling, and synchronization.

---

## 🚀 Key Features

* **Multitasking & Scheduling:** Implements a **Multilevel Queue Scheduler** (Round Robin for foreground, FCFS for background, and Priority for system tasks).
* **True Process Management:** Uses `fork()` and `exec()` to launch independent tasks in separate `xterm` windows.
* **Hardware Simulation:** Strictly manages user-defined RAM, HDD, and CPU Cores.
* **Synchronization:** Utilizes **Semaphores** for core limiting and **Mutex Locks** for protecting the PCB (Process Control Block) table.
* **IPC (Inter-Process Communication):** Communication between the OS and tasks via **Pipes**.
* **Interruption Handling:** Supports real-time `SIGSTOP`, `SIGCONT`, and `SIGKILL` signals for closing and minimizing apps.

---

## 🏗️ Architecture

The project is divided into three logical layers:

1.  **Kernel Layer:** Resource Manager, Memory Allocation, and IPC handling.
2.  **Scheduler Layer:** Context switching and queue management.
3.  **Application Layer:** 20+ standalone C++ applications (Calculator, Notepad with Autosave threads, Clock, etc.).

---

## 🚦 Getting Started

### Prerequisites
* **OS:** Kali Linux (or any Debian-based distro with `xterm` installed).
* **Compiler:** `g++` (GCC).

### Compilation
First, compile the main OS controller:
```bash
g++ os.cpp -o OS
![Nexus OS Preview](image_079cc7.png)
