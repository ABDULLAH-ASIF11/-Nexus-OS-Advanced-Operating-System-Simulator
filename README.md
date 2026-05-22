# 🖥️ Nexus OS: Advanced Operating System Simulator

![Nexus OS Interface](image_079cc7.png)

[![C++](https://img.shields.io/badge/Language-C%2B%2B17-blue.svg)](https://isocpp.org/)
[![Platform](https://img.shields.io/badge/Platform-Kali%20Linux-lightgrey.svg)](https://www.kali.org/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Status](https://img.shields.io/badge/Status-Completed-brightgreen.svg)]()

> A high-performance, multitasking kernel simulation built to demonstrate deep OS concepts including process lifecycles, resource contention, and multilevel scheduling.

---

## 📑 Table of Contents
* [Core Features](#-key-features)
* [System Architecture](#-architecture)
* [Scheduling Logic](#-scheduling-mechanism)
* [Application Catalog](#-application-catalog)
* [Installation & Usage](#-getting-started)

---

## 🚀 Key Features

* **⚙️ Hardware Constraint Simulation:** Dynamically allocates user-defined **RAM**, **HDD**, and **CPU Cores**.
* **🧵 True Process Management:** Uses `fork()` and `exec()` primitives to ensure each task is a distinct system process.
* **🛡️ Synchronization Primitives:** * **Semaphores:** For CPU core limiting.
    * **Mutex Locks:** For Atomic PCB (Process Control Block) updates.
    * **Condition Variables:** For intelligent RAM-wait state handling.
* **📡 IPC (Inter-Process Communication):** Implementation of **POSIX Pipes** for resource handshakes between tasks and the kernel.
* **🛑 Interrupt Handling:** Advanced signal management using `SIGSTOP`, `SIGCONT`, and `SIGKILL`.

---

## 🏗️ Architecture

Nexus OS operates on a **Three-Tier Architecture** to ensure clean separation of concerns:

| Layer | Responsibility | Key Components |
| :--- | :--- | :--- |
| **Kernel Layer** | Resource Management & Security | RAM Manager, HDD Allocator, IPC Handler |
| **Scheduler Layer** | Process Flow & State | Multilevel Queue, Context Switcher |
| **App Layer** | User Interaction | 20+ C++ Task Binaries |

---

## 🧠 Scheduling Mechanism

The simulator implements a **Priority-Based Multilevel Queue (MLQ)**:

1. **Level 0 (Foreground):** Interactive apps (Round Robin Scheduling).
2. **Level 1 (Background):** Automation tasks (FCFS Scheduling).
3. **Level 2 (System):** Kernel utilities (Priority-Based Scheduling).

---

## 📂 Application Catalog

Nexus OS supports over 20 concurrent applications, including:

### 📁 File Management
* `file_creator.cpp` - Atomic file creation.
* `file_editor.cpp` - Stream-based text editing.
* `file_move.cpp` & `file_copy.cpp` - Filesystem manipulation.
* `file_delete.cpp` - Resource cleanup.

### 🛠️ System Utilities
* `clock.cpp` - Real-time system clock.
* `calender.cpp` - Year-view calendar generator.
* `file_info.cpp` - Metadata & Permission viewer.

---

## 🚦 Getting Started

### 📋 Prerequisites
* **OS:** Kali Linux (Recommended) or Ubuntu.
* **Terminal:** `xterm` must be installed (`sudo apt install xterm`).
* **Compiler:** `g++` (GCC).
* **Compiler:**



1. **🛠️ Compilation** Compile the core OS and the resource deallocator:
   ```bash
   g++ os.cpp -o OS
   g++ dealloc_resource.cpp -o dealloc_resource
2. **🏃Execution** Launch the OS by passing your hardware constraints (RAM, HDD, Cores):
   ```bash
   ./OS <RAM_GB> <HDD_GB> <CORES>

---
## 👨‍💻 THE CREATOR

| ABDULLAH ASIF |
| :---: |
| React / Front-End Developer |
| [![LinkedIn](https://img.shields.io/badge/LINKEDIN-%230077B5?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/abdullah-asif-bhatti/) [![GitHub](https://img.shields.io/badge/GITHUB-%23100000?style=for-the-badge&logo=github&logoColor=white)](https://github.com/ABDULLAH-ASIF11) |
