# Minishell

![42 Project](https://img.shields.io/badge/42-Project-brightgreen)
![License](https://img.shields.io/badge/license-MIT-blue)

A custom implementation of a simple shell, inspired by bash, developed as part of the 42 school curriculum.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Technical Implementation](#technical-implementation)
- [Authors](#authors)
- [Acknowledgements](#acknowledgements)

## Overview

Minishell is a lightweight Unix shell that interprets and executes commands from the standard input or from a file. This project aims to deepen understanding of processes, file descriptors, and Unix system calls by recreating a functional shell environment.

## Features

- **Command Execution**: Execute commands with arguments
- **Pipes (`|`)**: Chain commands together
- **Redirections**:
  - Input redirection (`<`)
  - Output redirection (`>`)
  - Append output redirection (`>>`)
  - Here documents (`<<`)
- **Environment Variables**: Support for variable expansion
- **Signal Handling**: Handling of signals like CTRL+C, CTRL+D
- **Quote Handling**: Support for single and double quotes
- **Error Handling**: Proper exit status and error messages

## Installation

### Prerequisites

- GCC compiler
- Make
- Readline library

### Building the Shell

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/minishell-42.git
   cd minishell-42
   ```

2. Compile the project:
   ```bash
   make
   ```

3. Run the shell:
   ```bash
   ./minishell
   ```

## Usage

Once running, the shell displays a prompt where you can enter commands:

```bash
minishell> ls -la
minishell> echo "Hello World"
minishell> cat file.txt | grep "pattern"
```

### Examples

```bash
# Using pipes
minishell> ls -l | grep ".c$"

# Using redirections
minishell> cat < input.txt > output.txt

# Environment variables
minishell> echo $HOME

# Using quotes
minishell> echo "This is a 'quoted' string"
```

## Built-in Commands

- `cd [directory]`: Change the current directory
- `pwd`: Print the current working directory
- `echo [text]`: Display a line of text
- `export [name=value]`: Set environment variables
- `unset [name]`: Remove environment variables
- `env`: Display all environment variables
- `exit [status]`: Exit the shell with specified status

## Technical Implementation

### Project Structure

- **src/**: Source code
  - **builtin/**: Implementation of built-in commands
  - **execution/**: Command execution logic
  - **parsing/**: Lexical and syntactic analysis
  - **helper_func/**: Utility functions
- **include/**: Header files
- **libft/**: Custom C library

### Key Components

- **Lexer & Parser**: Transforms user input into tokens and validates syntax
- **Command Execution**: Handles execution of commands, including search in PATH
- **Redirection Handling**: Manages file descriptors for input/output redirection
- **Signal Management**: Customizes behavior for various Unix signals
- **Environment Management**: Handles shell environment variables

## Authors

- [Main contributor](https://github.com/eel-abed)
- [NPC](https://github.com/Makesense22pls)
## Acknowledgements

- 42 School for the project guidelines and educational framework
- The GNU Bash documentation for reference
