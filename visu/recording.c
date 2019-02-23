/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recording.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 16:01:38 by gperilla          #+#    #+#             */
/*   Updated: 2018/02/19 17:05:28 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_visu.h"

static void	room_soe_name(t_visuenv *env, int i, int *j)
{
	int k;

	env->penv.rooms[i].soe = 'o';
	if (env->penv.tmprooms[*j] == '#' && (env->penv.tmprooms[*j + 1] == 's'
		|| env->penv.tmprooms[*j + 1] == 'e'))
	{
		env->penv.rooms[i].soe = env->penv.tmprooms[*j + 1];
		*j += 2;
	}
	if (env->penv.rooms[i].soe == 'e')
		env->penv.rooms[i].dist = 0;
	else if (env->penv.rooms[i].soe == 's')
		env->penv.rooms[i].ants = env->penv.nb_ants;
	k = *j;
	while (env->penv.tmprooms[++*j] != ' ')
		if (!(env->penv.tmprooms[*j]))
			exit(0);
	env->penv.rooms[i].name = ft_strsub(env->penv.tmprooms, k, *j - k);
}

static void	rroommss(t_visuenv *env, int i, int *j)
{
	env->penv.rooms[i].next = NULL;
	env->penv.rooms[i].nbn = 0;
	env->penv.rooms[i].dist = INT_MAX;
	env->penv.rooms[i].ants = 0;
	room_soe_name(env, i, j);
	if (!(ft_isdigit(env->penv.tmprooms[*j + 1]) || (env->penv.tmprooms[*j
				+ 1] == '-' && ft_isdigit(env->penv.tmprooms[*j + 2]))))
		exit(0);
	env->penv.rooms[i].x = ft_atoi(env->penv.tmprooms + *j);
	env->xmax = ft_max(env->xmax, env->penv.rooms[i].x);
	while (env->penv.tmprooms[++*j] != ' ')
		if (!(env->penv.tmprooms[*j]))
			exit(0);
	if (!(ft_isdigit(env->penv.tmprooms[*j + 1]) || (env->penv.tmprooms[*j
				+ 1] == '-' && ft_isdigit(env->penv.tmprooms[*j + 2]))))
		exit(0);
	env->penv.rooms[i].y = ft_atoi(env->penv.tmprooms + *j);
	env->ymax = ft_max(env->ymax, env->penv.rooms[i].y);
	while (env->penv.tmprooms[++*j] != '\n')
		if (!(env->penv.tmprooms[*j]))
			exit(0);
	++*j;
}

static void	ppiippeess(t_visuenv *env, int i, int *j)
{
	int k;

	k = *j + 1;
	while (env->penv.tmppipes[++*j] != '-')
		if (!(env->penv.tmppipes[*j]))
			exit(0);
	env->penv.pipes[i].in = ft_strsub(env->penv.tmppipes, k, *j - k);
	k = *j + 1;
	while (env->penv.tmppipes[++*j] != '\n')
		if (!(env->penv.tmppipes[*j]))
			exit(0);
	env->penv.pipes[i].out = ft_strsub(env->penv.tmppipes, k, *j - k);
}

void		ii_m_recording_everything(t_visuenv *env)
{
	int i;
	int j;

	if (!(env->penv.rooms = malloc(sizeof(t_room) * env->penv.nb_rooms)))
		exit(0);
	i = -1;
	j = 0;
	while (++i < env->penv.nb_rooms)
		rroommss(env, i, &j);
	if (!(env->penv.pipes = malloc(sizeof(t_pipe) * env->penv.nb_pipes)))
		exit(0);
	i = -1;
	j = -1;
	while (++i < env->penv.nb_pipes)
		ppiippeess(env, i, &j);
	iinit_ants(env);
}

void		iinit_ants(t_visuenv *env)
{
	int i;
	int s;

	s = -1;
	while (env->penv.rooms[++s].soe != 's')
		continue;
	env->penv.ants = malloc(sizeof(t_ant) * env->penv.nb_ants);
	i = -1;
	while (++i < env->penv.nb_ants)
		env->penv.ants[i].room = s;
}
