/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthan <pthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 08:41:53 by pthan             #+#    #+#             */
/*   Updated: 2018/11/20 19:45:29 by pthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n && *(unsigned char*)s1 == *(unsigned char*)s2)
	{
		n--;
		s1++;
		s2++;
	}
	if (n > 0)
		return ((int)(*(unsigned char*)s1 - *(unsigned char*)s2));
	return (0);
}
