*This project has been created as part of the 42 curriculum by jpaulo-p.*

# get_next_line

## Description

`get_next_line` is a function that reads a file descriptor **one line at a time**. Each call returns the next line of the given `fd`, including the trailing `\n` when there is one, and `NULL` when there is nothing left to read or when an error occurs.

```c
char	*get_next_line(int fd);
```

The goal of the project is to write a function that can be called repeatedly in a loop to walk through a text file (or the standard input) without ever loading the whole content into memory, and to do so using a **static variable** to keep the reading state between calls. Only `read`, `malloc` and `free` are allowed; `lseek`, global variables and `libft` are forbidden.

### Files

| File | Content |
| --- | --- |
| `get_next_line.c` | Main logic: `get_next_line`, `ft_read_stash`, `ft_get_line`, `ft_save_rest` |
| `get_next_line_utils.c` | Helper functions: `ft_strlen`, `ft_strchr`, `ft_strjoin`, `ft_copy` |
| `get_next_line.h` | Prototypes, includes and the default `BUFFER_SIZE` |
| `main.c` | Test program — not part of the graded submission |

---

## Instructions

`BUFFER_SIZE` is defined at compile time. The header also defines a default value (42) inside an `#ifndef` guard, so the project compiles both **with** and **without** the `-D` flag.

```bash
# with an explicit buffer size
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl

# without the flag (falls back to the default in the header)
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c -o gnl
```

The function must behave correctly for any positive buffer size, so it is worth testing the extremes:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c -o gnl_1
cc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 get_next_line.c get_next_line_utils.c main.c -o gnl_big
```

### File (main.c)

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("teste.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

> The returned line is heap-allocated: **the caller is responsible for freeing it.**

### Cases covered by the tests

- Files with many lines, with and without a final `\n`
- Empty file and single-line file
- Lines longer than `BUFFER_SIZE`
- `BUFFER_SIZE` of 1 and of very large values
- Invalid file descriptors (negative or closed)
- Reading from the standard input (`fd = 0`)

Leak checking:

```bash
valgrind --leak-check=full ./gnl
```

---

## Algorithm and technical choices

### The stash

The core of the implementation is a `static char *stash`. Because it is static, it survives between calls: it stores everything that has already been read from the file descriptor but has not been returned to the caller yet.


### Step by step

1. **Validation** — `get_next_line` returns `NULL` immediately if `fd < 0` or `BUFFER_SIZE <= 0`.
2. **Reading** (`ft_read_stash`) — reads chunks of `BUFFER_SIZE` bytes and appends each one to the stash **while** there is no `\n` in it and `read` still returns bytes. If `read` fails, the stash is freed and `NULL` is returned.
3. **Extracting the line** (`ft_get_line`) — copies the stash up to and including the first `\n` into a freshly allocated string, which is the value returned to the caller.
4. **Keeping the remainder** (`ft_save_rest`) — allocates a new stash containing whatever comes after that `\n`, frees the old one, and returns `NULL` when nothing is left.

### Why this approach

- **The loop stops at the first `\n`.** The subject explicitly asks to read as little as possible per call, so the reading loop is controlled by `ft_strchr(stash, '\n')` instead of reading until the end of the file. The file is only fully read if it contains no newline at all.
- **A static variable instead of `lseek`.** `lseek` is forbidden, and the file offset must not be rewound anyway — the stash is what allows the next call to resume exactly where the previous one stopped, and it also works on file descriptors that are not seekable, such as the standard input or a pipe.
- **A single flat string rather than a linked list or a fixed array.** A `char *` keeps the logic simple to write, to read and to explain during defence, and all the memory management stays in one place: `ft_strjoin` frees the old stash every time it builds a new one, and `ft_save_rest` frees the stash it replaces. The trade-off is that appending copies the stash on every read, which is acceptable for the sizes involved in this project.
- **`BUFFER_SIZE` guarded by `#ifndef`.** The project must compile with and without the `-D BUFFER_SIZE` flag, so the header provides a default that the compiler flag overrides when present.
- **Helper functions written from scratch.** `libft` is not allowed here, so `ft_strlen`, `ft_strchr`, `ft_strjoin` and `ft_copy` live in `get_next_line_utils.c`. `ft_strjoin` differs from the classic libft version: it accepts a `NULL` stash (the very first call) and frees its first argument, which keeps the caller free of extra bookkeeping.

### Edge cases handled

- End of file without a trailing `\n`: the last line is returned without `\n`, and the following call returns `NULL`.
- Empty file: the first call already returns `NULL`.
- Line longer than `BUFFER_SIZE`: the reading loop simply performs several `read` calls before finding the newline.
- `read` returning `-1`: the stash is freed and set back to `NULL`, so the state is clean for any later call.

---

## Resources

- `man 2 read`, `man 3 malloc`, `man 2 open` — the system and library calls used in the project
- [Static variables in C — GeeksforGeeks](https://www.geeksforgeeks.org/static-variables-in-c/)
- 42 Norm— coding style enforced by the school
- Peer discussions at 42 São Paulo about buffer handling and memory management

### Use of AI

- Any explanation of concepts obtained through AI (for example, how static variables persist between calls) was checked against the manual pages and re-implemented by hand, so that the reasoning behind every line can be explained during the peer evaluation.

---