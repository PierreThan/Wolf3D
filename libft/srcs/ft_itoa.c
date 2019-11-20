/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthan <pthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:52:54 by pthan             #+#    #+#             */
/*   Updated: 2018/12/10 13:52:37 by pthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_itoa_length(int n)
{
	size_t			len;
	unsigned int	nb;

	len = 1;
	if (n < 0)
	{
		len++;
		nb = (unsigned int)(-n);
	}
	else
		nb = (unsigned int)n;
	if (nb >= 10)
		len += ft_itoa_length((int)(nb / 10));
	return (len);
}

char			*ft_itoa(int n)
{
	char			*res;
	unsigned int	nb;
	size_t			i;

	i = 1;
	if ((res = ft_strnew(ft_itoa_length(n))) == NULL)
		return (NULL);
	if (n < 0)
	{
		res[0] = '-';
		nb = (unsigned int)(-n);
	}
	else
		nb = (unsigned int)n;
	while (nb >= 10)
	{
		res[ft_itoa_length(n) - i++] = (char)(nb % 10 + 48);
		nb /= 10;
	}
	res[ft_itoa_length(n) - i] = (char)(nb + 48);
	return (res);
}
