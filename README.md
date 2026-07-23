# Minimal Unix‑Style Shell in C
A lightweight, educational Unix‑style shell implemented in C. Created to refine my understanding of shell functionality and strengthen my fundamentals in the C programming language.

## Getting Started
### Compile
```
gcc shell.c -o shell
```
### Run
```
./shell
```

## Example Usage
```
> ls
> pwd
> echo hello world
> exit
```

## Project Structure
- shell.c — main shell implementation
- README.md — project overview and documentation
- LICENSE.md — MIT license

## How It Works
### 1. Read Input
The shell reads user input character‑by‑character using a dynamically expanding buffer.

### 2. Tokenize
Input is split into tokens using whitespace delimiters such as ```\t```, ```\r```, and ```\n```.

### 3. Execute
Commands are executed using core POSIX system calls:
- fork() — creates a child process
- execvp() — replaces the child with the requested program
- waitpid() — synchronizes the parent with the child

### 4. Loop
The shell continues running until the user enters exit.

## The Why
This project was designed as a hands‑on way to explore how shells work under the hood and to strengthen my understanding of operating system internals, memory management, and process control.

## Future Enhancements
- Add built-in commands (cd, help)
- Support piping and redirection
- Improve error handling

## License
This project is licensed under the MIT License — see the LICENSE.md file for details.
This project is for educational purposes.

## Acknowledgments
This project is based on the tutorial [**“Write a Shell in C” by Danish Prakash**](https://danishpraka.sh/posts/write-a-shell/).

The tutorial provided the initial structure for this shell and served as a learning resource while I explored how to implement basic shell functionality. I plan to continue refining this project using additional tutorials and documentation.
