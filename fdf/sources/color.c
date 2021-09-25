/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 18:11:41 by agunczer          #+#    #+#             */
/*   Updated: 2021/09/22 14:25:17 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

typedef struct t_color {
	char	*r;
	char	*g;
	char	*b;
}	t_rgb;

// void	color(char *ptr, int z)
// {
// 	int	res;
// 	struct	s_color clr;
// 	clr.b = ptr;
// 	clr.g = ptr + 1;
// 	clr.r = ptr + 2;

// 	*(clr.r) = 0;
// 	*(clr.g) = 10;
// 	*(clr.b) = 0;
// 	res = (z + 1) * 20;
// 	*(clr.g) += res;
// }

void	color(char *ptr)
{
	*ptr = 0xFF;
}
