/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthan <pthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:30:50 by pthan             #+#    #+#             */
/*   Updated: 2018/11/20 15:30:53 by pthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return ((int)(*(unsigned char*)s1 - *(unsigned char*)s2));
		s2++;
		s1++;
	}
	return ((int)(*(unsigned char*)s1 - *(unsigned char*)s2));
}
