# Get Next Line (GNL)

## Overview
`get_next_line` is a function written in C that reads a line from a file or standard input. It takes a file descriptor as an argument and returns the next line from the file. The function returns NULL when it reaches the end of the file or encounters an error.

## Usage

### Function Prototype
```c
char *get_next_line(int fd);

Parameters
fd: File descriptor representing the file or standard input to be read.
Return Value
A string pointer if a line has been successfully read.
NULL if the end of the file is reached or an error occurs.

Example

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("example.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
'''
This example opens the file example.txt and prints each line. Remember to free the memory after printing each line.

Installation and Compilation
To use get_next_line, include its source file and header file in your project. Compile the source file along with your main program.

gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 main.c get_next_line.c -o gnl

The BUFFER_SIZE macro defines the buffer size for reading. Adjust this value to optimize performance.