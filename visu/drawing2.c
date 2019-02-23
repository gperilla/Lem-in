/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 16:00:01 by gperilla          #+#    #+#             */
/*   Updated: 2018/02/19 16:27:13 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_visu.h"

static void	draw_ants(t_visuenv *env)
{
	int		i;
	int		y;
	int		x;
	void	*antimg;

	antimg = mlx_xpm_file_to_image(env->mlx, "ant.xpm", &x, &y);
	i = -1;
	while (++i < env->penv.nb_ants)
	{
		y = (env->penv.rooms[env->penv.ants[i].room].y) * (1080 /
				(env->ymax + 1)) + (1080 / (env->ymax + 1) / 2) - 10;
		x = (env->penv.rooms[env->penv.ants[i].room].x) * (1920 /
					(env->xmax + 1)) + (1920 / (env->xmax + 1) / 2) - 10;
		mlx_put_image_to_window(env->mlx, env->win, antimg, x, y);
	}
}

static void	draw_names(t_visuenv *env)
{
	char	*str;
	int		i;
	int		y;
	int		x;

	i = -1;
	while (++i < env->penv.nb_rooms)
	{
		str = ft_strdup(env->penv.rooms[i].name);
		if (env->penv.rooms[i].soe == 's')
			str = ft_strjoin_free(str, " (start)", 1);
		else if (env->penv.rooms[i].soe == 'e')
			str = ft_strjoin_free(str, " (end)", 1);
		y = env->penv.rooms[i].y * (1080 / (env->ymax + 1)) + 20;
		x = env->penv.rooms[i].x * (1920 / (env->xmax + 1)) + 20;
		mlx_string_put(env->mlx, env->win, x, y, 0xFFFFFF, str);
		free(str);
	}
}

void		draw_pipes(t_visuenv *env)
{
	int i;
	int s1;
	int s2;

	i = -1;
	while (++i < env->penv.nb_pipes)
	{
		s1 = -1;
		while (!ft_strequ(env->penv.rooms[++s1].name, env->penv.pipes[i].in))
			continue;
		s2 = -1;
		while (!ft_strequ(env->penv.rooms[++s2].name, env->penv.pipes[i].out))
			continue;
		env->in.x = (env->penv.rooms[s1].x * (1920 / (env->xmax + 1))
				+ (1920 / (env->xmax + 1) / 2));
		env->in.y = env->penv.rooms[s1].y * (1080 / (env->ymax + 1))
			+ (1080 / (env->ymax + 1) / 2);
		env->out.x = (env->penv.rooms[s2].x * (1920 / (env->xmax + 1))
				+ (1920 / (env->xmax + 1) / 2));
		env->out.y = env->penv.rooms[s2].y * (1080 / (env->ymax + 1))
			+ (1080 / (env->ymax + 1) / 2);
		draw_line(env, &(env->in), &(env->out), 0x669933);
	}
}

void		next_move(t_visuenv *env)
{
	int x;
	int y;

	mlx_destroy_image(env->mlx, env->img);
	env->img = mlx_xpm_file_to_image(env->mlx, "rsz_terre.xpm", &x, &y);
	env->pix = mlx_get_data_addr(env->img, &env->bpp, &env->s_l, &env->endian);
	env->turn = ft_min(env->turn + 1, env->nb_turn);
	if (!env->stop && env->turn >= 0)
		ft_printf("\nturn %d of %d\n", env->turn + 1, env->nb_turn + 1);
	draw_pipes(env);
	draw_rooms(env);
	if (env->turn >= 0)
		draw_movement(env);
	if (env->turn == env->nb_turn)
		env->stop = 1;
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	draw_names(env);
	draw_ants(env);
}
