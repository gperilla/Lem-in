/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   les_voisins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 13:24:25 by gperilla          #+#    #+#             */
/*   Updated: 2018/02/16 13:35:09 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	you_re_welcome(t_env *env, int r, char *name)
{
	int i;
	int j;

	i = -1;
	while (env->rooms[r].next[++i] != -1)
		continue;
	j = -1;
	while (!ft_strequ(env->rooms[++j].name, name))
		continue;
	env->rooms[r].next[i] = j;
}

static void	vois1(t_env *env, int i, char *namein, char *nameout)
{
	int j;

	namein = env->pipes[i].in;
	nameout = env->pipes[i].out;
	j = -1;
	while (++j < env->nb_rooms)
		if (ft_strequ(env->rooms[j].name, namein)
				|| ft_strequ(env->rooms[j].name, nameout))
			env->rooms[j].nbn += 1;
}

static void	vois2(t_env *env, int i)
{
	int j;

	if (!(env->rooms[i].next = malloc(sizeof(int) * env->rooms[i].nbn)))
		game_over_man_game_over(env, NULL);
	j = -1;
	while (++j < env->rooms[i].nbn)
		env->rooms[i].next[j] = -1;
}

static void	vois3(t_env *env, int i, char *namein, char *nameout)
{
	int j;

	namein = env->pipes[i].in;
	nameout = env->pipes[i].out;
	j = -1;
	while (++j < env->nb_rooms)
	{
		if (ft_strequ(env->rooms[j].name, namein))
			you_re_welcome(env, j, nameout);
		else if (ft_strequ(env->rooms[j].name, nameout))
			you_re_welcome(env, j, namein);
	}
}

void		j_ai_toujours_prefere_aux_voisins_mes_voisines(t_env *env)
{
	int		i;
	char	*namein;
	char	*nameout;

	namein = NULL;
	nameout = NULL;
	i = -1;
	while (++i < env->nb_pipes)
		vois1(env, i, namein, nameout);
	i = -1;
	while (++i < env->nb_rooms)
		vois2(env, i);
	i = -1;
	while (++i < env->nb_pipes)
		vois3(env, i, namein, nameout);
}
