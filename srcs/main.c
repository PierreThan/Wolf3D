/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyczyns <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:43:52 by atyczyns          #+#    #+#             */
/*   Updated: 2020/02/18 14:20:41 by atyczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static int	check_input(int ac, char **argv, t_wolf *wolf)
{
	if (ac == 2)
	{
		if ((wolf->fd = open(argv[1], O_RDONLY)) < 0)
		{
			ft_putstr("usage error\n");
			return (0);
		}
		return (parse_file(wolf, argv));
	}
	ft_putstr("usage error");
	return (0);
}

int			close_wolf(void *param)
{
	free_wolf((t_wolf *)param);
	(void)param;
	exit(0);
	return (1);
}

int			free_wolf(t_wolf *wolf)
{
	int		i;

	if (wolf)
	{
		if (wolf->map)
		{
			i = -1;
			while (++i < wolf->width)
				if (wolf->map[i])
					ft_strdel(&(wolf->map[i]));
			ft_memdel((void **)(&(wolf->map)));
		}
		free_textures(wolf);
		if (wolf->displayed && wolf->mlx.mlx_ptr)
		{
			if (wolf->mlx.img.ptr)
				mlx_destroy_image(wolf->mlx.mlx_ptr, wolf->mlx.img.ptr);
			if (wolf->mlx.mlx_ptr)
				mlx_destroy_window(wolf->mlx.mlx_ptr, wolf->mlx.win_ptr);
		}
	}
	return (0);
}

void		init_wolf(t_wolf *wolf)
{
	wolf->fd = 0;
	wolf->height = 0;
	wolf->width = 0;
	wolf->move_speed = 0.20;
	wolf->rot_speed = 0.04;
	wolf->displayed = 0;
}

int			main(int ac, char **argv)
{
	t_wolf	wolf;

	if (ac != 2)
	{
		ft_putstr("usage error : one argument needed\n");
		return (0);
	}
	init_wolf(&wolf);
	if (check_input(ac, argv, &wolf) == 0 || check_border(&wolf) == 0)
		return (free_wolf(&wolf));
	if (ft_display_window("wolf", &wolf) == 0)
		return (free_wolf(&wolf));
	if (init_texture(&wolf) == 0)
	{
		ft_putendl("Toi, t'as touché à nos textures, vilain");
		return (free_wolf(&wolf));
	}
	ray_casting(&wolf);
	setup_controls(&wolf);
	mlx_loop(wolf.mlx.mlx_ptr);
	return (1);
}
