/* This example varies from the precedent one in that the color can be other
Than a shade of grey. As memset() only takes one value, this value is aplied
to each rgba channel, resulting in a gray palette.

In order to cretae specific colours we can use a helper function,
get_rgba, to do so.*/

#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdint.h>

#define WIDTH 128
#define HEIGHT 128

// Function to encode RGBA values into a 32-bit integer.
int32_t get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int32_t main(void)
{
    // Init mlx with a canvas size of 256x256 and the ability to resize the window.
    mlx_t* mlx = mlx_init(256, 256, "MLX42", true);
    if (!mlx) 
        exit(EXIT_FAILURE);

    // Create a 128x128 image.
    mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);

    // Fill each pixel with different colours.
    int y = 0;
    while (y < HEIGHT) // Iterate over rows
    {
        int x = 0;
        while (x < WIDTH) // Iterate over columns
        {
            // Example: Create a gradient effect.
            // uint8_t red = (x * 255) / WIDTH;  // Gradient for red channel.
            // uint8_t green = (y * 255) / HEIGHT;  // Gradient for green channel.
            // uint8_t blue = 255;  // Fixed blue channel.
            // uint8_t alpha = 255;  // Fully opaque.

            // Encode RGBA and assign to the pixel.
			// For the gradient, we use get_rgba
            //((int32_t*)img->pixels)[y * WIDTH + x] = get_rgba(red, green, blue, alpha);
			// If we alredy know tyhe colour, we can pass it directly
			((int32_t*)img->pixels)[y * WIDTH + x] = 0xFF0000FF; // Fully opaque red
            x++; // Increment column index
        }
        y++; // Increment row index
    }

    // Draw the image at coordinates (0, 0).
    mlx_image_to_window(mlx, img, 0, 0);

    // Run the main loop and terminate on quit.  
    mlx_loop(mlx);
    mlx_terminate(mlx);

    return (EXIT_SUCCESS);
}
