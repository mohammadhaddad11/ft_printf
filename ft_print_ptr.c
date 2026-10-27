/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddad <mhaddad@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:59:31 by mhaddad           #+#    #+#             */
/*   Updated: 2026/01/06 09:38:47 by mhaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	ft_putptr(unsigned long num)
{
	int		len;
	char	*base;

	base = "0123456789abcdef";
	len = 0;
	if (num >= 16)
	{
		len += ft_putptr(num / 16);
	}
	len += write(1, &base[num % 16], 1);
	return (len);
}

int	ft_print_ptr(unsigned long ptr)
{
	int	len;

	len = 0;
	if (ptr == 0)
	{
		return (write(1, "(nil)", 5));
	}
	len += write(1, "0x", 2);
	len += ft_putptr(ptr);
	return (len);
}
