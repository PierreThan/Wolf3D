/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyczyns <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 13:56:39 by atyczyns          #+#    #+#             */
/*   Updated: 2019/12/04 16:03:27 by atyczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	put_pxl_to_img(t_wolf *wolf, int x, int y, int color)
{
	if (x < WIDTH && y < HEIGHT)
	{
	//il faut ratacher la structure wall a wolf si possible
		wolf->y_texture = abs((((y * 256 - WIDTH * 128 + wolf->wall.line_height
			* 128) * 64) / wolf->wall.line_heightght) / 256);
		ft_memcpy(wolf->mlx.img.ptr + 4 * WIDTH * y + x * 4,
			&wolf->texture.data[wolf->x_texture % 64 * wolf->texture.sizeline
			+ wolf->y_texture % 64 * wolf->texture.bpp / 8], sizeof(int));
	}
}

//recupere les textures
void	load_textures(t_wolf *wolf)
{
	int		a;
	int		b;

	a = 64;
	b = 64;
	wolf->texture.img = mlx_xpm_file_to_image(wolf->mlx.mlx_ptr, "xpm_textures/wood.xpm",
		&a, &b);
	wolf->texture.data = mlx_get_data_addr(wolf->texture.img,
		&wolf->texture.bpp, &wolf->texture.sizeline, &wolf->texture.endian);
}
