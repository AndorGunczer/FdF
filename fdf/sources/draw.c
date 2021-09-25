/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 09:49:23 by agunczer          #+#    #+#             */
/*   Updated: 2021/09/25 15:41:04 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	draw_line_ctor(struct s_fdf *data)
{
	data->screen_w = 2440.0;
	data->screen_h = 1440.0;
	data->size = fabs(data->screen_w - data->screen_h) / (data->width);
	data->draw_w = (data->width * data->size) / 2.0;
	data->draw_h = ((data->height * data->size) / 2.0)
		+ (fabs(data->screen_w - data->screen_h) / 2.0);
	data->center_x = (data->screen_w / 2.0) - (data->draw_w / 2.0);
	data->center_y = (data->screen_h / 2.0) - (data->draw_h / 2.0);
	data->degree = 0.314;
	data->exag = 1.0;
	data->mlx = mlx_init ();
	data->mlx_win = mlx_new_window(data->mlx, data->screen_w, data->screen_h, "FdF");
	data->img = mlx_new_image(data->mlx, data->screen_w, data->screen_h);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	data->xpos = 0;
	data->ypos = 0;
}

void	setPoints(struct s_fdf *data, double calcX, double calcY, int i, int j)
{
	// data->point_matrix->x[i][j] = ft_calloc(sizeof(int), 1);
	// data->point_matrix->y[i][j] = ft_calloc(sizeof(int), 1);
	data->point_matrix->x[i][j] = calcX;
	data->point_matrix->y[i][j] = calcY;
}

void	twoDToIso(double *x, double *y, double z)
{
	double x_temp;
	double y_temp;

	x_temp = *x;
	y_temp = *y;
	*x = (x_temp - y_temp) * cos(0.314);
	*y = (x_temp + y_temp) * sin(0.314) - z;
}

void	call_bresen(struct s_fdf *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->height)
	{
		while (j < data->width)
		{
			if (j + 1 < data->width)
				bresen_line(data, data->point_matrix->x[i][j + 1], data->point_matrix->x[i][j], data->point_matrix->y[i][j + 1], data->point_matrix->y[i][j]);
			if (i + 1 < data->height)
				bresen_line(data, data->point_matrix->x[i + 1][j], data->point_matrix->x[i][j], data->point_matrix->y[i + 1][j], data->point_matrix->y[i][j]);
			j++;
		}
		i++;
		j = 0;
	}
}

void	create_point_matrix(struct s_fdf *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->point_matrix = ft_calloc(sizeof(struct s_point), 1);
	data->point_matrix->y = ft_calloc(sizeof(double *), data->height);
	data->point_matrix->x = ft_calloc(sizeof(double *), data->height);
	data->point_matrix->z = ft_calloc(sizeof(double *), data->height);
	while (i < data->height)
	{
		data->point_matrix->y[i] = ft_calloc(sizeof(double), data->width);
		data->point_matrix->x[i] = ft_calloc(sizeof(double), data->width);
		data->point_matrix->z[i] = ft_calloc(sizeof(double), data->width);
		while (j < data->width)
		{
			setPoints(data, data->xpos, data->ypos, i, j);
			data->point_matrix->z[i][j] = data->matrix[i][j] * ((data->size * 0.1));
			twoDToIso(&data->point_matrix->x[i][j], &data->point_matrix->y[i][j], data->point_matrix->z[i][j]);
			data->xpos += data->size;
			j++;
		}
		i++;
		j = 0;
		data->xpos = 0;
		data->ypos += data->size;
	}
}

void	draw_conductor(struct s_fdf *data)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	if (!data->mlx)
		draw_line_ctor(data);
	if (!data->point_matrix)
		create_point_matrix(data);
	call_bresen(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	mlx_hook(data->mlx_win, 2, 1L << 0, key_hook, data);
	mlx_loop(data->mlx);
}

		// s->position = (((round(s->isoX0) * 4) + (s->center_x * 4))) + 
		// (s->line_length * (round(s->isoY0) + s->center_y));
		// s->imgptr = s->addr + s->position;
		// color(s->imgptr, s->z1);

// 		s_point	create_point_matrix(data)
// {
// 	data->point_matrix = ft_calloc(sizeof(struct s_point), 1);
// 	while (i < data->height)
// 	{
// 		while (j < data->width)
// 		{
// 			data->xpos += data->size;
// 			point_handler(&i, &j, data);
// 			j++;
// 		}
// 		i++;
// 		j = 0;
// 		data->xpos = 0;
// 		data->ypos += data->size;
// 	}
// }

	// for(int k = 0; k < data->height; k++)
	// 	for(int l = 0; l < data->width; l++)
	// 		printf("X axis: %d\tY axis: %d\tZ axis: %d\n", data->point_matrix->x[k][l], data->point_matrix->y[k][l], data->point_matrix->z[k][l]);