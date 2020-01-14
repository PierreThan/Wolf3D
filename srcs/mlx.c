/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 02:52:37 by pthan             #+#    #+#             */
/*   Updated: 2020/01/14 19:15:12 by atyczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

//a proteger -> verifier les retours des fncs mlx

int		ft_display_window(char *title, t_wolf *wolf)
{
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

int		close_wolf(void *param)
{
	free_wolf((t_wolf *)param);
	(void)param;
	exit(0);
}
void	move(int key, t_wolf *wolf)
{
	int	new_x;
	int	new_y;

	if (key == ARROW_UP)
	{
		new_x = (int)(wolf->player.pos.x + wolf->player.dir.x * wolf->move_speed);
		new_y = (int)(wolf->player.pos.y + wolf->player.dir.y * wolf->move_speed);
 		if (wolf->map[new_x][(int)wolf->player.pos.y] == '0')
			wolf->player.pos.x += wolf->player.dir.x * wolf->move_speed;
    	if (wolf->map[(int)wolf->player.pos.x][new_y] == '0')
	  		wolf->player.pos.y += wolf->player.dir.y * wolf->move_speed;
	}
	else if (key == ARROW_DOWN)
	{
		new_x = (int)(wolf->player.pos.x - wolf->player.dir.x * wolf->move_speed);
		new_y = (int)(wolf->player.pos.y - wolf->player.dir.y * wolf->move_speed);
 		if (wolf->map[new_x][(int)wolf->player.pos.y] == '0')
			wolf->player.pos.x -= wolf->player.dir.x * wolf->move_speed;
    	if (wolf->map[(int)wolf->player.pos.x][new_y] == '0')
	  		wolf->player.pos.y -= wolf->player.dir.y * wolf->move_speed;
	}
	ray_casting(wolf);
}

void	rotate(int key, t_wolf *wolf)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = wolf->player.dir.x;
	old_plane_x = wolf->player.plane.x;
	if (key == ARROW_LEFT)
	{
		wolf->player.dir.x = wolf->player.dir.x * cos(-wolf->rot_speed) - wolf->player.dir.y * sin(-wolf->rot_speed);
    	wolf->player.dir.y = old_dir_x * sin(-wolf->rot_speed) + wolf->player.dir.y * cos(-wolf->rot_speed);
		wolf->player.plane.x = wolf->player.plane.x * cos(-wolf->rot_speed) - wolf->player.plane.y * sin(-wolf->rot_speed);
		wolf->player.plane.y = old_plane_x * sin(-wolf->rot_speed) + wolf->player.plane.y * cos(-wolf->rot_speed);
	}
	else if (key == ARROW_RIGHT)
	{
		wolf->player.dir.x = wolf->player.dir.x * cos(wolf->rot_speed) - wolf->player.dir.y * sin(wolf->rot_speed);
    	wolf->player.dir.y = old_dir_x * sin(wolf->rot_speed) + wolf->player.dir.y * cos(wolf->rot_speed);
    	wolf->player.plane.x = wolf->player.plane.x * cos(wolf->rot_speed) - wolf->player.plane.y * sin(wolf->rot_speed);
    	wolf->player.plane.y = old_plane_x * sin(wolf->rot_speed) + wolf->player.plane.y * cos(wolf->rot_speed);
	}
	ray_casting(wolf);
}

int		key_press(int key, void *param)
{
	t_wolf *wolf;

	//ft_printf("key pressed = %d\n", key);
	wolf = (t_wolf *)param;
	if (key == MAIN_PAD_ESC)
		close_wolf(wolf);
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
