/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthan <pthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:19:38 by pthan             #+#    #+#             */
/*   Updated: 2018/11/20 19:31:31 by pthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	n;
	size_t	l;
	char	*res;

	n = 0;
	if (!s)
		return (NULL);
	while (ft_iswhitespace(s[n]))
		n++;
	if (!s[n])
		return (ft_strnew(0));
	l = ft_strlen(s);
	while (ft_iswhitespace(s[l - 1]))
		l--;
	if (!(res = ft_strsub(s, n, l - n)))
		return (NULL);
	return (res);
}
