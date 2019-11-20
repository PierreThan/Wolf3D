/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthan <pthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:52:05 by pthan             #+#    #+#             */
/*   Updated: 2018/12/10 13:50:19 by pthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nb_line_tab(char const *s, char c)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	if (c == '\0')
		return (1);
	while (s && s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			n++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (n);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	t[3];
	char	**res;

	t[1] = 0;
	t[0] = 0;
	if (!(res = (char**)malloc(sizeof(char*) * (ft_nb_line_tab(s, c) + 1))))
		return (NULL);
	while (s && s[t[1]])
	{
		while (s[t[1]] && s[t[1]] == c)
			t[1]++;
		t[2] = 0;
		while (s[t[1] + t[2]] && s[t[1] + t[2]] != c)
			t[2]++;
		if (t[2])
		{
			if (!(res[t[0]] = ft_strsub(s, (unsigned int)t[1], t[2])))
				return (NULL);
			t[1] += t[2];
			t[0]++;
		}
	}
	res[t[0]] = 0;
	return (res);
}
