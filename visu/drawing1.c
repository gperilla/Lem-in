/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 15:58:13 by gperilla          #+#    #+#             */
/*   Updated: 2018/02/19 17:00:53 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_visu.h"
#include <math.h>

void		draw_rooms(t_visuenv *env)
{
	int			i;
	int			color;
	t_point		pt;
	int			sx;
	int			sy;

	i = -1;
	while (++i < env->penv.nb_rooms)
	{
		sy = 1080 / (env->ymax + 1);
		sx = 1920 / (env->xmax + 1);
		pt.y = env->penv.rooms[i].y * (1080 / (env->ymax + 1)) + sy / 2;
		pt.x = env->penv.rooms[i].x * (1920 / (env->xmax + 1)) + sx / 2;
		color = 0x669933;
		if (env->penv.rooms[i].soe == 's')
			color = 0x0099FF;
		else if (env->penv.rooms[i].soe == 'e')
			color = 0x006600;
		while (--sx > 0 && --sy > 0)
			draw_circle(env, pt, ft_min(sx, sy) / 2, color);
	}
}

static void	normoving(t_visuenv *env, int s1, int s2)
{
	env->in.x = (env->penv.rooms[s1].x * (1920 / (env->xmax + 1))
			+ (1920 / (env->xmax + 1) / 2));
	env->in.y = env->penv.rooms[s1].y * (1080 / (env->ymax + 1))
		+ (1080 / (env->ymax + 1) / 2);
	env->out.x = (env->penv.rooms[s2].x * (1920 / (env->xmax + 1))
			+ (1920 / (env->xmax + 1) / 2));
	env->out.y = env->penv.rooms[s2].y * (1080 / (env->ymax + 1))
		+ (1080 / (env->ymax + 1) / 2);
	draw_line(env, &(env->in), &(env->out), 0x777777);
}

static void	moving(t_visuenv *env, int *i)
{
	int		x;
	int		y;
	int		s1;
	int		s2;
	char	*name;

	y = ft_atoi(env->game + *i);
	s1 = env->penv.ants[y - 1].room;
	--env->penv.rooms[s1].ants;
	while (env->game[++*i] != '-')
		continue;
	x = *i + 1;
	while (env->game[++*i] != ' ')
		continue;
	name = ft_strsub(env->game, x, *i - x);
	if (!env->stop)
		ft_printf("ant %d to %s\n", y, name);
	x = -1;
	while (!ft_strequ(env->penv.rooms[++x].name, name))
		continue;
	env->penv.ants[y - 1].room = x;
	s2 = env->penv.ants[y - 1].room;
	++env->penv.rooms[s2].ants;
	normoving(env, s1, s2);
}

void		draw_movement(t_visuenv *env)
{
	int x;
	int i;

	x = 0;
	i = -1;
	while (x < env->turn)
		if (env->game[++i] == '\n')
			++x;
	while (env->game[++i] != '\n')
		if (ft_isdigit(env->game[i]))
			moving(env, &i);
}
