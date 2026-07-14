# Linux Mini Shell

A lightweight Unix-like command-line shell developed in **C** that demonstrates the fundamentals of **Linux system programming**. The shell supports execution of external commands, a limited set of built-in commands, background process execution, signal handling, and command piping using Linux system calls.

---

## Features

* Execute external Linux commands
* Support for limited built-in commands
* Custom shell prompt (PS1)
* Command parsing
* Background process execution (`&`)
* Command piping (`|`)
* Signal handling (`Ctrl+C`, `Ctrl+Z`)
* Process creation and synchronization
* Error handling for invalid commands

---

## Project Workflow

```text
Start Mini Shell
        ↓
Display Shell Prompt (PS1)
        ↓
Read User Input
        ↓
Parse Command
        ↓
 ┌───────────────────────────────┐
 │ Is it a Built-in Command?      │
 └───────────────────────────────┘
        ↓ Yes                     ↓ No
Execute Built-in            Create Child Process
Command                           │
                                  ↓
                           Execute using execvp()
                                  │
                                  ↓
                     Parent waits / Background Process
                                  │
                                  ↓
                   Handle Pipes & Signals (if required)
                                  │
                                  ↓
                         Display Prompt Again
```

---

## Built-in Commands

The shell supports a limited set of built-in commands, including:

* `cd`
* `pwd`
* `echo`
* `exit`
* `jobs`
* *(Add any other built-in commands implemented in your project.)*

---

## Linux System Calls Used

* `fork()`
* `execvp()`
* `wait()`
* `waitpid()`
* `pipe()`
* `dup2()`
* `open()`
* `close()`
* `read()`
* `write()`
* `signal()`

---

## Concepts Demonstrated

* Linux System Programming
* Process Creation and Management
* File Descriptors
* Inter-Process Communication (Pipes)
* Signal Handling
* Shell Programming
* Command Parsing
* Parent–Child Process Synchronization

---

## Technologies Used

* C Programming
* Linux (Ubuntu)
* GCC Compiler
* POSIX System Calls
* Shell Programming
* Git & GitHub

---

## Project Structure

```text
Linux-Mini-Shell/
│
├── main.c
├── shell.c
├── shell.h
├── parser.c
├── parser.h
├── execute.c
├── execute.h
├── signal.c
├── signal.h
├── builtin.c
├── builtin.h
├── Makefile
└── README.md
```

---

## Compilation

Compile the project using GCC:

```bash
gcc *.c -o minishell
```

Run the executable:

```bash
./minishell
```

---

## Key Learnings

* Developed a deeper understanding of Linux process management using `fork()`, `execvp()`, and `wait()`.
* Implemented command piping using `pipe()` and `dup2()`, gaining practical experience with file descriptor manipulation.
* Learned how signals are handled in Unix-like operating systems.
* Improved understanding of shell architecture, process synchronization, and inter-process communication.

---

## Future Enhancements

* Input/Output Redirection (`<`, `>`, `>>`)
* Command History
* Auto-completion
* Environment Variable Expansion
* Multiple Pipes
* Job Control Enhancements

---

## Author

**Vaishnav T A**

Embedded Systems | Linux System Programming | C Programming | Computer Networking
