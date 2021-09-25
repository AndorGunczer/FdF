/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 11:04:15 by agunczer          #+#    #+#             */
/*   Updated: 2021/09/25 15:56:14 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	rotate_x(struct s_fdf *data, int key)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!data->radian_matrix->alpha)
	{
		data->radian_matrix->alpha = ft_calloc(sizeof(double *), 1);
		*data->radian_matrix->alpha = 0.314;
	}
	if (key == 40)
		*data->radian_matrix->alpha += 0.1;
	else if (key == 46)
		*data->radian_matrix->alpha -= 0.1;
	while (i < data->height)
	{
		while (j < data->width)
		{
			data->point_matrix->y[i][j] = (data->base_points->base_y[i][j] * cos(*data->radian_matrix->alpha)) - (data->base_points->base_z[i][j] * sin(*data->radian_matrix->alpha));
			data->point_matrix->z[i][j] = (data->base_points->base_y[i][j] * sin(*data->radian_matrix->alpha)) + (data->base_points->base_z[i][j] * cos(*data->radian_matrix->alpha));
			j++;
		}
		j = 0;
		i++;
	}
}

void	rotate_y(struct s_fdf *data, int key)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!data->radian_matrix->beta)
	{
		data->radian_matrix->beta = ft_calloc(sizeof(double *), 1);
		*data->radian_matrix->beta = 0.314;
	}
	if (key == 4)
		*data->radian_matrix->beta += 0.1;
	else if (key == 3)
		*data->radian_matrix->beta -= 0.1;
	while (i < data->height)
	{
		while (j < data->width)
		{
			data->point_matrix->x[i][j] = (data->base_points->base_x[i][j] * cos(*data->radian_matrix->beta)) + (data->base_points->base_z[i][j] * sin(*data->radian_matrix->beta));
			data->point_matrix->z[i][j] = (data->base_points->base_z[i][j] * cos(*data->radian_matrix->beta)) - (data->base_points->base_x[i][j] * sin(*data->radian_matrix->beta));
			j++;
		}
		j = 0;
		i++;
	}
}

void	rotate_z(struct s_fdf *data, int key)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!data->radian_matrix->gamma)
	{
		data->radian_matrix->gamma = ft_calloc(sizeof(double *), 1);
		*data->radian_matrix->gamma = 0.314;
	}
	if (key == 11)
		*data->radian_matrix->gamma += 0.1;
	else if (key == 8)
		*data->radian_matrix->gamma -= 0.1;
	while (i < data->height)
	{
		while (j < data->width)
		{
			data->point_matrix->x[i][j] = (data->base_points->base_x[i][j] * cos(*data->radian_matrix->gamma)) - (data->base_points->base_y[i][j] * sin(*data->radian_matrix->gamma));
			data->point_matrix->y[i][j] = (data->base_points->base_x[i][j] * sin(*data->radian_matrix->gamma)) + (data->base_points->base_y[i][j] * cos(*data->radian_matrix->gamma));
			j++;
		}
		j = 0;
		i++;
	}
}

int		rotate_conductor(struct s_fdf *data, int key)
{
	if (!data->radian_matrix)
	{
		data->radian_matrix = ft_calloc(sizeof(struct s_radian), 1);
	}
	if (key == 40 || key == 46)
		rotate_x(data, key);
	if (key == 4 || key == 3)
		rotate_y(data, key);
	if (key == 11 || key == 8)
		rotate_z(data, key);
	return (0);
}