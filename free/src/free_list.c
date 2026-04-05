/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:59:48 by masenche          #+#    #+#             */
/*   Updated: 2026/04/03 14:04:31 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

void	free_list(va_list args)
{
	t_list	**lst;

	lst = va_arg(args, t_list **);
	if (lst && *lst)
	{
		ft_lstclear(lst, free);
		*lst = NULL;
	}
}
