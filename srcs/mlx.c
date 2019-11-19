/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 02:52:37 by pthan             #+#    #+#             */
/*   Updated: 2019/10/25 02:52:38 by pthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

//a proteger -> verifier les retours des fncs mlx

void	ft_display_window(char *title, t_wolf *wolf)
{
	if ((wolf->mlx.mlx_ptr = mlx_init()))
	{
		if (wolf->mlx.win_ptr = mlx_new_window(wolf->mlx.mlx_ptr,
			WIDTH, HEIGHT, title))
		{
			if ((wolf->mlx.img.ptr =
					mlx_new_image(wolf->mlx.mlx_ptr, WIDTH, HEIGHT)))
			{
				wolf->mlx.img.data = (int*)mlx_get_data_addr(
					wolf->mlx.img.ptr, &(wolf->mlx.img.bpp),
					&(wolf->mlx.img.size_l), &(wolf->mlx.img.endian));
				return ;
			}
		}
	}
	free_mlx(wolf);
}

int		close_wolf(void *param)
{
	free_wolf((t_wolf *)param);
	(void)param;
	exit(0);
}

int		key_press(int key, void *param)
{
	t_wolf *wolf;

	wolf = (t_wolf *)param;
	if (key == MAIN_PAD_ESC)
		exit(0);
	else if (key == ARROW_UP || key == ARROW_DOWN)
		move(key, wolf);
	else if (key == ARROW_LEFT || key == ARROW_RIGHT)
		rotate(key, wolf);
	return (0);
}

void	setup_controls(t_wolf *wolf)
{
	mlx_hook(wolf->mlx.win_ptr, 2, 0, key_press, wolf);
	mlx_hook(wolf->mlx.win_ptr, 17, 0, close_wolf, wolf);
	//mlx_hook(wolf->mlx.win_ptr, 4, 0, mouse_press, wolf);
}
