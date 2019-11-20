/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthan <pthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 08:28:54 by pthan             #+#    #+#             */
/*   Updated: 2018/11/20 08:34:11 by pthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*tmpd;
	char	*tmps;

	tmpd = (char *)dst;
	tmps = (char *)src;
	if (dst <= src)
	{
		while (len-- > 0)
		{
			*tmpd = *tmps;
			tmpd++;
			tmps++;
		}
	}
	else
	{
		while (len > 0)
		{
			len--;
			*(tmpd + len) = *(tmps + len);
		}
	}
	return (dst);
}
