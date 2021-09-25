/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 18:12:45 by agunczer          #+#    #+#             */
/*   Updated: 2021/09/25 16:17:44 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	exaggarate(struct s_fdf *data, double exag)
{
	int	i;
	int	j;
	double	x_temp;
	double	y_temp;

	i = 0;
	j = 0;
	exag = 0;
	while (i < data->height)
	{
		while (j < data->width)
		{
			x_temp = data->point_matrix->x[i][j];
			y_temp = data->point_matrix->y[i][j];
			// if (data->matrix[i][j] != 0)
			// {
			// 	data->point_matrix->x[i][j] = ;
			// 	data->point_matrix->y[i][j] = ;
			// }
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
	// *x = (x_temp - y_temp) * cos(0.314);
	// *y = (x_temp + y_temp) * sin(0.314) - z;
int	key_hook(int keycode, struct s_fdf *data)
{
	if (!data->base_points)
	{
		int	i;
		int	j;

		i = 0;
		j = 0;
		data->base_points = ft_calloc(sizeof(struct s_point), 1);
		data->base_points->base_y = ft_calloc(sizeof(double *), data->height);
		data->base_points->base_x = ft_calloc(sizeof(double *), data->height);
		data->base_points->base_z = ft_calloc(sizeof(double *), data->height);
		while (i < data->height)
		{
			data->base_points->base_y[i] = ft_calloc(sizeof(double), data->width);
			data->base_points->base_x[i] = ft_calloc(sizeof(double), data->width);
			data->base_points->base_z[i] = ft_calloc(sizeof(double), data->width);
			while (j < data->width)
			{
				data->base_points->base_y[i][j] = data->point_matrix->y[i][j];
				data->base_points->base_x[i][j] = data->point_matrix->x[i][j];
				data->base_points->base_z[i][j] = data->point_matrix->z[i][j];
				j++;
			}
			i++;
			j = 0;
		}
	}
	if (keycode == ESC)
	{
		mem_free(data);
		exit(0);
	}
	if (keycode == ARR_LEFT)
		data->mov_x -= 20;
	if (keycode == ARR_RIGHT)
		data->mov_x += 20;
	if (keycode == ARR_UP)
		data->mov_y -= 20;
	if (keycode == ARR_DOWN)
		data->mov_y += 20;
	if (keycode == 40)
		rotate_conductor(data, 40);
	if (keycode == 46)
		rotate_conductor(data, 46);
	if (keycode == 4)
		rotate_conductor(data, 4);
	if (keycode == 3)
		rotate_conductor(data, 3);
	if (keycode == 11)
		rotate_conductor(data, 11);
	if (keycode == 8)
		rotate_conductor(data, 8);
	if (keycode == 69)
		exaggarate(data, 1.1);
	if (keycode == 78)
		exaggarate(data, 0.9);
	ft_putnbr_fd(keycode, 1);
	free(data->img);
	free(data->addr);
	create_win(data);
	draw_conductor(data);
	return (0);
}

void	create_win(struct s_fdf *data)
{
	data->mlx = mlx_init ();
	data->img = mlx_new_image(data->mlx, data->screen_w, data->screen_h);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	data->xpos = 0;
	data->ypos = 0;
}

void	terminate(char *s)
{
	if (errno == 0)
		ft_putendl_fd(s, 2);
	else
		perror(s);
	exit(1);
}
