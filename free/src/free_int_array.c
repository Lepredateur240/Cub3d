/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_int_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 19:12:00 by masenche          #+#    #+#             */
/*   Updated: 2026/04/05 19:14:25 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

static void	ft_free_int_tab(int **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
}

void	free_int_array(va_list args)
{
	int	***tab;

	tab = va_arg(args, int ***);
	if (tab && *tab)
	{
		ft_free_int_tab(*tab);
		*tab = NULL;
	}
}