/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:55:13 by agunczer          #+#    #+#             */
/*   Updated: 2021/09/25 13:16:03 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int mem_free(struct s_fdf *data)
{
	ft_custom_free(data, 1);
	ft_custom_free(data, 2);
	free(data->point_matrix);
	free(data->radian_matrix);
	free(data->base_points);

	mlx_destroy_window(data->mlx, data->mlx_win);
	free(data->img);
	free(data->addr);
	free(data->mlx);
	return (0);
}