/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 13:20:47 by gperilla          #+#    #+#             */
/*   Updated: 2018/02/16 13:34:44 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	beginning_of_the_end(t_env *env, int *start, int *end)
{
	env->rooms[env->i].soe = 'o';
	if (env->tmprooms[env->j] == '#'
	&& (env->tmprooms[env->j + 1] == 's' || env->tmprooms[env->j + 1] == 'e'))
	{
		env->rooms[env->i].soe = env->tmprooms[env->j + 1];
		env->j += 2;
		if (env->tmprooms[env->j] == '#')
			game_over_man_game_over(env, NULL);
	}
	if (env->rooms[env->i].soe == 'e')
	{
		++*end;
		env->rooms[env->i].dist = 0;
	}
	else if (env->rooms[env->i].soe == 's')
	{
		++*start;
		env->rooms[env->i].ants = env->nb_ants;
	}
	if (*end > 1 || *start > 1)
		game_over_man_game_over(env, NULL);
}

static void	get_the_dataroom(t_env *env)
{
	int k;

	k = env->j;
	while (env->tmprooms[++env->j] != ' ')
		if (!(env->tmprooms[env->j]) || env->tmprooms[env->j] == '\n')
			game_over_man_game_over(env, NULL);
	env->rooms[env->i].name = ft_strsub(env->tmprooms, k, env->j - k);
	if (!(ft_isdigit(env->tmprooms[env->j + 1]) || (env->tmprooms[env->j
	+ 1] == '-' && ft_isdigit(env->tmprooms[env->j + 2]))))
		game_over_man_game_over(env, NULL);
	env->rooms[env->i].x = ft_atoi(env->tmprooms + env->j);
	while (env->tmprooms[++env->j] != ' ')
		if (!(env->tmprooms[env->j]) || env->tmprooms[env->j] == '\n')
			game_over_man_game_over(env, NULL);
	if (!(ft_isdigit(env->tmprooms[env->j + 1]) || (env->tmprooms[env->j
	+ 1] == '-' && ft_isdigit(env->tmprooms[env->j + 2]))))
		game_over_man_game_over(env, NULL);
	env->rooms[env->i].y = ft_atoi(env->tmprooms + env->j);
	while (env->tmprooms[++env->j] != '\n')
		if (!(env->tmprooms[env->j]))
			game_over_man_game_over(env, NULL);
	++env->j;
}

static void	roorooms(t_env *env)
{
	static int start;
	static int end;

	init_rooms(env);
	beginning_of_the_end(env, &start, &end);
	get_the_dataroom(env);
}

static void	tailler_les_pipes(t_env *env)
{
	int k;

	k = 0;
	while (++env->i < env->nb_pipes)
	{
		k = env->j + 1;
		while (env->tmppipes[++env->j] != '-')
			if (!(env->tmppipes[env->j]) || env->tmppipes[env->j] == '\n')
				game_over_man_game_over(env, NULL);
		env->pipes[env->i].in = ft_strsub(env->tmppipes, k, env->j - k);
		k = 0;
		while (!ft_strequ(env->rooms[k].name, env->pipes[env->i].in))
			if (++k == env->nb_rooms)
				game_over_man_game_over(env, NULL);
		k = env->j + 1;
		while (env->tmppipes[++env->j] != '\n')
			if (!(env->tmppipes[env->j]) || env->tmppipes[env->j] == '-')
				game_over_man_game_over(env, NULL);
		env->pipes[env->i].out = ft_strsub(env->tmppipes, k, env->j - k);
		k = 0;
		while (!ft_strequ(env->rooms[k].name, env->pipes[env->i].in))
			if (++k == env->nb_rooms)
				game_over_man_game_over(env, NULL);
	}
}

void		i_m_recording_everything(t_env *env)
{
	if (!(env->rooms = (t_room*)malloc(sizeof(t_room) * env->nb_rooms)))
		game_over_man_game_over(env, NULL);
	env->i = -1;
	env->j = 0;
	while (++env->i < env->nb_rooms)
		roorooms(env);
	if (!(env->pipes = (t_pipe*)malloc(sizeof(t_pipe) * env->nb_pipes)))
		game_over_man_game_over(env, NULL);
	env->i = -1;
	env->j = -1;
	tailler_les_pipes(env);
}
