/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:57:27 by masenche          #+#    #+#             */
/*   Updated: 2026/04/05 19:14:34 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

#include <stdarg.h>
#include <stdlib.h>
#include "../../libft/libft.h"

typedef void	(*t_free_func)(va_list);

typedef struct s_free_map
{
	char		specifier;
	t_free_func	func;
}				t_free_map;

void	free_list(va_list args);
void	free_str_array(va_list args);
void	free_simple_ptr(va_list args);
void	free_int_array(va_list args);
void	ft_ultimate_free(const char *fmt, ...);

#endif