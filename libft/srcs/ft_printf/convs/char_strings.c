/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_strings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 18:11:03 by mjouffro          #+#    #+#             */
/*   Updated: 2019/05/28 18:11:04 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		char_conv(t_printf *pf)
{
	char c;

	if ((pf->flags & LM_LONG) || (pf->conv == 'C'))
		wchar_conv(pf);
	else
	{
		c = va_arg(pf->ap, int);
		pf->precision = 0;
		pf->pad = pf->min_len ? --pf->min_len : 0;
		if (!(pf->flags & F_MINUS))
		{
			(pf->flags & F_ZERO) ? min_padding(pf, '0', pf->pad)
			: min_padding(pf, ' ', pf->pad);
		}
		char_padding(pf, c);
		(pf->flags & F_MINUS) ? min_padding(pf, ' ', pf->pad) : 0;
	}
}

void		wchar_conv(t_printf *pf)
{
	size_t	wclen;
	wint_t	wc;

	wc = va_arg(pf->ap, wint_t);
	if (!(wclen = ft_wcharlen(wc)))
		pf->ret = -1;
	pf->pad = pf->min_len ? pf->min_len - wclen : 0;
	!(pf->flags & F_MINUS) ? min_padding(pf, ' ', pf->pad) : 0;
	buffer(pf, ft_get_wchar(wc), 0, wclen);
	(pf->flags & F_MINUS) ? min_padding(pf, ' ', pf->pad) : 0;
}

/*
** 6 is for the length of (null)
*/

void		str_conv(t_printf *pf)
{
	char	*str;
	int		len;

	if ((pf->flags & LM_LONG) || (pf->conv == 'S'))
		wstr_conv(pf);
	else
	{
		str = va_arg(pf->ap, char*);
		len = str ? ft_strlen(str) : 6;
		if (pf->precision && pf->precision < len)
			len = (pf->precision == -1) ? 0 : pf->precision;
		pf->pad = pf->min_len ? pf->min_len - len : 0;
		if (!(pf->flags & F_MINUS))
		{
			(pf->flags & F_ZERO) ? min_padding(pf, '0', pf->pad)
			: min_padding(pf, ' ', pf->pad);
		}
		str ? buffer(pf, str, 0, len) : buffer(pf, "(null)", 0, len);
		(pf->flags & F_MINUS) ? min_padding(pf, ' ', pf->pad) : 0;
	}
}

void		wstr_conv(t_printf *pf)
{
	wchar_t	*wstr;
	int		wstrlen;
	int		len;
	int		i;

	i = 0;
	wstr = va_arg(pf->ap, wchar_t*);
	wstrlen = wstr ? ft_wstrlen(wstr) : 6;
	if (pf->precision && pf->precision < wstrlen)
		wstrlen = pf->precision;
	len = wstr ? wslen_tobuff(wstr, wstrlen) : wslen_tobuff(L"(null)", wstrlen);
	pf->pad = (pf->min_len - len < 0) ? 0 : (pf->min_len - len);
	if (!(pf->flags & F_MINUS))
	{
		(pf->flags & F_ZERO) ? min_padding(pf, '0', pf->pad)
		: min_padding(pf, ' ', pf->pad);
	}
	wstr ? wstr_tobuff(pf, wstr, len) : buffer(pf, "(null)", 0, wstrlen);
	(pf->flags & F_MINUS) ? min_padding(pf, ' ', pf->pad) : 0;
}

size_t		wslen_tobuff(wchar_t *s, int wslen)
{
	int		to_buff;
	int		c_len;
	int		cnt;
	int		tmp;

	cnt = 0;
	to_buff = 0;
	tmp = wslen;
	while (*s && (wslen > 0))
	{
		c_len = ft_wcharlen(*s);
		cnt += c_len;
		if (cnt <= tmp)
			to_buff += c_len;
		wslen -= c_len;
		s++;
	}
	return (to_buff);
}
