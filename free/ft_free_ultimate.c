/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ultimate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:20:09 by masenche          #+#    #+#             */
/*   Updated: 2026/04/03 14:05:07 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

static void	exec_free(char c, va_list args)
{
	int					i;
	static t_free_map	map[] = {
		{'p', free_simple_ptr},
		{'a', free_str_array},
		{'l', free_list}
	};

	i = 0;
	while (i < 3)
	{
		if (map[i].specifier == c)
		{
			map[i].func(args);
			return ;
		}
		i++;
	}
}

void	ft_ultimate_free(const char *fmt, ...)
{
	va_list	args;
	int		i;

	if (!fmt)
		return ;
	va_start(args, fmt);
	i = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%' && fmt[i + 1])
		{
			exec_free(fmt[i + 1], args);
			i++;
		}
		i++;
	}
	va_end(args);
}
