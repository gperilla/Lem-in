/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putpixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:21:01 by gperilla          #+#    #+#             */
/*   Updated: 2018/02/15 14:46:24 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_visu.h"

void	my_putpixel(t_visuenv *env, int x, int y, int color)
{
	int		pos;
	int8_t	mask;

	if ((x >= 0 && x < 1920) && (y >= 0 && y < 1080))
	{
		pos = (y * env->s_l + x * (env->bpp / 8));
		mask = color;
		env->pix[pos] = mask;
		color = color >> 8;
		mask = color;
		env->pix[pos + 1] = mask;
		color = color >> 8;
		mask = color;
		env->pix[pos + 2] = mask;
		color = color >> 8;
		mask = color;
		env->pix[pos + 3] = mask;
	}
}
