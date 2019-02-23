/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 16:30:20 by gperilla          #+#    #+#             */
/*   Updated: 2018/02/19 17:08:11 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_visu.h"

void	put_cirxel(t_visuenv *env, t_point pt, t_point pt2, int color)
{
	my_putpixel(env, pt.x + pt2.x, pt.y + pt2.y, color);
	my_putpixel(env, pt.x + pt2.y, pt.y + pt2.x, color);
	my_putpixel(env, pt.x - pt2.y, pt.y + pt2.x, color);
	my_putpixel(env, pt.x - pt2.x, pt.y + pt2.y, color);
	my_putpixel(env, pt.x - pt2.x, pt.y - pt2.y, color);
	my_putpixel(env, pt.x - pt2.y, pt.y - pt2.x, color);
	my_putpixel(env, pt.x + pt2.y, pt.y - pt2.x, color);
	my_putpixel(env, pt.x + pt2.x, pt.y - pt2.y, color);
}

void	negerr(int *y, int *err, int *dy)
{
	++*y;
	*err += *dy;
	*dy += 2;
}

void	draw_circle(t_visuenv *env, t_point pt, int radius, int color)
{
	t_point		pt2;
	int			dx;
	int			dy;
	int			err;

	pt2.x = radius - 1;
	pt2.y = 0;
	dx = 1;
	dy = 1;
	err = dx - (radius << 1);
	while (pt2.x >= pt2.y)
	{
		put_cirxel(env, pt, pt2, color);
		if (err <= 0)
			negerr(&(pt2.y), &err, &dy);
		if (err > 0)
		{
			pt2.x--;
			dx += 2;
			err += dx - (radius << 1);
		}
	}
}
