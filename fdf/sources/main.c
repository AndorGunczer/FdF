/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 14:50:09 by agunczer          #+#    #+#             */
/*   Updated: 2021/08/04 20:03:37 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "../libft/libft.h"
#include "../includes/fdf.h"

int     main(int argc, char *argv[])
{
    struct t_fdf *data;

    data = ft_calloc(sizeof(struct t_fdf), 1);
    set_matrix(data, argv[1]);
    return (0);
}