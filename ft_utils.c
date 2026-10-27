/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddad <mhaddad@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:32:29 by mhaddad           #+#    #+#             */
/*   Updated: 2026/01/06 10:12:01 by mhaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_print_char(char c)
{
	return (write(1, &c, 1));
}

int	ft_print_str(char *str)
{
	int	len;

	len = 0;
	if (!str)
		str = "(null)";
	while (str[len])
	{
		write(1, &str[len], 1);
		len++;
	}
	return (len);
}

int	ft_print_nbr(int n)
{
	int		len;
	long	num;

	num = n;
	len = 0;
	if (num < 0)
	{
		len += ft_print_char('-');
		num = -num;
	}
	if (num >= 10)
		len += ft_print_nbr(num / 10);
	len += ft_print_char((num % 10) + '0');
	return (len);
}

int	ft_print_unsigned(unsigned int n)
{
	int	len;

	len = 0;
	if (n >= 10)
		len += ft_print_unsigned(n / 10);
	len += ft_print_char((n % 10) + '0');
	return (len);
}
