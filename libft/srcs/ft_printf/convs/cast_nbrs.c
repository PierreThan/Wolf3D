/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_nbrs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 20:28:28 by mjouffro          #+#    #+#             */
/*   Updated: 2019/04/11 20:59:00 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		ft_castconvint(t_printf *pf)
{
	intmax_t nb;

	if ((pf->flags & LM_LONG || pf->flags & LM_LONG2) || (pf->conv == 'D'))
		nb = (intmax_t)(va_arg(pf->ap, long));
	else if (pf->flags & LM_LONG2)
		nb = (intmax_t)(va_arg(pf->ap, long long));
	else if (pf->flags & LM_CHAR)
		nb = (intmax_t)(char)(va_arg(pf->ap, int));
	else if (pf->flags & LM_SHORT)
		nb = (intmax_t)(short)(va_arg(pf->ap, int));
	else if (pf->flags & LM_INTMAX)
		nb = (intmax_t)(va_arg(pf->ap, intmax_t));
	else if (pf->flags & LM_SIZE_T)
		nb = (va_arg(pf->ap, ssize_t));
	else
		nb = (intmax_t)(va_arg(pf->ap, int));
	int_conv(pf, nb);
}

void		ft_castconvuox(t_printf *pf)
{
	uintmax_t	nb;

	if ((pf->flags & LM_LONG) || (pf->conv == 'U') || (pf->conv == 'O'))
		nb = (intmax_t)va_arg(pf->ap, unsigned long);
	else if (pf->flags & LM_LONG2)
		nb = (intmax_t)va_arg(pf->ap, unsigned long long);
	else if (pf->flags & LM_CHAR)
		nb = (uintmax_t)((unsigned char)va_arg(pf->ap, int));
	else if (pf->flags & LM_SHORT)
		nb = (uintmax_t)((unsigned short)va_arg(pf->ap, int));
	else if (pf->flags & LM_INTMAX)
		nb = (va_arg(pf->ap, uintmax_t));
	else if (pf->flags & LM_SIZE_T)
		nb = ((uintmax_t)va_arg(pf->ap, size_t));
	else
		nb = (uintmax_t)va_arg(pf->ap, unsigned int);
	if (pf->conv == 'u' || pf->conv == 'U' ||
			pf->conv == 'b' || pf->conv == 'B')
		uint_conv(pf, nb);
	else
		ox_conv(pf, nb);
}
