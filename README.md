*This project was created as part of the 42 curriculum by mhaddad.*

# ft_printf

## Description

A focused implementation of formatted stdout output in C. The project develops
variadic-function handling, format parsing, recursive numeric conversion, and
accurate output-length accounting without depending on libc `printf` for its
implementation.

## Instructions

Requirements: a C compiler, Make, and `ar` on a Unix-like system.

```sh
git clone git@github.com:mohammadhaddad11/ft_printf.git
cd ft_printf
make
cc -Wall -Wextra -Werror -I. examples/demo.c libftprintf.a -o printf_example
./printf_example
```

The archive is `libftprintf.a`; include `ft_printf.h` in client code. Targets
`clean`, `fclean`, and `re` remove objects, remove the archive, and rebuild.

## Technical Implementation

`ft_printf(const char *format, ...)` walks the string from left to right. Literal
characters go directly to `write(1, ...)`; `%` dispatches the next character to
a conversion helper. The helper byte counts are added to the return value.
`va_start`, `va_arg`, and `va_end` provide variadic access.

| Conversion | Behavior |
| --- | --- |
| `%c` | One character, including a possible NUL byte |
| `%s` | String; NULL produces `(null)` |
| `%p` | Lowercase hexadecimal with `0x`; zero produces `(nil)` |
| `%d`, `%i` | Signed decimal `int` |
| `%u` | Unsigned decimal |
| `%x`, `%X` | Lowercase/uppercase hexadecimal |
| `%%` | Literal percent sign |

## Algorithms and Design Decisions

Decimal and hexadecimal helpers recursively emit the higher digits before the
last digit. Numeric conversion needs O(log n) recursion depth and no heap
allocation. String output is linear in its length. The small dispatcher is easy
to inspect, but one-character writes trade throughput for simplicity.

This is a supported subset of `printf`, not a complete replacement. Width,
precision, flags, length modifiers, and floating-point conversions are absent.
Unknown conversion characters produce no output. NULL format strings and a
trailing solitary `%` are not safely handled. `%p` reads `unsigned long`, which
relies on ABI assumptions; the observed Linux behavior is not a portable C
guarantee. Helpers do not consistently propagate write failures.

## Verification

On Fedora, 2026-10-27, `make re` and the example passed with strict warning flags.
[`tests/compare.c`](tests/compare.c) matched libc output and a return count of
78 bytes for a combined supported-format case covering integer boundaries,
hexadecimal, a fixed non-NULL pointer, percent, strings, and a NUL character.

```sh
cc -Wall -Wextra -Werror -I. tests/compare.c libftprintf.a -o printf_compare
./printf_compare custom > custom.out 2> custom.count
./printf_compare libc > libc.out 2> libc.count
cmp custom.out libc.out
cmp custom.count libc.count
```

These are targeted checks, not exhaustive libc conformance or write-error
certification. Unsupported-format limitations remain in the original source.

## Resources

- Linux manual pages: `printf(3)`, `stdarg(3)`, `write(2)`.
- [Variadic arguments](https://en.cppreference.com/w/c/variadic).
- Conversion-table and usage presentation informed by [AhmadNajiKam/Ft_Printf](https://github.com/AhmadNajiKam/Ft_Printf) and [BilalOrabi/Printf](https://github.com/BilalOrabi/Printf); no code was copied.

## AI Usage

The original README included AI-use documentation. For this publication, an AI
assistant inspected the implementation, revised its explanations, and added
the example and differential check. No formatting algorithm was replaced.
