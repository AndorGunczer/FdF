#include "fdf/mlx/mlx.h"

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

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}


int     main(void)
{
    struct s_data img;
    struct pos  pos;
    int     position;
    char    *imgptr;
    void    *mlx = mlx_init();
    void    *mlx_win = mlx_new_window(mlx, 800, 600, "This is america");
    img.img = mlx_new_image(mlx, 800, 600);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    pos.xpos = 20;
    pos.ypos = 20;
    position = pos.xpos * 4 + img.line_length * pos.ypos;
    imgptr = img.addr + position;
    *imgptr = 0x00;
    *(imgptr + 1) = 0x00;
    *(imgptr + 2) = 0xFF;
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

    mlx_loop(mlx);
}