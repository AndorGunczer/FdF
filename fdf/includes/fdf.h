/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 14:28:54 by agunczer          #+#    #+#             */
/*   Updated: 2021/09/25 15:34:09 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define ESC 53
# define ARR_RIGHT 124
# define ARR_LEFT 123
# define ARR_UP 126
# define ARR_DOWN 125

# define ERR_NO_MAP "Map cannot be found!"
# define ERR_NO_SPACE "Problem with file!"
# define ERR_FILE_EMPTY "File is EMPTY"

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>

struct s_point
{
	double	**z;
	double	**x;
	double	**y;
};

struct s_radian
{
	double *alpha;
	double *beta;
	double *gamma;
};

struct s_base
{
	double **base_z;
	double **base_x;
	double **base_y;
};

struct s_fdf
{
	int		**matrix;
	int		width;
	int		height;
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		position;
	char	*imgptr;
	double	dx;
	double	sx;
	double	dy;
	double	sy;
	double	y_step;
	double	x_step;
	double	err;
	double	e2;
	double	x0;
	double	y0;
	double	x1;
	double	y1;
	double	isoX0;
	double	isoY0;
	double	isoX1;
	double	isoY1;
	double	screen_w;
	double	screen_h;
	double	draw_w;
	double	draw_h;
	double	center_x;
	double	center_y;
	double	exag;
	double		z;
	double		z1;
	double		size;
	double		xpos;
	double		ypos;
	double	mov_y;
	double	mov_x;
	double	degree;
	struct s_base	*base_points;
	struct s_radian *radian_matrix;
	struct s_point *point_matrix;
};

//file_read.c
// void	get_params(char *file_name, int *x, int *y);
// void	set_line(struct s_fdf *data, char *file_name);
void	set_matrix(struct s_fdf *data, char *file_name);


//file_read.c lists
t_list	*get_params(char *file_name, int *x, int *y);
void	set_line(struct s_fdf *data, t_list *lst);


//draw.c
void	draw_conductor(struct s_fdf *data);
void	draw_line_ctor(struct s_fdf *data);
void	setPoints(struct s_fdf *data, double calcX, double calcY, int i, int j);
void	create_point_matrix(struct s_fdf *data);
void	twoDToIso(double *x, double *y, double z);
int		key_hook(int keycode, struct s_fdf *s);
void	call_bresen(struct s_fdf *data);

//bresen.c
void	bresen_ctor(struct s_fdf *bresen, double isoX1, double isoX0, double isoY1, double isoY0);
void	bresen_line(struct s_fdf *s, double isoX1, double isoX0, double isoY1, double isoY0);
void	put_pixel(struct s_fdf *s, double isoX0, double isoY0);

//color.c
void	color(char *ptr);

//move.c
void	terminate(char *s);
void	create_win(struct s_fdf *data);
int		exaggarate(struct s_fdf *data, double exag);

//rotate.c
int		rotate_conductor(struct s_fdf *data, int key);
void	rotate_x(struct s_fdf *data, int key);
void	rotate_y(struct s_fdf *data, int key);
void	rotate_z(struct s_fdf *data, int key);

//free_functions.c
void	ft_single_free(char **string);
void	ft_double_free(char	**string);
void	ft_custom_free(struct s_fdf *data, char SD);
void	ft_single_int_free(int	*string);
void	ft_double_int_free(int	**string);
void	ft_single_double_free(double *string);
int		mem_free(struct s_fdf *data);

#endif