/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 08:25:40 by gperilla          #+#    #+#             */
/*   Updated: 2018/02/16 18:06:47 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft/libft.h"

typedef struct	s_ant
{
	int		room;
	int		moved;
}				t_ant;

typedef struct	s_pipe
{
	char	*in;
	char	*out;
}				t_pipe;

typedef struct	s_room
{
	char	*name;
	int		dist;
	int		nbn;
	int		nbninf;
	int		*next;
	int		ants;
	char	soe;
	int		x;
	int		y;
}				t_room;

typedef struct	s_env
{
	int		nb_ants;
	char	*tmprooms;
	int		nb_rooms;
	t_room	*rooms;
	char	*tmppipes;
	int		nb_pipes;
	t_pipe	*pipes;
	t_ant	*ants;
	int		distmax;
	int		i;
	int		j;
}				t_env;

void			game_over_man_game_over(t_env *env, char *line);

void			i_m_recording_everything(t_env *env);

void			init_rooms(t_env *env);

void			j_ai_toujours_prefere_aux_voisins_mes_voisines(t_env *env);

void			insert_resolv_algorithm_here(t_env *env);

void			i_can_go_the_distance(t_env *env);

void			verif_road(t_env *env);

void			init_ants(t_env *env);

#endif
