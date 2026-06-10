# VirtualWorks Online Internship - C++ Programming Track

Welcome to my submission repository for the VirtualWorks Online Internship. This workspace contains a collection of production-ready, clean, and robust C++ implementations designed to demonstrate fundamental software engineering concepts, memory safety, and elegant console-based user interfaces.

---

## 📁 Repository Workspace Map

* 📄 `main.cpp` - **Task 1:** Menu-Driven Basic Calculator
* 📄 `guessing_game.cpp` - **Task 2:** Interactive Number Guessing Game
* 📄 `hotel_management.cpp` - **Task 3:** File-Based Hotel Management System
* 📄 `tic_tac_toe.cpp` - **Task 4:** Console 2D-Matrix Tic-Tac-Toe Game
* 📄 `contact_management.cpp` - **Task 5:** Permanent Storage Contact Management System

---

## 🛠️ Deep Dive into the Tasks

### 🧮 Task 1: Basic Calculator
* **Concept:** Algorithmic logic and conditional evaluation.
* **Key Implementations:** * Features complete input stream validation (`cin.clear()`) to elegantly block character/string entry loops.
  * Structural protection mechanisms against mathematical anomalies like division by zero.

### 🎮 Task 2: Number Guessing Game
* **Concept:** Standard PRNG (Pseudo-Random Number Generation) execution.
* **Key Implementations:**
  * Uses system-clock seeding via `srand(time(0))` to produce a truly unique gaming state on every execution.
  * Adaptive proximity hints ("Way off" vs. "Getting close") to improve player experience.

### 🏨 Task 3: Hotel Management System
* **Concept:** Object persistent structuring using file Input/Output streams (`<fstream>`).
* **Key Implementations:**
  * Dynamically handles room bookings, records matching, and transaction billing summaries.
  * Implements safe file-stream flushing and standard database file rewrite methods during active guest checkouts.

### ❌ Task 4: Tic-Tac-Toe Game
* **Concept:** Multi-dimensional matrix layout parsing.
* **Key Implementations:**
  * Operates on a structured $3 \times 3$ matrix array loop checking horizontal, vertical, and cross-diagonal wins.
  * Includes automated slot restriction safety bounds and natural draw/tie state monitoring.

### 📞 Task 5: Contact Management System
* **Concept:** Flat-file text-database engine management.
* **Key Implementations:**
  * Supports high-level CRUD (Create, Read, Search, Delete) actions stored locally on disk space via `contacts.txt`.
  * Features a flexible multi-field search analyzer (matches name or phone values) and safe temporary storage cache pipelines for record deletion.

---

## 🚀 Local Compilation & Execution Blueprint

Compile any of the applications using a standard C++ compiler like GCC (`g++`).

```bash
# Task 1: Calculator
g++ main.cpp -o calculator && ./calculator

# Task 2: Guessing Game
g++ guessing_game.cpp -o guessing_game && ./guessing_game

# Task 3: Hotel Management
g++ hotel_management.cpp -o hotel_system && ./hotel_system

# Task 4: Tic-Tac-Toe
g++ tic_tac_toe.cpp -o tictactoe && ./tictactoe

# Task 5: Contact Manager
g++ contact_management.cpp -o contacts && ./contacts
