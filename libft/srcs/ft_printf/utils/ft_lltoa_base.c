/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:56:52 by mjouffro          #+#    #+#             */
/*   Updated: 2019/04/11 21:27:53 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char				*ft_lltoa_base(uintmax_t nb, intmax_t base)
{
	uintmax_t		nb_size;
	static char		str[22];
	char			*strbase;

	ft_bzero(str, 22);
	strbase = "0123456789abcdef";
	nb_size = ft_nbrlen(nb, base);
	str[nb_size] = '\0';
	while (nb_size--)
	{
		str[nb_size] = strbase[(nb % base)];
		nb /= base;
	}
	return (str);
}
