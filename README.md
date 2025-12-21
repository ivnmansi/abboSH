# abboSH

A small UNIX-like shell written in C, built as a learning project to explore process management, system calls, and basic shell features.

---

## Features

- **Interactive loop**: Reads a line, parses it into tokens, and executes.
- **Built-ins**:
	- `cd [dir]` – change the current working directory (defaults to `$HOME`).
	- `exit` – exit the shell
- **Command execution**:
	- Uses `fork` + `execvp` to run external programs.
	- Prints process exit status or terminating signal.
- **Redirection**:
	- Output redirection: `>` (truncate) and `>>` (append).
	- Input redirection: `<` from file.
	- Here-document: `<<` with a stop word, implemented via a temporary file.

---

## Installation

### Prerequisites

- A POSIX-compatible system (tested on Linux).
- `gcc` or another C compiler.
- `make`.

### Build

From the project root:

```bash
make
```

This should produce the binary in `build/abboSH`.

---

## Usage

Run the shell from the project directory:

```bash
./build/abboSH
```

You should see a prompt similar to:

```text
user@hostname /current/dir > 
```

Type commands just like in a basic shell:

```text
user@hostname /home/user > ls -l
user@hostname /home/user > cd Documents
user@hostname /home/user/Documents > echo "hello world"
```

Exit with:

```text
user@hostname /home/user > exit
Bye bye!
```

---

## To do

- Add support for:
	- Pipes (`cmd1 | cmd2`)
	- Background jobs (`cmd &`)
	- Basic command history
- Improve error handling and messages
- Implement signal handling
- Customization options
