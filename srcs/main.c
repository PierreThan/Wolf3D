/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyczyns <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:43:52 by atyczyns          #+#    #+#             */
/*   Updated: 2019/11/20 16:48:33 by atyczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static int	check_input(int ac, char **argv, t_wolf *wolf)
{
	if (ac == 2)
	{
		if ((wolf->fd = open(argv[1], O_RDONLY)) < 0)
		{
			ft_printf("usage error\n");
			return (0);
		}
		return (parse_file(wolf, argv));
	}
	return (0);
}

int			free_wolf(t_wolf *wolf)
{
	int		i;

	i = 0;
	if (wolf)
	{
		if (wolf->mlx.mlx_ptr)
		{
			mlx_destroy_image(wolf->mlx.mlx_ptr, wolf->mlx.img.ptr);
			mlx_destroy_window(wolf->mlx.mlx_ptr, wolf->mlx.win_ptr);
		}
		if (wolf->map)
		{
			while (wolf->map[i])
				ft_strdel(&(wolf->map[i++]));
			ft_memdel((void **)(&(wolf->map)));
		}
	}
	return (0);
}

int			main(int ac, char **argv)
{
	t_wolf	wolf;

	// verifier check_input, free_wolf et init_mlx
	// faire le raycasting puis les hooks
	if (check_input(ac, argv, &wolf) == 0)
		return (free_wolf(&wolf));
	if (inti_mlx(wolf) == 0)
		return (free_wolf(&wolf));
	// faire tableau --> grille avec bloc 64x64(x64);
	//init_grid(&wolf);
	//ray_casting(&wolf);
	//setup_mlx_ctrls(&wolf);
	mlx_loop(wolf.mlx.mlx_ptr);
	return (0);
}
