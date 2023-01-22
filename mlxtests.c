#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#define WIDTH 256
#define HEIGHT 256

mlx_image_t	*img;
mlx_key_data_t *keydata;

void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	// mlx_texture_t* down;
	// mlx_texture_t* up;
	// mlx_texture_t* right;
	// mlx_texture_t* left;

	// down = mlx_load_png("assets/rat_front.png");
	// up = mlx_load_png("assets/rat_front.png");
	// right = mlx_load_png("assets/rat_front.png");
	// = mlx_load_png("assets/rat_front.png");

	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		img->instances[0].y -= 64;
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		img->instances[0].y += 64;

	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		img->instances[0].x -= 64;

	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		img->instances[0].x += 64;
}

int main(void)
{
	mlx_t *mlx;
	mlx_texture_t* start;

	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(1);
	start = mlx_load_png("assets/rat_front.png");
	if(!start)
		exit(1);
	//	up = mlx_load_png("assets/rat_back.png");
	//	right = mlx_load_png("assets/rat_right.png");
	
	img = mlx_texture_to_image(mlx, start);
	
	
	memset(img->pixels, 0, (64*64));
	//img = mlx_texture_to_image(mlx, up);
	//mlx_image_to_window(mlx, img, 0, 0);
	//img = mlx_texture_to_image(mlx, right);
	//mlx_image_to_window(mlx, img, 0, 0);
	img = mlx_texture_to_image(mlx, start);
	mlx_image_to_window(mlx, img, 0, 0);

	mlx_key_hook(mlx, &my_keyhook, NULL);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}