/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_the_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 13:29:16 by gperilla          #+#    #+#             */
/*   Updated: 2018/02/16 18:08:57 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	init_rooms(t_env *env)
{
	env->rooms[env->i].next = NULL;
	env->rooms[env->i].nbn = 0;
	env->rooms[env->i].dist = INT_MAX;
	env->rooms[env->i].ants = 0;
}

void	insert_dist_algo_here(t_env *env, int r, int dist)
{
	int i;

	if (env->rooms[r].dist <= dist)
		return ;
	env->rooms[r].dist = dist;
	if (env->rooms[r].soe == 's')
		return ;
	i = -1;
	while (++i < env->rooms[r].nbn)
		insert_dist_algo_here(env, env->rooms[r].next[i], dist + 1);
}

void	i_can_go_the_distance(t_env *env)
{
	int i;
	int j;

	i = -1;
	while (++i < env->nb_rooms)
		if (env->rooms[i].soe == 'e')
		{
			j = -1;
			while (++j < env->rooms[i].nbn)
				insert_dist_algo_here(env, env->rooms[i].next[j], 1);
		}
}

void	verif_road(t_env *env)
{
	int i;
	int j;
	int in;

	i = -1;
	in = 0;
	while (++i < env->nb_rooms)
	{
		env->rooms[i].nbninf = 0;
		j = -1;
		while (++j < env->rooms[i].nbn)
			if (env->rooms[env->rooms[i].next[j]].dist < env->rooms[i].dist)
				++env->rooms[i].nbninf;
		if (env->rooms[i].soe == 's' && env->rooms[i].dist != INT_MAX)
			in += 1;
	}
	if (in != 1)
		game_over_man_game_over(env, NULL);
}

void	init_ants(t_env *env)
{
	int i;
	int a;

	if (!(env->ants = malloc(sizeof(t_ant) * env->nb_ants)))
		game_over_man_game_over(env, NULL);
	i = -1;
	while (env->rooms[++i].soe != 's')
		continue;
	a = -1;
	while (++a < env->nb_ants)
		env->ants[a].room = i;
}
