#include "so_long.h"

// Function to render the map using the floor tile
void	render_floor(mlx_t *mlx, mlx_image_t *floor_image, t_map *map)
{
	uint32_t y = 0;
	uint32_t x;

	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == '0') // Render floor for empty spaces
			{
				mlx_image_to_window(mlx, floor_image, x * TILE_SIZE, y
					* TILE_SIZE);
			}
			x++;
		}
		y++;
	}
}