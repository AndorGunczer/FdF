/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 14:50:09 by agunczer          #+#    #+#             */
/*   Updated: 2021/09/25 15:01:14 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	main(int argc, char *argv[])
{
	static struct s_fdf	*data;

	if (argc == 2)
	{
		data = ft_calloc(sizeof(struct s_fdf), 1);
		set_matrix(data, argv[1]);
		draw_conductor(data);
		mem_free(data);
	}
	return (0);
}
