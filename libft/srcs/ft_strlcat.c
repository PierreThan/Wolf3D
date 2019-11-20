/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthan <pthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 09:30:15 by pthan             #+#    #+#             */
/*   Updated: 2018/11/20 19:37:04 by pthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	l;

	i = 0;
	j = 0;
	l = ft_strlen(src);
	while (dst[i] && i < size)
		i++;
	while (size > 0 && src[j] && i < size - 1)
		dst[i++] = (char)(src[j++]);
	if (j)
		dst[i] = '\0';
	return (i + l - j);
}
