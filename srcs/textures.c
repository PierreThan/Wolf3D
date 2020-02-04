/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyczyns <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 13:56:39 by atyczyns          #+#    #+#             */
/*   Updated: 2020/01/22 18:50:52 by atyczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	init_texture(t_wolf *wolf)
{
	int		x;
	int		y;
	int		xcolor;
	int		ycolor;
	int		xycolor;

	x = -1;
	if (!(wolf->texture.text_map = (int **)ft_memalloc(sizeof(int *) * 8)))
		free_wolf(wolf);
	while (++x < 8)
		if (!(wolf->texture.text_map[x]
			= (int *)ft_memalloc(sizeof(int) * TEXT_WIDTH * TEXT_HEIGHT)))
			free_wolf(wolf);
	x = -1;
	while (++x < TEXT_WIDTH)
	{
		y = -1;
		while (++y < TEXT_HEIGHT)
		{
			xcolor = (x * 256 / TEXT_WIDTH) ^ (y * 256 / TEXT_HEIGHT);
			ycolor = y * 256 / TEXT_HEIGHT;
			xycolor = y * 128 / TEXT_HEIGHT + x * 128 / TEXT_WIDTH;
			wolf->texture.text_map[0][TEXT_WIDTH * y + x]
				= 65536 * 254 * (x != y && x != TEXT_WIDTH - y);
			wolf->texture.text_map[1][TEXT_WIDTH * y + x]
				= xycolor + 256 * xycolor + 65536 * xycolor;
			wolf->texture.text_map[2][TEXT_WIDTH * y + x]
				= 256 * xycolor + 65536 * xycolor;
			wolf->texture.text_map[3][TEXT_WIDTH * y + x]
				= xcolor + 256 * xcolor + 65536 * xycolor;
			wolf->texture.text_map[4][TEXT_WIDTH * y + x] = 256 * xcolor;
			wolf->texture.text_map[5][TEXT_WIDTH * y + x] 
				= 65536 * 192 * (x % 16 && y % 16);;
			wolf->texture.text_map[6][TEXT_WIDTH * y + x] = 65536 * ycolor;
			wolf->texture.text_map[7][TEXT_WIDTH * y + x] 
				= 128 + 256 * 128 + 65536 * 128;
		}
	}
}

void	free_textures(t_wolf *wolf)
{
	int	i;

	i = -1;
	if (wolf)
	{
		if (wolf->texture.text_map)
		{
			while (++i < 8)
			{
				if (wolf->texture.text_map[i])
					ft_memdel(wolf->texture.text_map[i]);
			}
			ft_memdel(wolf->texture.text_map);
		}
	}
}
