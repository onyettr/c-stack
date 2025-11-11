# ANSI C Programming Exercises  - Stack

# Introduction
Simple stack implementation. 

It uses dynamic memory allocation
for the Stack_t type called from an exposed StackCreate() function call. 

### 📦 Core Implementation & Build
This section contains the fundamental source code and the build script.

* **`stack.c`**: **Core Stack Implementation.** Defines the data structure and operations (push, pop, etc.).
* **`stack.h`**: Header file with function prototypes and definitions for the stack.
* `main.c`: Entry point that launches the test harness.
* `makefile`: The build script used to compile and link the project.

### 🛡️ Error Handling
These utilities manage error states and trapping.

* `trap.c`: Source code for the global **error trap handler**.
* `trap.h`: Header file for the error handler.

### 🧪 Test Harness & Suites
These files are dedicated to verifying the correctness of the stack implementation.

* `test.h`: Common header file for all test modules (macros, definitions).
* `stack_check.ts`: Script for the `check` testing tool for automated verification.
* **Individual Test Files**: Dedicated modules for specific functions:
    * `test_empty.c`
    * `test_pop.c`
    * `test_push.c`
    * `test_size.c`
    * `test_swap.c`
    * `test_top.c`

### 🚀 Building and Running
Two methods to build either old fashioned Makefile or with CMake

#### Makefile

<code>

$ make all

</code>

##### CMake

<code>

$ mkdir build

$ cd build

$ cmake ..

$ make

</code>

## 🧪 Test Coverage

The project includes dedicated test files for all major stack operations:

* **`test_push.c`**: Verifies correct element insertion.
* **`test_pop.c`**: Checks correct element removal and stack state change.
* **`test_top.c`**: Ensures the top element is correctly retrieved without removal.
* **`test_empty.c`**: Tests if the stack's emptiness state is correctly reported.
* **`test_size.c`**: Verifies the stack's current size is maintained accurately.
* **`test_swap.c`**: Tests the utility function to swap the top two elements (if implemented).

---

### Prerequisites

To build and run this project, you will need:

* A C compiler (e.g., GCC)
* The `make` utility
* CMake
