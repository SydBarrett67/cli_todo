# TODO

Simple command line TODO tool for quick todo-ing in the terminal.

## Usage

```text
todo [command] [arguments] [flags]
```

The executable is located at:

```text
build/todo.exe
```

## Commands

| Command         | Description                                                     |
| --------------- | --------------------------------------------------------------- |
| `new`           | Creates a new `todo.txt` file in the current working directory. |
| `add <task>`    | Adds a new task to the `todo.txt` file.                         |
| `check <index>` | Deletes the task at the specified index.                        |
| `read`          | Prints the contents of the `todo.txt` file to the console.      |
| `delete`        | Deletes the `todo.txt` file.                                    |

## Flags



## Example

```bash
todo new
todo add "Study C++"
todo read
todo check 0
todo delete
```

Tasks are stored in `todo.txt` in the current working directory.

Example:

```text
TODO:
0 - Study C++
2 - Finish project
```
