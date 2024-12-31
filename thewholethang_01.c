# include "./mlx/include/MLX42/MLX42.h"
# include <stdio.h>
# include <stdlib.h>

// IMPORTANT: compilation
// gcc -Wall -Werror -Wextra thewholethang_01.c libft/libft.a mlx/libmlx.a 
// mlx/libmlx_Linux.a -lXext -lX11

#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>

#define MLX_ERROR       1
#define WINDOW_WIDTH    1200
#define WINDOW_HEIGHT   400


/*
 * MLX_STRUCT
 * I stock all the data into a struct
 * because the handler function takes 
 * (void *)pointer_to_data
 * I need therefore this gimmick to 
 * pass more elements in one-go
*/
// typedef struct s_mlx_data
// {
//     void	*mlx_ptr;
//     void	*win_ptr;
// }               t_mlx_data;

int	main()
{
	void	*mlx_ptr;
    void	*win_ptr;
	void	*img_ptr;
	char	*path;
	int		img_width;
	int		img_height;

	path = "./assets/grasstile.xpm";
	img_width = 120;
	img_height = 120;
	mlx_ptr = mlx_init(img_width, img_height, "Hi :)", 1);
	if (!mlx_ptr)
		return (1);
	win_ptr = mlx_new_window(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "hi :)");
	if (!win_ptr)
		return (free(mlx_ptr), 1);
	img_ptr = mlx_xpm_file_to_image(mlx_ptr, path, &img_width, &img_height);
	if (!img_ptr)
		return (1);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	mlx_loop(mlx_ptr);
	mlx_destroy_window(mlx_ptr, win_ptr);
	free(mlx_ptr);
	return (0);
}