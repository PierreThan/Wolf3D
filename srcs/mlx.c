/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 02:52:37 by pthan             #+#    #+#             */
/*   Updated: 2020/01/23 15:58:37 by atyczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

/*
**a proteger -> verifier les retours des fncs mlx
*/

int		ft_display_window(char *title, t_wolf *wolf)
{
	wolf->displayed = 1;
	if ((wolf->mlx.mlx_ptr = mlx_init()))
	{
		if ((wolf->mlx.win_ptr = mlx_new_window(wolf->mlx.mlx_ptr,
			WIDTH, HEIGHT, title)))
		{
			if ((wolf->mlx.img.ptr =
					mlx_new_image(wolf->mlx.mlx_ptr, WIDTH, HEIGHT)))
			{
				wolf->mlx.img.data = (int*)mlx_get_data_addr(
					wolf->mlx.img.ptr, &(wolf->mlx.img.bpp),
					&(wolf->mlx.img.size_l), &(wolf->mlx.img.endian));
				return (1);
			}
			return (0);
		}
		return (0);
	}
	return (0);
}

int		key_press(int key, void *param)
{
	t_wolf	*wolf;
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = 0.0;
	old_plane_x = 0.0;
	wolf = (t_wolf *)param;
	if (key == MAIN_PAD_ESC || key == DESTROY_NOTIFY)
		close_wolf(wolf);
	else if (key == ARROW_UP || key == ARROW_DOWN ||
			key == MAIN_PAD_W || key == MAIN_PAD_S)
		move(key, wolf);
	else if (key == ARROW_LEFT || key == ARROW_RIGHT ||
			key == MAIN_PAD_A || key == MAIN_PAD_D)
		rotate(key, wolf, old_dir_x, old_plane_x);
	return (0);
}

void	setup_controls(t_wolf *wolf)
{
	mlx_hook(wolf->mlx.win_ptr, HOOK_KEY_DOWN, 1, key_press, wolf);
}
