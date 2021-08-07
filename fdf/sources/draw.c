/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 09:49:23 by agunczer          #+#    #+#             */
/*   Updated: 2021/08/07 17:30:45 by agunczer         ###   ########.fr       */
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

typedef struct	s_bresenham {
	int position;
	char *imgptr;
	int dx;
	int sx;
	int dy;
	int sy;
	int err;
	int e2;
}	s_bresenham;

typedef struct  pos {
    int xpos;
    int ypos;
}   this;

void	bresenham_ctor(int x0, int y0, int x1, int y1, s_bresenham *bresen)
{
	bresen->dx = abs(x1-x0);
	if(x0 < x1)
		bresen->sx = 1;
	else
		bresen->sx = (-1);
	bresen->dy = abs(y1-y0);
	if(y0 < y1)
		bresen->sy = 1;
	else
		bresen->sy = (-1);
	if (bresen->dx > bresen->dy)
		bresen->err = bresen->dx/2;
	else
		bresen->err = -(bresen->dy)/2;
}

void line(int x0, int y0, int x1, int y1, t_data *img) 
{
	s_bresenham bresen;
	bresenham_ctor(x0, y0, x1, y1, &bresen);
	while (1) // while (true);
	{
		bresen.position = (int)x0 * 4 + img->line_length * (int)y0; //  - data->matrix[i][j]
		bresen.imgptr = img->addr + bresen.position;
		*(bresen.imgptr + 2) = 0xFF;
		if (x0==x1 && y0==y1) 
			break;
		bresen.e2 = bresen.err;
		if (bresen.e2 >-bresen.dx) 
		{ 
			bresen.err -= bresen.dy;
			x0 += bresen.sx; 
		}
		if (bresen.e2 < bresen.dy) 
		{ 
			bresen.err += bresen.dx; 
			y0 += bresen.sy; 
		}
 	}
}



void	draw_points(struct t_fdf *data)
{
	int i = 0;
	int j = 0;
	struct s_data img;
    struct pos  pos;
    int     position;
    char    *imgptr;
    void    *mlx = mlx_init();
    void    *mlx_win = mlx_new_window(mlx, 2440, 1440, "This is america");
    img.img = mlx_new_image(mlx, 2440, 1440);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	pos.xpos = 200;
    pos.ypos = 200;
    while (i < data->height)
	{
		while (j < data->width)
		{
		    pos.xpos += 10;
			position = pos.xpos * 4 + img.line_length * (pos.ypos - data->matrix[i][j]);
			imgptr = img.addr + position;
			// if (data->matrix[i][j] == 0)
			// // 	*(imgptr + 2) = 0xFF;
			// // else
			// // 	*(imgptr + 1) = 0xFF;
			if (j + 1 < data->width)
				line(pos.xpos, pos.ypos - (data->matrix[i][j]), pos.xpos + 10, pos.ypos - (data->matrix[i][j + 1]), &img);
			if (i + 1 < data->height)
				line(pos.xpos, pos.ypos - (data->matrix[i][j]), pos.xpos, (pos.ypos + 10) - (data->matrix[i + 1][j]), &img);
			j++;
		}
		i++;
		j = 0;
		pos.xpos = 200;
		pos.ypos += 10;
	}
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

    mlx_loop(mlx);
	// for (int i = 0; i < data->height && printf("\n"); i++ )
	// 	for(int c = 0; c < data->width; c++)
	// 		printf("%i ", data->matrix[i][c]);
}

/*
			if (j + 1 < data->width)
				line(pos.xpos, pos.ypos - (data->matrix[i][j]), pos.xpos + 10, pos.ypos - (data->matrix[i][j + 1]), &img);
			if (i + 1 < data->height)
				line(pos.xpos, pos.ypos - (data->matrix[i][j]), pos.xpos, (pos.ypos + 10) - (data->matrix[i + 1][j]), &img);
+++ HAVE TO CHECK IF WITHIN POINTERS OF IMAGE!!!!
+++ HAVE TO OPTIMIZE IT TO THE CENTER!!!!
*/