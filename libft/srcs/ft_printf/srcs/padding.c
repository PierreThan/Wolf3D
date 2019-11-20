/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 20:15:12 by mjouffro          #+#    #+#             */
/*   Updated: 2019/04/11 20:39:59 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	char_padding(t_printf *pf, char c)
{
	check_buff(pf);
	pf->buff[pf->buff_i] = c;
	pf->buff_i++;
}

void	hash_padding(t_printf *pf)
{
	char_padding(pf, '0');
	check_buff(pf);
	if (pf->conv == 'x' || pf->conv == 'p')
		pf->buff[pf->buff_i++] = 'x';
	else if (pf->conv == 'X')
		pf->buff[pf->buff_i++] = 'X';
}

void	min_padding(t_printf *pf, char c, int len)
{
	if (len > 0)
		while (len--)
			char_padding(pf, c);
}
