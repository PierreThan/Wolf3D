/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthan <pthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 09:52:07 by pthan             #+#    #+#             */
/*   Updated: 2018/11/20 09:54:03 by pthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	n;

	n = ft_strlen(s);
	if (c == 0)
		return ((char*)(s + n));
	while (n-- > 0)
	{
		if ((char)s[n] == (char)(c))
			return ((char*)(s + n));
	}
	return (NULL);
}
