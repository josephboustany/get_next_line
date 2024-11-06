
# get_next_line

## Project Overview
`get_next_line` is a function that reads one line at a time from a file descriptor, handling memory allocation and buffer management efficiently. Developed as part of the 42 School curriculum, this project strengthens understanding of static variables, dynamic memory handling, and reading from file descriptors.

## Requirements
- **Function Prototype**: `char *get_next_line(int fd);`
- **Files**: 
  - `get_next_line.c`: Contains the main logic for reading lines.
  - `get_next_line_utils.c`: Helper functions supporting `get_next_line`.
  - `get_next_line.h`: Header file with function prototypes and necessary includes.
- **Bonus Files**:
  - `get_next_line_bonus.c` and `get_next_line_utils_bonus.c` for handling multiple file descriptors simultaneously.
- **External Functions Used**: `read`, `malloc`, `free`.
- **Buffer Size**: Controlled with the compiler flag `-D BUFFER_SIZE=n`, where `n` is the buffer size.

## Features
1. **Line-by-Line Reading**:
   - Each call to `get_next_line` returns the next line, including the newline character (`
`), except at EOF.
   - Returns `NULL` at the end of the file or if an error occurs.

2. **Buffer Management**:
   - A static variable retains buffer data between function calls, allowing efficient line reading without redundant reads.

3. **Customizable Buffer Size**:
   - The function works with various buffer sizes, adapting based on the specified `BUFFER_SIZE`.

## Usage
### Compilation
To compile the project with a buffer size, specify `BUFFER_SIZE` as shown below:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o get_next_line
```

### Example Usage
```c
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main() {
    int fd = open("example.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL) {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

### Bonus Part
The bonus version includes support for multiple file descriptors. The project handles separate reading positions for each file descriptor opened.

#### Bonus Compilation
Compile with:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c -o get_next_line_bonus
```

## Learning Outcomes
This project emphasizes:
- **Memory Management**: Utilizing `malloc` and `free` effectively to handle dynamic memory allocation.
- **Static Variables**: Managing persistent data across multiple function calls.
- **File I/O Handling**: Practical use of file descriptors and efficient buffer reading.

## Testing
1. **Buffer Sizes**: Test with various `BUFFER_SIZE` values, including small (1), medium (42), and large (4096) sizes.
2. **File Types**: Use regular files, pipes, and edge cases like empty files.
3. **Edge Cases**: Ensure correct handling of EOF, files without newlines, and large files.

## Restrictions
- **Forbidden Functions**: No usage of `lseek()` or global variables.
- **Memory Leaks**: Ensure all dynamically allocated memory is freed.

## Acknowledgments
Special thanks to 42 School for providing a challenging curriculum that builds core programming skills through practical projects.

---

This `README.md` offers a comprehensive overview of the project, providing installation, usage, and testing guidelines.
