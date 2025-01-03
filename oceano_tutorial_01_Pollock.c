# include "mlx/include/MLX42/MLX42.h"
# include <stdio.h>
# include <stdlib.h>

// IMPORTANT: compilation
// gcc -Wall -Werror -Wextra oceano_tutorial_01_Pollock.c libft/libft.a mlx/libmlx.a 
// mlx/libmlx_Linux.a -lXext -lX11

// 01 - POLLOCK

// Painting a pixel
// int	main(void)
// {
// 	void	*mlx_ptr;
// 	void	*win_ptr;

// 	mlx_ptr = mlx_init();
// 	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "Hi!");
// 	mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xf4d03f);
// 	mlx_loop(mlx_ptr);
// 	return (0);
// }

// Painting a line
// int	main(void)
// {
// 	void	*mlx_ptr;
// 	void	*win_ptr;
// 	int		i;

// 	mlx_ptr = mlx_init();
// 	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "Hi!");
// 	i = 0;
// 	while (i < 100)
// 	{
// 		mlx_pixel_put(mlx_ptr, win_ptr, 250 + i, 250 + i, 0xf4d03f);
// 		i++;
// 	}
// 	mlx_loop(mlx_ptr);
// }

// Painting a square (contour)
// int	main(void)
// {
// 	void	*mlx_ptr;
// 	void	*win_ptr;
// 	int		i;

// 	mlx_ptr = mlx_init();
// 	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "Hi!");
// 	i = 0;
// 	while (i < 100)
// 	{
// 		mlx_pixel_put(mlx_ptr, win_ptr, 250 + i, 250, 0xf4d03f);
// 		mlx_pixel_put(mlx_ptr, win_ptr, 250, 250 + i, 0xf4d03f);
// 		mlx_pixel_put(mlx_ptr, win_ptr, 250 + i, 350, 0xf4d03f);
// 		mlx_pixel_put(mlx_ptr, win_ptr, 350, 250 + i, 0xf4d03f);
// 		i++;
// 	}
// 	mlx_loop(mlx_ptr);
// }

// Painting a solid square
#define WIDTH 800
#define HEIGHT 500

// int	main(void)
// {
// 	void	*mlx_ptr;
// 	void	*win_ptr;
// 	int		y;
// 	int		x;

// 	mlx_ptr = mlx_init();
// 	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "Hi!");
// 	y = 0;
// 	while (y < HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIDTH)
// 		{
// 			mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xf4d03f);
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_loop(mlx_ptr);
// }

// Same but with some margins between the window and the square
// int	main(void)
// {
// 	void	*mlx_ptr;
// 	void	*win_ptr;
// 	int		y;
// 	int		x;

// 	mlx_ptr = mlx_init();
// 	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "Hi!");
// 	y = 50; // padding margin
// 	while (y < HEIGHT - 50) // padding margin
// 	{
// 		x = 50; // margin
// 		while (x < WIDTH - 50) // padding margin
// 		{
// 			mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xf4d03f);
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_loop(mlx_ptr);
// }

// Same but with adaptative padding -> if height and widht are redefined, it will
// preserve the proportions 
// int	main(void)
// {
// 	void	*mlx_ptr;
// 	void	*win_ptr;
// 	int		y;
// 	int		x;

// 	mlx_ptr = mlx_init();
// 	win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "Hi!");
// 	y = HEIGHT * 0.1; // padding margin
// 	while (y < HEIGHT * 0.9) // padding margin
// 	{
// 		x = WIDTH * 0.1; // margin
// 		while (x < WIDTH * 0.9) // padding margin
// 		{
// 			mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xf4d03f);
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_loop(mlx_ptr);
// }

// y = HEIGHT * 0.1; sets the starting y-coordinate to 10% of the total height.
// This creates a top padding margin.
// while (y < HEIGHT * 0.9) ensures that the loop runs until y reaches 90% of 
// the total height, creating a bottom padding margin.
// Inside the outer loop, x = WIDTH * 0.1; sets the starting x-coordinate to 10% 
// of the total width, creating a left padding margin.
// while (x < WIDTH * 0.9) ensures that the inner loop runs until x reaches 90% 
// of the total width, creating a right padding margin.

// Let's randomise all the pixels in the canvas
// 1st function is invalid because now i am using CODAM libx -> 2nd function

// int	main(void)
// {
// 	void	*mlx_ptr;
// 	void	*win_ptr;
// 	int		y;
// 	int		x;

// 	mlx_ptr = mlx_init();
// 	win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "Hi!");
// 	y = HEIGHT * 0.1; // padding margin
// 	while (y < HEIGHT * 0.9) // padding margin
// 	{
// 		x = WIDTH * 0.1; // margin
// 		while (x < WIDTH * 0.9) // padding margin
// 		{
// 			mlx_pixel_put(mlx_ptr, win_ptr, x, y, rand() % 0x1000000);
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_loop(mlx_ptr);
// }

// Randomize all the pixels in the canvas
// to compile:
// gcc -Wall -Wextra -Werror oceano_tutorial_01_Pollock.c libft/libft.a mlx/mlxbuild/libmlx42.a -lXext -lX11 -ldl -lglfw -lm -pthread
#include "./mlx/include/MLX42/MLX42.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 800
#define HEIGHT 500

int main(void)
{
	// Seed the random number generator
    srand(time(NULL));

    // Initialize MLX42 context
    mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Hi :)", true);
    if (!mlx)
    {
        fprintf(stderr, "Failed to initialize MLX42\n");
        return EXIT_FAILURE;
    }

    // Create a new image (framebuffer)
    mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
    if (!img)
    {
        fprintf(stderr, "Failed to create image\n");
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    // Add the image to the window
    if (mlx_image_to_window(mlx, img, 0, 0) < 0)
    {
        fprintf(stderr, "Failed to add image to window\n");
        mlx_delete_image(mlx, img);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    // Draw random pixels within a margin using while loops
    int y = HEIGHT * 0.1; // Start at 10% height
    while (y < HEIGHT * 0.9) // End at 90% height
    {
        int x = WIDTH * 0.1; // Start at 10% width
        while (x < WIDTH * 0.9) // End at 90% width
        {
            // Generate random red, green, and blue values
            int red = rand() % 256;    // Random red (0-255)
            int green = rand() % 256;  // Random green (0-255)
            int blue = rand() % 256;   // Random blue (0-255)
			int alpha = 255;		   // Fully opaque

            // Combine them into a single color using bit operations
            //int color = (red << 16) | (green << 8) | blue;

			// Combine them into a single color in AABBGGRR format
            // int alpha = 255; // Fully opaque
            // int color = (alpha << 24) | (blue << 16) | (green << 8) | red;

			// Normalize the color into 0xRRGGBBAA format
            int color = (red << 24) | (green << 16) | (blue << 8) | alpha;

			// Debugging: Print out the color values
            // if (x % 100 == 0 && y % 100 == 0) // Only log occasionally to avoid spamming
            // {
            //     printf("x: %d, y: %d, R: %d, G: %d, B: %d, Color: 0x%06X\n", x, y, red, green, blue, color);
            // }

			// Debugging: Print the normalized color
            if (x % 100 == 0 && y % 100 == 0)
            {
                printf("x: %d, y: %d, R: %d, G: %d, B: %d, Color: 0x%08X\n", x, y, red, green, blue, color);
            }

            // Set the pixel at the current position
            mlx_put_pixel(img, x, y, color);

            x++;
        }
        y++;
    }

    // Enter the rendering loop
    mlx_loop(mlx);

    // Cleanup resources
    mlx_delete_image(mlx, img);
    mlx_terminate(mlx);

    return EXIT_SUCCESS;
}

// Brief Explanation of the Color Rendering Issue

// The issue was caused by a mismatch between the color format expected by the 
// MLX42 library and how the colors were being packed and passed to 
// the mlx_put_pixel function. Here’s a breakdown:
// 	1.	Original Problem:
// 	•	Your initial implementation used the 0xRRGGBB format 
// 		(Red-Green-Blue, without alpha).
// 	•	However, MLX42 expected colors in the format 0xAABBGGRR 
// 		(Alpha-Blue-Green-Red), with the alpha channel included.
// 	•	This caused the red channel to be suppressed, and you only saw blues 
// 		and greens because the bits for red were interpreted incorrectly.
// 	2.	Attempted Fix:
// 	•	Adding an alpha channel (0xAABBGGRR) caused an overrepresentation of 
// 		red because the alpha bits (intended for transparency) were interpreted 
// 		as part of the red channel.
// 	3.	Final Solution:
// 	•	Packing the color data in the 0xRRGGBBAA format, ensuring proper 
// 		interpretation by MLX42. This matches the library’s expectations and 
// 		ensures all channels (Red, Green, Blue, and Alpha) are correctly rendered.

