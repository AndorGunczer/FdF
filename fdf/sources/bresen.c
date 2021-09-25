/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 18:40:35 by agunczer          #+#    #+#             */
/*   Updated: 2021/09/25 15:06:45 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	bresen_ctor(struct s_fdf *bresen, double isoX1, double isoX0, double isoY1, double isoY0)
{
	bresen->x_step = 0;
	bresen->y_step = 0;
	bresen->dx = fabs(isoX1 - isoX0);
	if (isoX0 < isoX1)
		bresen->sx = 1;
	else
		bresen->sx = (-1);
	bresen->dy = fabs(isoY1 - isoY0);
	if (isoY0 < isoY1)
		bresen->sy = 1;
	else
		bresen->sy = (-1);
	if (bresen->dx > bresen->dy)
		bresen->err = bresen->dx / 2.0;
	else
		bresen->err = -(bresen->dy) / 2.0;
}

void	put_pixel(struct s_fdf *s, double isoX0, double isoY0)
{
	if (round(isoX0) + round(s->center_x + s->mov_x) < s->screen_w
		&& round(isoX0) + round(s->center_x + s->mov_x) > 0
		&& round(isoY0) + round(s->center_y + s->mov_y) < s->screen_h
		&& round(isoY0) + round(s->center_y + s->mov_y) > 0)
	{
		s->position = ((round(isoX0) + round(s->center_x + s->mov_x)) * 4)
			+ (s->line_length * (round(isoY0) + round(s->center_y + s->mov_y)));
		s->imgptr = s->addr + s->position;
		color(s->imgptr);
	}
}

void	bresen_line(struct s_fdf *s, double isoX1, double isoX0, double isoY1, double isoY0)
{
	bresen_ctor(s, isoX1, isoX0, isoY1, isoY0);
	while (s->x_step <= s->dx)
	{
		put_pixel(s, isoX0, isoY0);
		s->e2 = s->err;
		if (s->e2 > -s->dx)
		{
			s->err -= s->dy;
			isoX0 += s->sx;
			(s->x_step)++;
		}
		if (s->e2 < s->dy)
		{
			s->err += s->dx;
			isoY0 += s->sy;
			(s->y_step)++;
		}
	}
	put_pixel(s, isoX0, isoY0);
}
