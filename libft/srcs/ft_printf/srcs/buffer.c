/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 20:17:44 by mjouffro          #+#    #+#             */
/*   Updated: 2019/05/28 18:09:45 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		reset_struct(t_printf *pf)
{
	pf->flags = 0;
	pf->precision = 0;
	pf->min_len = 0;
	pf->neg = 0;
	pf->base = 0;
	pf->conv = 0;
	pf->pad = 0;
}

void		reset_buff(t_printf *pf)
{
	write(pf->fd, pf->buff, BUFF_SIZE - 1);
	ft_bzero(pf->buff, BUFF_SIZE);
	pf->ret += (BUFF_SIZE - 1);
	pf->buff_i = 0;
}

void		check_buff(t_printf *pf)
{
	if (pf->buff_i == BUFF_SIZE - 1)
		reset_buff(pf);
}

/*
** buffer function allows us to write directly in the static buffer
** when called i will always be set to 0
** n corresponds to len of string
** if the index of the buffer + the len of the string is bigger than
** BUFF SIZE we copy BUFF SIZE minus index of buffer, then add this result
** to i to continue and writing in the buffer
*/

void		buffer(t_printf *pf, char *str, int i, int n)
{
	int		len;

	len = n - i;
	if (pf->buff_i + len >= BUFF_SIZE - 1)
	{
		ft_memcpy(&pf->buff[pf->buff_i], &str[i],
				((BUFF_SIZE - 1) - pf->buff_i));
		i += (BUFF_SIZE - 1) - pf->buff_i;
		reset_buff(pf);
		buffer(pf, str, i, n);
	}
	else
		while (len--)
			pf->buff[pf->buff_i++] = str[i++];
}

void		wstr_tobuff(t_printf *pf, wchar_t *str, int len)
{
	int i;

	i = 0;
	while (len > 0)
	{
		i = ft_wcharlen(*str);
		buffer(pf, ft_get_wchar(*str), 0, i);
		len -= i;
		str++;
	}
}
