#include "so_long.h"

#define WIDTH 800
#define HEIGHT 600

// Función para dibujar una línea en la imagen
void	draw_line(mlx_image_t *img, int x1, int y1, int x2, int y2,
		uint32_t color)
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x2 - x1);
	sx = x1 < x2 ? 1 : -1;
	dy = -abs(y2 - y1);
	sy = y1 < y2 ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		mlx_put_pixel(img, x1, y1, color);
		if (x1 == x2 && y1 == y2)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x1 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}

// Función para dibujar la cuadrícula
void	draw_grid(mlx_image_t *img)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	// Dibujar líneas verticales
	while (x <= WIDTH)
	{
		draw_line(img, x, 0, x, HEIGHT, 0xFFFFFFFF); // Blanco
		x += TILE_SIZE;
	}
	// Dibujar líneas horizontales
	while (y <= HEIGHT)
	{
		draw_line(img, 0, y, WIDTH, y, 0xFFFFFFFF); // Blanco
		y += TILE_SIZE;
	}
}

