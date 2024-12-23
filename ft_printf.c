/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoyturk <ysoyturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:17:04 by ysoyturk          #+#    #+#             */
/*   Updated: 2024/12/07 17:43:29 by ysoyturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	find_type(va_list args, char type)
{
	unsigned long	ptr;

	if (type == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (type == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (type == '%')
		return (ft_putchar('%'));
	if (type == 'd' || type == 'i')
		return (ft_nbr(va_arg(args, int)));
	if (type == 'u')
		return (ft_convert(va_arg(args, unsigned int), "0123456789", 0));
	if (type == 'p')
	{
		ptr = va_arg(args, unsigned long);
		if (!ptr)
			return (ft_putstr("(nil)"));
		ft_putstr("0x");
		return (ft_convert(ptr, "0123456789abcdef", 0) + 2);
	}
	if (type == 'x' || type == 'X')
		return (ft_convert(va_arg(args, unsigned int), "", type));
	return (0);
}

int	ft_printf(const char *text, ...)
{
	int		sum;
	va_list	args;

	sum = 0;
	va_start(args, text);
	while (*text)
	{
		if (*text != '%')
			sum += write(1, text, 1);
		else if (*(text + 1))
		{
			sum += find_type(args, *(text + 1));
			text++;
		}
		text++;
	}
	va_end(args);
	return (sum);
}
