/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: merel <merel@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/09 10:21:53 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/10/03 15:22:01 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_atoi(const char *str)
{
	long long	i;
	int			n;

	i = 0;
	n = 1;
	while (*str == ' ' || *str == '\n' || *str == '\t'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-' )
			n = n * -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		i = i * 10 + (*str - 48);
		str++;
	}
	return ((int)i * n);
}
