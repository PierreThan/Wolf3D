/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_wchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:56:34 by mjouffro          #+#    #+#             */
/*   Updated: 2019/04/11 21:26:36 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
**  UTF-8 encoding
**
**  0xC0 = 	11000000
**  0x80 =  10000000
**  0x3f =    111111
**  0xE0 =  11100000
**
** & -> if both bits are 1 -> 1, otherwise 0
** used with 0x3F -> will check last 6 digit and drop others
**
**     00010100010
**   &      111111
**   =      100010
*/

char		*ft_get_wchar(wint_t wc)
{
	static char	tab[5];

	ft_bzero(tab, 5);
	if (wc <= 0x7F)
		tab[0] = wc;
	else if (wc <= 0x7FF)
	{
		tab[0] = (wc >> 6) + 0xC0;
		tab[1] = (wc & 0x3F) + 0x80;
	}
	else if (wc <= 0xFFFF)
	{
		tab[0] = (wc >> 12) + 0xE0;
		tab[1] = ((wc >> 6) & 0x3F) + 0x80;
		tab[2] = (wc & 0x3F) + 0x80;
	}
	else if (wc <= 0x1FFFFF)
	{
		tab[0] = (wc >> 18) + 0xf0;
		tab[1] = ((wc >> 12) & 0x3F) + 0x80;
		tab[2] = ((wc >> 6) & 0x3F) + 0x80;
		tab[3] = (wc & 0x3F) + 0x80;
	}
	return (tab);
}
