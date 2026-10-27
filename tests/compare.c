#include "ft_printf.h"
#include <limits.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int	main(int argc, char **argv)
{
	int	count;
	void	*value;
	int	(*format)(const char *, ...);

	if (argc != 2)
		return (2);
	format = ft_printf;
	if (strcmp(argv[1], "libc") == 0)
		format = printf;
	value = (void *)(uintptr_t)42;
	count = format("literal|%c|%s|%d|%i|%u|%x|%X|%%|%p|%c|\n",
			'A', "hello", INT_MIN, INT_MAX, UINT_MAX, UINT_MAX,
			UINT_MAX, value, '\0');
	fflush(stdout);
	fprintf(stderr, "%d\n", count);
	return (0);
}
