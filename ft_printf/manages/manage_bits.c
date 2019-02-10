/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_bits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 15:42:39 by gscolera          #+#    #+#             */
/*   Updated: 2019/01/13 15:42:40 by gscolera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_value(FORMAT *f, intmax_t *binary)
{
	va_list			copy;

	if (f->flags & DOLLAR)
	{
		va_copy(copy, f->list);
		while (--f->argnum > 0)
			va_arg(copy, void*);
	}
	*binary = va_arg((f->flags & DOLLAR) ? copy : f->list, intmax_t);
}

static void	print_bits(FORMAT *f, unsigned char value)
{
	short bit;

	bit = 128;
	while (bit != 0)
	{
		if (value / bit > 0)
		{
			add_values(f, 49, 1);
			value %= bit;
			bit /= 2;
		}
		else
		{
			add_values(f, 48, 1);
			bit /= 2;
		}
	}
}

void		manage_bits(FORMAT *f)
{
	intmax_t binary;

	get_value(f, &binary);
	print_bits(f, binary);
}
