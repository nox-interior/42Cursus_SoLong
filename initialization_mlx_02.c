# include "./mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h> // For free

// https://reactive.so/post/42-a-comprehensive-guide-to-so_long

// IMPORTANT: compilation
// gcc -Wall -Werror -Wextra initialization_of_mlx.c libft/libft.a mlx/libmlx.a 
// mlx/libmlx_Linux.a -lXext -lX11

// typedef struct 	s_map;
// {
// 	//
// }				t_map;

// typedef struct	s_data
// {
// 	void	*mlx_ptr; // MLX pointer
// 	void	*win_ptr; // MLX window pointer
// 	void	*textures[5]; // MLX image pointers (on the stack)
// 	//t_map	*map; // Map pointer (contains map details, preferably)
// }				t_data;

// To start working with the MLX, we first need to initialise the MLX library. 
// Under the hood, this creates a new structure which contains all the required 
// data for the MLX to function correctly.

// int	main(void)
// {
// 	void	*mlx_ptr;

// 	mlx_ptr = mlx_init();
// 	if (!mlx_ptr)
// 		return (1);
// 	free(mlx_ptr);
// 	return (0);
// }

// In this example, you'll notice we set the mlx_ptr to the result of the mlx_init
// function. It may return NULL if there was an issue with X11, 
// which you will have to manage.

// Creating a window

// int	main(void)
// {
// 	void	*mlx_ptr;
// 	void	*win_ptr;

// 	mlx_ptr = mlx_init();
// 	if (!mlx_ptr)
// 		return (1);
// 	win_ptr = mlx_new_window(mlx_ptr, 600, 400, "hi :)");
// 	if (!win_ptr)
// 		return (free(mlx_ptr), 1);
// 	mlx_destroy_window(mlx_ptr, win_ptr);
// 	free(mlx_ptr);
// 	return (0);
// }

// This should open a window, and then immediately close it, as we are calling 
// the destroy methods right after. To prevent this behaviour and tell the MLX 
// to wait, we have to learn about hooks and events!

// int	main(void)
// {
// 	void	*mlx_ptr;
// 	void	*win_ptr;

// 	mlx_ptr = mlx_init();
// 	if (!mlx_ptr)
// 		return (1);
// 	win_ptr = mlx_new_window(mlx_ptr, 800, 400, "hi :)");
// 	if (!win_ptr)
// 		return (free(mlx_ptr), 1);

// 	// Basic event loop to keep the window open
// 	mlx_loop(mlx_ptr);

// 	mlx_destroy_window(mlx_ptr, win_ptr);
// 	free(mlx_ptr);
// 	return (0);
// }

#include <X11/X.h>
#include <X11/keysym.h>

// // This little program will open a wondow and print the code number of each key
// // pressed, until closed.
// typedef struct	s_data
// {
// 	void	*mlx_ptr;
// 	void	*win_ptr;
// }				t_data;

// int	on_destroy(t_data *data)
// {
// 	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
// 	mlx_destroy_display(data->mlx_ptr);
// 	free(data->mlx_ptr);
// 	exit (0);
// 	return (0);
// }

// int	on_keypress(int keysym, t_data *data)
// {
// 	(void)data;
// 	printf("Pressed key: %d\n", keysym);
// 	return (0);
// }
// int	main(void)
// {
// 	t_data	data;
	
// 	data.mlx_ptr = mlx_init();
// 	if (!data.mlx_ptr)
// 		return (1);
// 	data.win_ptr = mlx_new_window(data.mlx_ptr, 600, 400, "hi :)");
// 	if (!data.win_ptr)
// 		return (free(data.mlx_ptr), 1);
 
// 	// Register key release hook
// 	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &data);
 
// 	// Register destroy hook
// 	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
 
// 	// Enters the event as an infinite loop over the MLX pointer and waits for 
// 	// events and handles them
// 	// Rendering: It continuously updates the window, allowing for animations
// 	// and real-time graphics rendering.
// 	// When you call mlx_loop(data.mlx_ptr);, you are telling the program to
// 	// start this event loop using the mlx_ptr (MLX pointer) which is
// 	// initialized earlier in your code. This keeps the application running and
// 	// responsive to user inputs.
// 	mlx_loop(data.mlx_ptr);
// 	return (0);
// }
// When you call mlx_loop(data.mlx_ptr);, you are telling the program to start this
// event loop using the mlx_ptr (MLX pointer) which is initialized earlier in your
// code. This keeps the application running and responsive to user inputs.
// The KeyRelease and DestroyNotify constants are native X11 events, and can be
// imported through the X11 headers.

int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	//void	*img_ptr;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (1);
	win_ptr = mlx_new_window(mlx_ptr, 1920, 1080, "hi :)");
	if (!win_ptr)
		return (free(mlx_ptr), 1);
	//img_ptr = mlx_new_image(mlx_ptr, 1920, 1080);
	mlx_loop(mlx_ptr);
	mlx_destroy_window(mlx_ptr, win_ptr);
	free(mlx_ptr);
	return (0);
}