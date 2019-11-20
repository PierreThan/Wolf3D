/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 21:42:16 by pthan             #+#    #+#             */
/*   Updated: 2019/05/28 18:11:10 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_minlen(t_printf *pf, long double nb)
{
	int			min;
	uintmax_t	n;

	min = pf->min_len;
	if (nb < 0)
	{
		min -= 1;
		nb = -nb;
	}
	n = (uintmax_t)nb;
	min -= (ft_nbrlen(n, 10) + pf->precision + 1);
	if (pf->precision == 0)
		min++;
	if (pf->flags & F_PLUS || pf->flags & F_SPACE)
		min--;
	return (min);
}

int		check_infnan(t_printf *pf, long double nb)
{
	int		i;
	int		min;

	i = pf->buff_i;
	if (!(ft_isnan(nb) || ft_isinf(nb)))
		return (1);
	min = (nb < 0.0) ? pf->min_len - 4 : pf->min_len - 3;
	(pf->flags & F_MINUS) ? 0 : min_padding(pf, ' ', min);
	if (ft_isnan(nb) && pf->conv == 'F')
		buffer(pf, "NAN", 0, 3);
	else if (ft_isnan(nb) && pf->conv == 'f')
		buffer(pf, "nan", 0, 3);
	else if (ft_isinf(nb) && pf->conv == 'F' && nb < 0.0)
		buffer(pf, "-INF", 0, 4);
	else if (ft_isinf(nb) && pf->conv == 'f' && nb < 0.0)
		buffer(pf, "-inf", 0, 4);
	else if (ft_isinf(nb) && pf->conv == 'F' && nb >= 0.0)
		buffer(pf, "INF", 0, 3);
	else if (ft_isinf(nb) && pf->conv == 'f' && nb >= 0.0)
		buffer(pf, "inf", 0, 3);
	(pf->flags & F_MINUS) ? min_padding(pf, ' ', min) : 0;
	return (i == pf->buff_i ? 1 : 0);
}

void	f_padding(t_printf *pf, int min, long double nb)
{
	if (pf->flags & F_MINUS)
	{
		f_conv(pf, nb);
		min_padding(pf, ' ', min);
	}
	else
	{
		(pf->flags & F_PLUS && pf->flags & F_ZERO) ? char_padding(pf, '+') : 0;
		(pf->flags & F_ZERO) ? min_padding(pf, '0', min) :
		min_padding(pf, ' ', min);
		f_conv(pf, nb);
	}
}

void	float_conv(t_printf *pf)
{
	long double	nb;
	int			min;

	if (!pf->precision)
		pf->precision = 6;
	if (pf->precision == -1)
		pf->precision = 0;
	if (pf->flags & LM_DOUBLE)
		nb = va_arg(pf->ap, long double);
	else
		nb = (long double)va_arg(pf->ap, double);
	if (!check_infnan(pf, nb))
		return ;
	min = get_minlen(pf, nb);
	f_padding(pf, min, nb);
}
