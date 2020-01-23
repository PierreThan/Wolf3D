/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2d_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyczyns <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 15:38:55 by atyczyns          #+#    #+#             */
/*   Updated: 2020/01/23 15:42:44 by atyczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/wolf3d.h>

void		vec2d_mat2d_mult(t_vec2d *vec, t_mat2d *mat)
{
	double	tmp;

	tmp = vec->x;
	vec->x = (vec->x * mat->a) + (mat->b * vec->y);
	vec->y = (tmp * mat->c) + (mat->d * vec->y);
}
