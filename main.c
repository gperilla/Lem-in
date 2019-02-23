/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 03:49:39 by gperilla          #+#    #+#             */
/*   Updated: 2018/02/20 09:38:12 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	game_over_man_game_over(t_env *env, char *line)
{
	if (line)
	{
		ft_printf("%s\n", line);
		ft_strdel(&line);
	}
	free(env);
	ft_printf("ERROR\n");
	exit(0);
}

void	init_env(t_env *env)
{
	char *line;

	env->distmax = 0;
	env->nb_ants = 0;
	env->tmprooms = ft_strdup("");
	env->nb_rooms = 0;
	env->rooms = NULL;
	env->tmppipes = ft_strdup("");
	env->nb_pipes = 0;
	env->pipes = NULL;
	if (!(get_next_line(0, &line) > 0))
		game_over_man_game_over(env, line);
	while (line[0] == '#')
	{
		free(line);
		if (!(get_next_line(0, &line)))
			game_over_man_game_over(env, line);
	}
	if ((env->nb_ants = ft_atoi(line)) <= 0)
		game_over_man_game_over(env, line);
	ft_printf("%s\n", line);
	ft_strdel(&line);
}

int		rooms_or_pipes(t_env *env, char *line)
{
	int i;

	i = -1;
	while (line[++i] != ' ' && line[i] != '-')
		if (!line[i])
			return (0);
	if (line[i] == ' ' && !env->nb_pipes)
	{
		env->tmprooms = ft_strjoin_free(env->tmprooms, line, 1);
		env->tmprooms = ft_strjoin_free(env->tmprooms, "\n", 1);
		env->nb_rooms += 1;
	}
	else if (line[i] == '-')
	{
		env->tmppipes = ft_strjoin_free(env->tmppipes, line, 1);
		env->tmppipes = ft_strjoin_free(env->tmppipes, "\n", 1);
		env->nb_pipes += 1;
	}
	else
		return (0);
	return (1);
}

void	main_while(t_env *env)
{
	char	*line;
	int		flagstart;
	int		flagend;

	flagstart = 0;
	flagend = 0;
	while (get_next_line(0, &line) > 0)
	{
		if (line[0] == '#' && line[1] == '#')
		{
			if (ft_strequ(line, "##start") && !flagstart && !env->nb_pipes)
				env->tmprooms = ft_strjoin_free(env->tmprooms, "#s", 1);
			else if (ft_strequ(line, "##end") && !flagend && !env->nb_pipes)
				env->tmprooms = ft_strjoin_free(env->tmprooms, "#e", 1);
		}
		else if (line[0] != '#')
			if (!(rooms_or_pipes(env, line)))
				return ;
		ft_printf("%s\n", line);
		ft_strdel(&line);
	}
	if (!env->nb_rooms || !env->nb_pipes)
		game_over_man_game_over(env, NULL);
}

int		main(void)
{
	t_env	*env;

	if (!(env = malloc(sizeof(t_env))))
		game_over_man_game_over(env, NULL);
	init_env(env);
	main_while(env);
	i_m_recording_everything(env);
	j_ai_toujours_prefere_aux_voisins_mes_voisines(env);
	i_can_go_the_distance(env);
	verif_road(env);
	init_ants(env);
	insert_resolv_algorithm_here(env);
	return (0);
}
