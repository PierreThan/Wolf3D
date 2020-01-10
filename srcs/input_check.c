
#include "../includes/wolf3d.h"

int		get_nbr_per_line(char *str)
{
	int	nbr_per_line;

	nbr_per_line = 0;
	while (str && *str)
	{
		if (*str != ' ')
		{
			if (ft_isdigit(*str))
			{
				str++;
				nbr_per_line++;
			}
			else
				return (0);
		}
		else
			str++;
	}
	return (nbr_per_line);
}

int		get_dimensions(t_wolf *wolf)
{
	char	*line;
	int		i;
	int		ret[2];

	i = 0;
	while (++i && (ret[0] = get_next_line(wolf->fd, &line) > 0))
	{
		ret[1] = get_nbr_per_line(line);
		if (i == 1 && ret[1])
			wolf->width = ret[1];
		else if (ret[1] == 0 || ret[1] != wolf->width)
			close(wolf->fd);
		wolf->height++;
	}
	if (ret[0] <= 0)
		close(wolf->fd);
	if (!ret[0])
		ft_strdel(&line);
	if (ret[0] < 0 || (!ret[0] && !wolf->width && !wolf->height))
		return (0);
	else
		return (1);
}

void	get_line(t_wolf *wolf, char *line, int j)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (line && line[k])
	{
		if (ft_isdigit(line[k]))
		{
			wolf->map[i][j] = line[k];
			i++;
			k++;
		}
		else
			k++;
	}
}

int		get_file(t_wolf *wolf, char **argv)
{
	int		j;
	int		ret;
	char	*line;

	if ((wolf->fd = open(argv[1], O_RDONLY)) < 0)
	{
		ft_printf("usage error\n");
		return (0);
	}
	j = 0;
	while ((ret = get_next_line(wolf->fd, &line)) > 0)
	{
		get_line(wolf, line, j);
		ft_strdel(&line);
		j++;
	}
	close(wolf->fd);
	if (j == wolf->height && !ret)
		return (1);
	return (0);
}

int		init_player(t_wolf *wolf)
{
	int i;
	int j;

	i = 0;
	while (i < wolf->width)
	{
		j = 0;
		while (j < wolf->height)
		{
			if (wolf->map[i][j] == '0')
			{
				wolf->player.pos.x = i;
				wolf->player.pos.x += 0.5;
				wolf->player.pos.y = j;
				wolf->player.pos.y += 0.5;
				wolf->player.dir.x = 1;
				wolf->player.dir.y = 1;
				wolf->player.plane.x = 0;
				wolf->player.plane.y = 0.66;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int		parse_file(t_wolf *wolf, char **argv)
{
	int	i;
	int	j;

	i = 0;
	wolf->height = 0;
	wolf->width = 0;
	if (!get_dimensions(wolf))
	{
		ft_printf("wrong file format\n");
		return (0);
	}
	if (!(wolf->map =
			(char **)ft_memalloc(wolf->width * sizeof(char *))))
		return (0);
	while (i < wolf->width)
	{
		if (!(wolf->map[i] = ft_strnew(wolf->height)))
			return (0);
		i++;
	}
	if (get_file(wolf, argv) == 0)
	{
		ft_printf("parsing problem\n");
		return (0);
	}
	j = 0;
	/*AFFICHAGE
	while (j < wolf->height)
	{
		i = 0;
		while (i < wolf->width)
		{
			ft_putchar(wolf->map[i][j]);
			ft_putchar(' ');
			i++;
		}
		ft_putchar('\n');
		j++;
	}*/
	if (init_player(wolf))
		return (1);
	return (0);
}
