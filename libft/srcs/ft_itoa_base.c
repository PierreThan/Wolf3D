/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 19:28:00 by pthan             #+#    #+#             */
/*   Updated: 2019/10/30 19:29:14 by pthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_itoa_base(int n, unsigned int base)
{
	char			*res;
	unsigned int	nb;
	int				i;
	int				size;
	const char		base_vals[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	nb = (n < 0 && base == 10 ? -n : n);
	size = ft_nblenbase(nb, base) + (n < 0 && base == 10 ? 1 : 0);
	if (!(res = ft_strnew(size)))
		return (NULL);
	i = 0;
	if (n < 0 && base == 10)
		res[i++] = '-';
	while (i < size)
	{
		res[--size] = base_vals[nb % base];
		nb /= base;
	}
	return (res);
}
