/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:21:55 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/08/16 15:42:13 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *nptr)
{
	int		i;
	long	res;
	int		negative;

	i = 0;
	res = 0;
	negative = 1;
	while (nptr[i] != '\0' && (nptr[i] == ' ' || nptr[i] == '\n'
			|| nptr[i] == '\t' || nptr[i] == '\v' || nptr[i] == '\f'
			|| nptr[i] == '\r'))
		i++;
	if (nptr[i] == '-')
		negative = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i + 1] == '-' || nptr[i + 1] == '+' || nptr[i + 1] == '\0')
			return (123151511215421);
		i++;
	}
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res * negative);
}
