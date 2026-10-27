#include "ft_printf.h"

int	main(void)
{
	int	count;

	count = ft_printf("%s: %d %u %x %X %%\n", "ft_printf", -42, 42u,
			42u, 42u);
	if (count < 0)
		return (1);
	return (0);
}
