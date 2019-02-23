/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_visu.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 15:19:41 by gperilla          #+#    #+#             */
/*   Updated: 2018/02/19 16:31:05 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_VISU_H
# define LEMIN_VISU_H

# include "../lemin.h"
# include "minilibx_macos/mlx.h"

typedef struct	s_point
{
	int x;
	int y;
}				t_point;

typedef struct	s_line
{
	int x;
	int y;
	int dx;
	int dy;
	int xdir;
	int ydir;
	int p;
}				t_line;

typedef struct	s_viuenv
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*pix;
	void	*bckg;
	char	*dirt;
	int		bpp;
	int		s_l;
	int		endian;
	char	*game;
	int		nb_turn;
	int		turn;
	t_env	penv;
	int		xmax;
	int		ymax;
	int		stop;
	t_point	in;
	t_point	out;
}				t_visuenv;

void			my_putpixel(t_visuenv *env, int x, int y, int color);

void			draw_line(t_visuenv *ev, t_point *pt1, t_point *pt2, int color);

void			draw_circle(t_visuenv *env, t_point pt, int radius, int color);

void			draw_pipes(t_visuenv *env);

void			draw_rooms(t_visuenv *env);

void			draw_movement(t_visuenv *env);

void			next_move(t_visuenv *env);

void			ii_m_recording_everything(t_visuenv *env);

void			iinit_ants(t_visuenv *env);

#endif
