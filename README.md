*This project was created as part of the 42 curriculum by mhaddad.*

# ft_printf

`ft_printf` turns a format string and a variable number of arguments into text
on standard output. It implements a focused subset of C's formatted printing
interface without calling libc `printf` to produce that output.

The project connects three low-level tasks: parse control characters in a
string, retrieve arguments with the correct types, and convert values into
bytes while counting the output.

## Build and use

Requirements: a C compiler, Make, and `ar` on a Unix-like system.

```sh
git clone git@github.com:mohammadhaddad11/ft_printf.git
cd ft_printf
make
cc -Wall -Wextra -Werror -I. examples/demo.c libftprintf.a -o printf_example
./printf_example
```

The [demo](examples/demo.c) prints:

```text
ft_printf: -42 42 2a 2A %
```

Clients include [`ft_printf.h`](ft_printf.h) and link `libftprintf.a` after their
source/object files. The public function is:

```c
int ft_printf(const char *format, ...);
```

`make clean` removes objects, `make fclean` also removes the archive, and
`make re` rebuilds everything.

## Supported conversions

| Specifier | Argument retrieved | Output |
| --- | --- | --- |
| `%c` | `int` | One character, including a possible NUL byte |
| `%s` | `char *` | String bytes up to the terminator; NULL becomes `(null)` |
| `%d`, `%i` | `int` | Signed decimal |
| `%u` | `unsigned int` | Unsigned decimal |
| `%x`, `%X` | `unsigned int` | Hexadecimal with lowercase/uppercase letters |
| `%p` | `unsigned long` in this implementation | Lowercase hex with `0x`; zero becomes `(nil)` |
| `%%` | None | A literal percent sign |

`%p`'s retrieval type is an implementation limitation, not a recommendation
for portable variadic pointer handling. The Linux ABI used for verification
permits the observed behavior; callers should not infer universal portability.

## From a format string to bytes

```text
format + arguments
      ↓
ft_printf: scan and keep a running count
      ├── ordinary byte ───────────────▶ ft_print_char
      └── '%' + conversion ─▶ ft_formats / va_arg
                                  ↓
                         type-specific helper
                                  ↓
                         write(1, bytes, count)
```

### 1. Initialize variadic state

[`ft_printf`](ft_printf.c) uses `va_start` to initialize a `va_list`. The format
is the only information indicating the number and types of following values;
the variadic interface does not supply a type-safe container. A wrong argument
type or missing argument can therefore cause undefined behavior.

### 2. Scan literals and conversion markers

The scanner moves from left to right. An ordinary character is sent directly
to `ft_print_char`. On `%`, it passes the next character to `ft_formats`, then
advances past both the marker and the conversion. The dispatcher is a small
conditional chain rather than a parser for width, precision, or modifiers.

### 3. Retrieve the next value

`va_arg` advances the argument state using the conversion's expected type.
For `%c`, the helper retrieves `int` because character arguments undergo the
normal variadic integer promotions. `%d`/`%i` share signed output, and `%%`
does not consume a value. `va_end` closes the variadic lifecycle before return.

### 4. Convert numbers without building heap strings

[`ft_print_nbr`](ft_utils.c) handles a sign and recursively emits the higher
decimal digits before the last digit. Unsigned decimal uses division by 10;
[`ft_print_hex`](ft_print_hex.c) divides by 16 and indexes a lowercase or
uppercase digit alphabet. Zero reaches the final digit write directly.

[`ft_print_ptr`](ft_print_ptr.c) handles the prefix and zero-pointer spelling,
then recursively emits hexadecimal digits. Number conversion uses call-stack
space proportional to digit count and no heap allocation. Direct byte writes
keep the implementation small, but make many system calls.

## Understanding the returned count

For normal output, helper counts are accumulated into the result. For example:

```c
int count = ft_printf("value=%d hex=%x\n", 42, 42u);
/* Output: value=42 hex=2a followed by newline; count is 16. */
```

The newline counts as one byte. A NUL emitted through `%c` also counts even
though it is not visible in a terminal. The return value is about bytes, not
the number of conversions or visual character cells.

Error handling is incomplete: string output increments its count even when
individual writes fail, and other helpers can add negative write results to
an accumulated value. This is not libc-compatible error propagation.

## Verification and interface limits

The strict build and demo passed. The bundled [comparison driver](tests/compare.c)
also matched libc output and its 78-byte return count for its supported-format
case, including integer boundaries and a NUL character:

```sh
cc -Wall -Wextra -Werror -I. tests/compare.c libftprintf.a -o printf_compare
./printf_compare custom > custom.out 2> custom.count
./printf_compare libc > libc.out 2> libc.count
cmp custom.out libc.out
cmp custom.count libc.count
```

Width, precision, formatting flags, length modifiers, and floating-point
conversions are absent. An unknown conversion emits nothing rather than
reporting a format error. A NULL format or a trailing solitary `%` is not
safely handled. These boundaries matter more than calling the function a full
drop-in replacement: it is an implementation of the listed subset.

## Resources

- C/POSIX manual pages: `printf(3)`, `stdarg(3)`, `write(2)`
- [C variadic arguments](https://en.cppreference.com/w/c/variadic)

## AI Usage

AI assisted documentation and targeted verification examples. The formatting
implementation is preserved; the examples describe its actual supported paths
and do not claim exhaustive libc conformance.
