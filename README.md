*This project was created as part of the 42 curriculum by mhaddad.*

# ft_printf

A compact C implementation of formatted output using variadic arguments and a character-by-character format dispatcher.

## Description

`ft_printf(const char *format, ...)` writes to standard output and returns its accumulated output count. On supported normal-output paths this is the number of bytes written; write failures are not consistently propagated.

| Conversion | Output |
| --- | --- |
| `%c`, `%s` | Character and string; a NULL string produces `(null)` |
| `%p` | Pointer in lowercase hexadecimal with `0x`; zero produces `(nil)` |
| `%d`, `%i` | Signed decimal integer |
| `%u` | Unsigned decimal integer |
| `%x`, `%X` | Lowercase and uppercase hexadecimal |
| `%%` | Literal percent |

## Instructions

Requires a C compiler, Make, and `ar`.

```sh
git clone git@github.com:mohammadhaddad11/ft_printf.git
cd ft_printf
make
cc -Wall -Wextra -Werror -I. examples/demo.c libftprintf.a -o printf_example
./printf_example
```

The header is `ft_printf.h` and the generated archive is `libftprintf.a`. Use `make clean`, `make fclean`, or `make re` to clean or rebuild.

## Implementation

The function walks the format string from left to right. Ordinary characters are written directly; a `%` dispatches to the appropriate conversion helper. Arguments are accessed with `va_arg`, and the helper byte counts contribute to the final return value.

Numeric helpers recursively write higher-order digits before the final digit. This avoids heap allocation for integer formatting, while making many small `write` calls.

## Testing and Limitations

The repository contains [a demo](examples/demo.c) and [a comparison test](tests/compare.c). During the earlier portfolio publication, a targeted supported-format comparison matched libc output and a 78-byte return count.

```sh
cc -Wall -Wextra -Werror -I. tests/compare.c libftprintf.a -o printf_compare
./printf_compare custom > custom.out 2> custom.count
./printf_compare libc > libc.out 2> libc.count
cmp custom.out libc.out
cmp custom.count libc.count
```

Width, precision, formatting flags, length modifiers, and floating-point conversions are not implemented. A null format string, a trailing solitary `%`, and some write-failure paths are not safely handled. Unknown conversions produce no output. `%p` retrieves an `unsigned long` rather than `void *`, so its behavior relies on ABI assumptions and is not a portable C guarantee.

## Resources

- C/POSIX manual pages: `printf(3)`, `stdarg(3)`, `write(2)`
- [C variadic arguments](https://en.cppreference.com/w/c/variadic)

## AI Usage

AI assisted with documentation and targeted verification examples during portfolio publication. This README refresh used AI-assisted review; the formatting implementation remains unchanged.
