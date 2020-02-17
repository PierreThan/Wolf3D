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

static void	init_texture3(t_wolf *wolf)
{
	t_img	*tmp;
	int		*w;
	int		*h;

	w = &(wolf->texture.width);
	h = &(wolf->texture.height);
	tmp = wolf->texture.img;
	while (tmp && tmp->ptr != NULL)
		tmp++;
	tmp->ptr = mlx_xpm_file_to_image(wolf->mlx.mlx_ptr, PURPLESTONE, w, h);
	tmp->data = (int*)mlx_get_data_addr(
		tmp->ptr, &(tmp->bpp), &(tmp->size_l), &(tmp->endian));
}

static void	init_texture2(t_wolf *wolf)
{
	t_img	*tmp;
	int		*w;
	int		*h;

	w = &(wolf->texture.width);
	h = &(wolf->texture.height);
	tmp = wolf->texture.img;
	while (tmp && tmp->ptr != NULL)
		tmp++;
	tmp->ptr = mlx_xpm_file_to_image(wolf->mlx.mlx_ptr, MOSSY, w, h);
	tmp->data = (int*)mlx_get_data_addr(
		tmp->ptr, &(tmp->bpp), &(tmp->size_l), &(tmp->endian));
	tmp++;
	tmp->ptr = mlx_xpm_file_to_image(wolf->mlx.mlx_ptr, COLORSTONE, w, h);
	tmp->data = (int*)mlx_get_data_addr(
		tmp->ptr, &(tmp->bpp), &(tmp->size_l), &(tmp->endian));
	tmp++;
	tmp->ptr = mlx_xpm_file_to_image(wolf->mlx.mlx_ptr, GREYSTONE, w, h);
	tmp->data = (int*)mlx_get_data_addr(
		tmp->ptr, &(tmp->bpp), &(tmp->size_l), &(tmp->endian));
	tmp++;
	tmp->ptr = mlx_xpm_file_to_image(wolf->mlx.mlx_ptr, BLUESTONE, w, h);
	tmp->data = (int*)mlx_get_data_addr(
		tmp->ptr, &(tmp->bpp), &(tmp->size_l), &(tmp->endian));
	init_texture3(wolf);
}

void		init_texture(t_wolf *wolf)
{
	t_img	*tmp;
	int		*w;
	int		*h;

	if (!(wolf->texture.img =
		(t_img *)ft_memalloc(sizeof(t_img) * NB_TEXTURES)))
		free_wolf(wolf);
	wolf->texture.width = 64;
	wolf->texture.height = 64;
	w = &(wolf->texture.width);
	h = &(wolf->texture.height);
	tmp = wolf->texture.img;
	tmp->ptr = mlx_xpm_file_to_image(wolf->mlx.mlx_ptr, BRICK, w, h);
	tmp->data = (int*)mlx_get_data_addr(
		tmp->ptr, &(tmp->bpp), &(tmp->size_l), &(tmp->endian));
	tmp++;
	tmp->ptr = mlx_xpm_file_to_image(wolf->mlx.mlx_ptr, REDBRICK, w, h);
	tmp->data = (int*)mlx_get_data_addr(
		tmp->ptr, &(tmp->bpp), &(tmp->size_l), &(tmp->endian));
	tmp++;
	tmp->ptr = mlx_xpm_file_to_image(wolf->mlx.mlx_ptr, WOOD, w, h);
	tmp->data = (int*)mlx_get_data_addr(
		tmp->ptr, &(tmp->bpp), &(tmp->size_l), &(tmp->endian));
	tmp++;
	init_texture2(wolf);
}

void		free_textures(t_wolf *wolf)
{
	int		i;
	t_img	*tmp;

	i = -1;
	if (wolf)
	{
		if (wolf->texture.img)
		{
			while (++i < NB_TEXTURES)
			{
				tmp = wolf->texture.img[NB_TEXTURES - 1 - i].ptr;
				if (tmp)
					mlx_destroy_image(wolf->mlx.mlx_ptr,
						wolf->texture.img[NB_TEXTURES - 1 - i].ptr);
			}
			ft_memdel((void**)(&wolf->texture.img));
		}
	}
}
