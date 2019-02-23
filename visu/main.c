/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 15:54:01 by gperilla          #+#    #+#             */
/*   Updated: 2018/02/19 17:14:13 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin_visu.h"

int		my_key_events(int key, t_visuenv *env)
{
	(void)env;
	if (key == 53)
	{
		if (fork() == 0)
			system("killall afplay");
		exit(0);
	}
	if (key == 124)
		next_move(env);
	return (0);
}

void	init_env(t_visuenv *env)
{
	env->penv.nb_ants = 0;
	env->penv.tmprooms = ft_strdup("");
	env->penv.nb_rooms = 0;
	env->penv.rooms = NULL;
	env->penv.tmppipes = ft_strdup("");
	env->penv.nb_pipes = 0;
	env->penv.pipes = NULL;
	env->xmax = 0;
	env->ymax = 0;
	env->game = ft_strdup("");
	env->stop = 0;
	env->nb_turn = -1;
	env->turn = -2;
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, 1920, 1080, "Visu");
	env->img = mlx_new_image(env->mlx, 1920, 1080);
	env->pix = mlx_get_data_addr(env->img, &env->bpp, &env->s_l, &env->endian);
	if (fork() == 0)
	{
		system("afplay music.mp3");
		exit(0);
	}
}

void	rooms_or_pipes(t_visuenv *env, char *line)
{
	int i;

	i = -1;
	while (line[++i] != ' ' && line[i] != '-')
		if (!line[i])
			exit(0);
	if (line[i] == ' ' && !env->penv.nb_pipes)
	{
		env->penv.tmprooms = ft_strjoin_free(env->penv.tmprooms, line, 1);
		env->penv.tmprooms = ft_strjoin_free(env->penv.tmprooms, "\n", 1);
		env->penv.nb_rooms += 1;
	}
	else if (line[i] == '-')
	{
		env->penv.tmppipes = ft_strjoin_free(env->penv.tmppipes, line, 1);
		env->penv.tmppipes = ft_strjoin_free(env->penv.tmppipes, "\n", 1);
		env->penv.nb_pipes += 1;
	}
	else
		exit(0);
}

void	main_while(t_visuenv *env)
{
	char	*line;

	while (get_next_line(0, &line) > 0)
	{
		if (line[0] == '\0')
			break ;
		if (line[0] == '#' && line[1] == '#')
		{
			if (ft_strequ(line, "##start") && !env->penv.nb_pipes)
				env->penv.tmprooms =
					ft_strjoin_free(env->penv.tmprooms, "#s", 1);
			else if (ft_strequ(line, "##end") && !env->penv.nb_pipes)
				env->penv.tmprooms =
					ft_strjoin_free(env->penv.tmprooms, "#e", 1);
		}
		else if (line[0] != '#')
			rooms_or_pipes(env, line);
		ft_printf("%s\n", line);
		ft_strdel(&line);
	}
	if (line)
		free(line);
	if (!env->penv.nb_rooms || !env->penv.nb_pipes)
		exit(0);
}

int		main(void)
{
	t_visuenv	*env;
	char		*line;

	if (!(env = malloc(sizeof(t_visuenv))))
		exit(0);
	init_env(env);
	get_next_line(0, &line);
	env->penv.nb_ants = ft_atoi(line);
	ft_printf("%s\n", line);
	free(line);
	main_while(env);
	ii_m_recording_everything(env);
	ft_printf("\n");
	while (get_next_line(0, &line) > 0)
	{
		ft_printf("%s\n", line);
		line = ft_strjoin_free(line, "\n", 1);
		env->game = ft_strjoin_free(env->game, line, 3);
		++env->nb_turn;
	}
	next_move(env);
	mlx_key_hook(env->win, my_key_events, env);
	mlx_loop(env->mlx);
	return (0);
}
