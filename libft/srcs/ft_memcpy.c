/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthan <pthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 08:18:29 by pthan             #+#    #+#             */
/*   Updated: 2018/11/20 19:42:16 by pthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*tmpd;
	char	*tmps;

	tmpd = (char *)dst;
	tmps = (char *)src;
	while (n--)
	{
		*tmpd = *tmps;
		tmpd++;
		tmps++;
	}
	return (dst);
}
