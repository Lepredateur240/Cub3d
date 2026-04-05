/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_str_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:00:15 by masenche          #+#    #+#             */
/*   Updated: 2026/04/03 14:04:37 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

static void	ft_free_tab(char **tab)
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

void	free_str_array(va_list args)
{
	char	***tab;

	tab = va_arg(args, char ***);
	if (tab && *tab)
	{
		ft_free_tab(*tab);
		*tab = NULL;
	}
}
