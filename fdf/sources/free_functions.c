/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 18:11:47 by agunczer          #+#    #+#             */
/*   Updated: 2021/09/25 14:27:41 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_single_free(char **string)
{
	if (!string)
		return ;
	free(*string);
	*string = 0;
}

void	ft_double_free(char	**string)
{
	int	i;

	i = 0;
	if (!string)
		return ;
	while (string[i] != NULL)
	{
		ft_single_free(&string[i]);
		i++;
	}
	free(string);
	string = 0;
}

void	ft_double_int_free(int	**string)
{
	int	i;

	i = 0;
	if (!string)
		return ;
	while (string[i] != NULL)
	{
		ft_single_int_free(string[i]);
		i++;
	}
	free(string);
	string = 0;
}

void	ft_single_int_free(int	*string)
{
	if (!string)
		return ;
	free(string);
	string = 0;
}

void	ft_single_double_free(double *string)
{
	if (!string)
		return ;
	free(string);
	string = 0;
}

void	ft_double_double_free(double	**string)
{
	int	i;

	i = 0;
	if (!string)
		return ;
	while (string[i] != NULL)
	{
		ft_single_double_free(string[i]);
		i++;
	}
	free(string);
	string = 0;
}

void	ft_custom_free(struct s_fdf *data, char SD)
{
	if (SD == 'S')
	{
		ft_single_double_free(data->radian_matrix->alpha);
		ft_single_double_free(data->radian_matrix->beta);
		ft_single_double_free(data->radian_matrix->gamma);
	}
	if (SD == 'D')
	{
		ft_double_double_free(data->point_matrix->x);
		ft_double_double_free(data->point_matrix->y);
		ft_double_double_free(data->point_matrix->z);
		ft_double_double_free(data->base_points->base_x);
		ft_double_double_free(data->base_points->base_y);
		ft_double_double_free(data->base_points->base_z);
		ft_double_int_free(data->matrix);
	}
}
