/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 14:28:54 by agunczer          #+#    #+#             */
/*   Updated: 2021/08/05 10:06:21 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

struct  t_fdf
{
    int     **matrix;
    int     width;
    int     height;
};

//file_read.c
t_list	*get_params(char *file_name, struct t_fdf *data, int *x, int *y);
void	set_line(struct t_fdf *data, t_list *lst, char *file_name);
void    set_matrix(struct t_fdf *data, char *file_name);

//draw.c
void	draw_points(struct t_fdf *data);



#endif