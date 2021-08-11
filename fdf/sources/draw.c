/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 09:49:23 by agunczer          #+#    #+#             */
/*   Updated: 2021/08/11 16:27:39 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../includes/fdf.h"
#include <math.h>

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
	double dx;
	double sx;
	double dy;
	double sy;
	double y_step;
	double x_step;
	double err;
	double e2;
}	s_bresenham;

typedef struct  pos {
    double x0;
    double y0;
	double x1;
	double y1;
	double isoX0;
	double isoY0;
	double isoX1;
	double isoY1;
}   this;

typedef struct	s_dim {
	double	screen_w;
	double	screen_h;
	double	draw_w;
	double	draw_h;
	double	center_x;
	double	center_y;
}	dimensions;

// (w/2)-(ww/2)
// (h/2)-(hh/2)

void	bresenham_ctor(double x0, double y0, double x1, double y1, s_bresenham *bresen)
{
	bresen->x_step = 0;
	bresen->y_step = 0;
	bresen->dx = fabs(x1-x0);
	if(x0 < x1)
		bresen->sx = 1;
	else
		bresen->sx = (-1);
	bresen->dy = fabs(y1-y0);
	if(y0 < y1)
		bresen->sy = 1;
	else
		bresen->sy = (-1);
	if (bresen->dx > bresen->dy)
		bresen->err = bresen->dx/2;
	else
		bresen->err = -(bresen->dy)/2;
}

void line(double x0, double y0, double x1, double y1, t_data *img, dimensions *dim) 
{
	s_bresenham bresen;
	bresenham_ctor(x0, y0, x1, y1, &bresen);
	// bresen.imgptr = img->addr + bresen.position;
	while (bresen.x_step <= bresen.dx) // while (true);
	{
		bresen.position = (round(x0) + dim->center_x) * 4 + (img->line_length * (round(y0) + dim->center_y)); //  - data->matrix[i][j]
		bresen.imgptr = img->addr + bresen.position;
		*(bresen.imgptr) = 0xFF;
		bresen.e2 = bresen.err;
		if (bresen.e2 >-bresen.dx) 
		{ 
			bresen.err -= bresen.dy;
			x0 += bresen.sx; 
			bresen.x_step++;
		}
		if (bresen.e2 < bresen.dy) 
		{ 
			bresen.err += bresen.dx; 
			y0 += bresen.sy; 
			bresen.y_step++;
		}
 	}
	bresen.position = ((int)x0 + dim->center_x) * 4 + (img->line_length * ((int)y0 + dim->center_y)); //  - data->matrix[i][j]
	bresen.imgptr = img->addr + bresen.position;
	*(bresen.imgptr) = 0xFF;
}

void		setPoints(double *x, double *y, double calcX, double calcY)
{
	*x = calcX;
	*y = calcY;
}

void		twoDToIso(struct pos *point, int z, int z1)
{
	point->isoX0 = (point->x0 - point->y0) * cos(0.5);
	point->isoY0 = (point->x0 + point->y0) * sin(0.5) - z;
	point->isoX1 = (point->x1 - point->y1) * cos(0.5);
	point->isoY1 = (point->x1 + point->y1) * sin(0.5) - z1;
}

// x = (w/2) - (ww/2)
// y = (h/2) - (hh/2)

void	draw_points(struct t_fdf *data)
{
	int i = 0;
	int j = 0;
	double z;
	double z1;
	struct s_data img;
    struct pos  pos;
	struct s_dim dim;
	int size = 1300 / data->width;
	dim.screen_w = 2440;
	dim.screen_h = 1200;
	dim.draw_w = (data->width * size) / 2;
	dim.draw_h = ((data->height * size) / 2) + 700; // +800
	dim.center_x = (dim.screen_w/2) - (dim.draw_w/2);
	dim.center_y = (dim.screen_h/2) - (dim.draw_h/2);
    int     position;
    char    *imgptr;
    void    *mlx = mlx_init();
    void    *mlx_win = mlx_new_window(mlx, dim.screen_w, dim.screen_h, "This is america");
    img.img = mlx_new_image(mlx, dim.screen_w, dim.screen_h);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	int xpos = 0;
    int ypos = 0;
    while (i < data->height)
	{
		while (j < data->width)
		{
		    xpos += size;
			if (j + 1 < data->width)
			{
				setPoints(&pos.x0, &pos.y0, xpos, ypos);
				setPoints(&pos.x1, &pos.y1, xpos + size, ypos);
				z = data->matrix[i][j];
				z1 = data->matrix[i][j + 1];
				twoDToIso(&pos, z, z1);
				// line(pos.x0, pos.y0, pos.x1, pos.y1, &img);
				line(pos.isoX0, pos.isoY0, pos.isoX1, pos.isoY1, &img, &dim);
			}
			if (i + 1 < data->height)
			{
				setPoints(&pos.x0, &pos.y0, xpos, ypos);
				setPoints(&pos.x1, &pos.y1, xpos, (ypos + size));
				z = data->matrix[i][j];
				z1 = data->matrix[i + 1][j];
				twoDToIso(&pos, z, z1);
				// line(pos.x0, pos.y0, pos.x1, pos.y1, &img);
				line(pos.isoX0, pos.isoY0, pos.isoX1, pos.isoY1, &img, &dim);
			}
			j++;
		}
		i++;
		j = 0;
		xpos = 0;
		ypos += size;
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