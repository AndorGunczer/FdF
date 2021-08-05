/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 09:49:23 by agunczer          #+#    #+#             */
/*   Updated: 2021/08/05 18:54:29 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../includes/fdf.h"

typedef	struct	s_draw {
	int     position;
    char    *imgptr;
    void    *mlx;
	void    *mlx_win;
}	draw;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel; //32px
	int		line_length; //width * height
	int		endian; //depends on arch.
}				t_data;

typedef struct  pos {
    int xpos;
    int ypos;
}   this;

void	draw_points(struct t_fdf *data)
{
	int i = 0;
	int j = 0;
	struct s_data img;
    struct pos  pos;
    int     position;
    char    *imgptr;
    void    *mlx = mlx_init();
    void    *mlx_win = mlx_new_window(mlx, 1920, 1080, "This is america");
    img.img = mlx_new_image(mlx, 1920, 1080);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	pos.xpos = 100;
    pos.ypos = 50;
    while (i < data->height)
	{
		while (j < data->width)
		{
		    pos.xpos += 20;
			position = pos.xpos * 4 + img.line_length * (pos.ypos - data->matrix[i][j]);
			imgptr = img.addr + position;
			if (data->matrix[i][j] == 0)
				*(imgptr + 2) = 0xFF;
			else
				*(imgptr + 1) = 0xFF;
			j++;
		}
		i++;
		j = 0;
		pos.xpos = 100;
		pos.ypos += 20;
	}
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

    mlx_loop(mlx);
	// for (int i = 0; i < data->height && printf("\n"); i++ )
	// 	for(int c = 0; c < data->width; c++)
	// 		printf("%i ", data->matrix[i][c]);
}