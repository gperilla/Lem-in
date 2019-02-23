/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 13:26:38 by gperilla          #+#    #+#             */
/*   Updated: 2018/02/16 19:01:56 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	calc_dist_max(t_env *env)
{
	int i;

	i = -1;
	while (++i < env->nb_rooms)
		if (env->rooms[i].dist != INT_MAX)
			env->distmax = ft_max(env->distmax, env->rooms[i].dist);
}

static void	incomiiing(t_env *env, int r, int dist, int *launched)
{
	while (++env->j < env->rooms[r].nbn && env->rooms[r].ants > 0)
	{
		if (env->rooms[env->rooms[r].next[env->j]].dist
				<= env->rooms[r].dist + dist
				&& (env->rooms[env->rooms[r].next[env->j]].ants
					== 0 || env->rooms[env->rooms[r].next[env->j]].soe == 'e'))
		{
			*launched = 1;
			env->ants[env->i].room = env->rooms[r].next[env->j];
			env->rooms[env->rooms[r].next[env->j]].ants += 1;
			env->rooms[r].ants -= 1;
			env->ants[env->i].moved = 1;
			ft_printf("L%d-%s ", env->i + 1,
					env->rooms[env->rooms[r].next[env->j]].name);
			while (++env->i < env->nb_ants)
				if (env->ants[env->i].room == r && !env->ants[env->i].moved)
					break ;
			if (env->rooms[env->rooms[r].next[env->j]].soe == 'e')
				--env->j;
		}
		if (env->i >= env->nb_ants)
			break ;
	}
}

static void	i_like_to_move_it_move_it(t_env *env, int r)
{
	int launched;
	int dist;

	env->i = -1;
	while (++env->i < env->nb_ants)
		if (env->ants[env->i].room == r && !env->ants[env->i].moved)
			break ;
	dist = -1;
	while (env->rooms[r].ants > 0 && env->i < env->nb_ants
			&& dist < ft_max(0, env->rooms[r].ants - env->rooms[r].nbninf))
	{
		launched = 0;
		env->j = -1;
		incomiiing(env, r, dist, &launched);
		++dist;
	}
}

static void	how_far_i_ll_go(t_env *env, int e)
{
	int i;
	int dist;

	while (env->rooms[e].ants < env->nb_ants)
	{
		i = -1;
		while (++i < env->nb_ants)
			env->ants[i].moved = 0;
		dist = 0;
		while (++dist < env->distmax + 1)
		{
			i = -1;
			while (++i < env->nb_rooms)
				if ((env->rooms[i].dist == dist && env->rooms[i].soe != 's')
						&& env->rooms[i].ants > 0)
					i_like_to_move_it_move_it(env, i);
		}
		i = -1;
		while (++i < env->nb_rooms)
			if ((env->rooms[i].soe == 's')
					&& env->rooms[i].ants > 0)
				i_like_to_move_it_move_it(env, i);
		ft_printf("\n");
	}
}

void		insert_resolv_algorithm_here(t_env *env)
{
	int s;
	int e;

	calc_dist_max(env);
	s = -1;
	while (env->rooms[++s].soe != 's')
		continue;
	e = -1;
	while (env->rooms[++e].soe != 'e')
		continue;
	ft_printf("\n");
	how_far_i_ll_go(env, e);
}
