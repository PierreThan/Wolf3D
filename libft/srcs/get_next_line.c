/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 19:37:56 by pthan             #+#    #+#             */
/*   Updated: 2019/01/24 19:39:25 by pthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	get_line(char **line, char **str)
{
	unsigned long	i;
	char			*tmp;

	i = 0;
	tmp = *str;
	while (str[0][i] && str[0][i] != '\n')
		i++;
	if (!(*line = ft_strsub(str[0], 0, i)))
		return (-1);
	if (i == ft_strlen(str[0]))
	{
		if (!(str[0] = ft_strnew(0)))
			return (-1);
	}
	else
	{
		if (!(*str = ft_strdup((*str + i + 1))))
			return (-1);
	}
	free(tmp);
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*res = NULL;
	long		r;
	char		buff[BUFFER_SIZE + 1];
	char		*tmp;

	if (fd < 0 || !line || read(fd, buff, 0) < 0)
		return (-1);
	while ((r = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[r] = '\0';
		tmp = res;
		if (tmp)
		{
			if (!(res = ft_strjoin(res, buff)))
				return (-1);
			free(tmp);
		}
		else
			res = ft_strdup(buff);
		if (ft_strchr(res, '\n'))
			return (get_line(line, &res));
	}
	if (r == 0 && res && ft_strlen(res))
		return (get_line(line, &res));
	return (r < 0 ? -1 : 0);
}
