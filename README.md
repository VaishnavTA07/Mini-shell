# Linux Mini Shell

A lightweight Unix-like command-line shell developed in **C** to demonstrate the fundamentals of **Linux System Programming**. The shell supports built-in commands, external command execution, command piping, signal handling, and basic job control using Linux system calls.

---

## Features

- Custom shell prompt (`PS1`)
- Execute external Linux commands
- Execute built-in commands
- Command parsing using `strtok()`
- Single pipe (`|`) support
- Signal handling (`Ctrl+C`, `Ctrl+Z`)
- Foreground job execution
- Background job execution (`bg`)
- Resume stopped jobs in foreground (`fg`)
- Display stopped/background jobs (`jobs`)
- Job management using a linked list
- Parent-child process synchronization
- Error handling for invalid commands

---

## Architecture

```text
                           main()
                              │
                              ▼
                        scan_input()
                              │
        ┌─────────────────────┼─────────────────────┐
        │                     │                     │
        ▼                     ▼                     ▼
 Install Signal        Read User Input      Update Prompt
   Handlers               (fgets)              (PS1)
                              │
                              ▼
                       Parse Command
                     (Tokenization)
                              │
                              ▼
                  check_command_type()
                              │
              ┌───────────────┴───────────────┐
              │                               │
              ▼                               ▼
      Built-in Commands              External Commands
              │                               │
              ▼                               ▼
 execute_internal_command()               fork()
                                              │
                              ┌───────────────┴──────────────┐
                              │                              │
                           Parent                        Child
                              │                              │
                    waitpid(WUNTRACED)        Restore Default Signals
                              │                      (SIGINT/SIGTSTP)
                              │                              │
                     WIFSTOPPED()?                           ▼
                              │                   execute_external_command()
                              ▼                              │
                        insert_job()                  pipe(), dup2(), execvp()
                              │
                              ▼
                     Linked List (Jobs)
```

---

## Built-in Commands

| Command | Description |
|----------|-------------|
| `cd` | Change current directory |
| `pwd` | Print current working directory |
| `echo` | Display text or environment variables |
| `jobs` | Display stopped/background jobs |
| `fg` | Resume the most recent stopped job in the foreground |
| `bg` | Resume the most recent stopped job in the background |
| `exit` | Exit the shell |

---

## External Commands

The shell executes Linux commands such as:

- `ls`
- `cat`
- `sleep`
- `date`
- `cal`
- `grep`
- `ps`
- `clear`
- and many other Linux utilities using `execvp()`.

---

## Job Control

The shell implements basic job control.

- **Ctrl + Z** stops the foreground process.
- Stopped jobs are stored in a linked list.
- `jobs` displays all stopped jobs.
- `fg` resumes the latest stopped job in the foreground.
- `bg` resumes the latest stopped job in the background.
- Jobs are managed using process IDs (`pid_t`).

---

## Signal Handling

The shell handles:

- **SIGINT (Ctrl+C)**
- **SIGTSTP (Ctrl+Z)**

The shell itself ignores termination while waiting for input, whereas child processes restore the default signal handlers to behave like normal Linux commands.

---

## Linux System Calls / Library Functions Used

### Process Management

- `fork()`
- `execvp()`
- `waitpid()`
- `kill()`

### Pipe Management

- `pipe()`
- `dup2()`

### Signal Handling

- `signal()`

### Directory Management

- `getcwd()`
- `chdir()`

### Environment Variables

- `getenv()`

### File Descriptor Operations

- `close()`

### String Handling

- `strtok()`
- `strcspn()`

---

## Concepts Demonstrated

- Linux System Programming
- Process Creation
- Parent–Child Synchronization
- Process States
- Job Control
- Signal Handling
- Pipes
- File Descriptor Duplication
- Linked List Data Structure
- Command Parsing
- Environment Variables

---

## Technologies Used

- C Programming
- Linux (Ubuntu)
- GCC
- POSIX APIs
- Git
- GitHub

---

## Project Structure

```text
Mini-shell/
│
├── main.c
├── fun.c
├── minishell.h
├── Makefile (optional)
└── README.md
```

---

## Compilation

```bash
gcc *.c -o minishell
```

Run:

```bash
./minishell
```

---

## Sample Execution

```text
MyShell:sleep 100
^Z

[1]+ Stopped    sleep 100

MyShell:jobs

[1] PID : 131    Command : sleep 100

MyShell:fg

(wait until process finishes)

MyShell:
```

---

## Key Learnings

- Built a Unix-like command-line shell from scratch.
- Learned Linux process creation using `fork()`.
- Executed external programs using `execvp()`.
- Implemented process synchronization using `waitpid()`.
- Understood process states and signal handling.
- Implemented command piping using `pipe()` and `dup2()`.
- Developed a basic job-control mechanism using linked lists.
- Learned foreground and background process management.

---

## Future Enhancements

- Input Redirection (`<`)
- Output Redirection (`>`, `>>`)
- Multiple Pipes
- Command History
- Auto-completion
- Wildcard Expansion
- Environment Variable Expansion
- Job IDs similar to Bash
- Background execution using `&`

---

## Author

**Vaishnav T A**

Embedded Systems | Linux System Programming | C Programming | Computer Networking
