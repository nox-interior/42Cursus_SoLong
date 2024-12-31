# include "mlx/mlx.h"

// compilation
// cc -Wall -Werror -Wextra initialization_of_mlx.c libft/libft.a mlx/libmlx.a 
// mlx/libmlx_Linux.a -lXext -lX11

typedef struct	s_data 
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	ft_my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello World!");
	img.img = mlx_new_image(mlx, 1920, 1080);

	/*
	** After creating an image, we can call `mlx_get_data_addr`, we pass
	** `bits_per_pixel`, `line_length`, and `endian` by reference. These will
	** then be set accordingly for the *current* data address.
	*/
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	ft_my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_loop(mlx);
}

// First try outs: a window. plus an image. Exit: crtl + c
// int	main(void)
// {
// 	void	*mlx;
// 	void	*mlx_win;
// 	void	*img;

// 	mlx = mlx_init();
// 	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello World!");
// 	mlx_loop(mlx);
// 	img = mlx_new_image(mlx, 1920, 1080);
// }

