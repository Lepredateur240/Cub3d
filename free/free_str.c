/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:00:00 by masenche          #+#    #+#             */
/*   Updated: 2026/04/03 14:01:04 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

void	free_simple_ptr(va_list args)
{
	void	**ptr;

	ptr = va_arg(args, void **);
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
