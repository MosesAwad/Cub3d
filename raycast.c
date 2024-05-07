/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:46:48 by mawad             #+#    #+#             */
/*   Updated: 2024/05/07 19:01:55 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_params_and_vectors(t_game *game, t_dda *dda,
	t_vector *ray_dir, double x)
{
	dda->camera_x = (2 * x / game->map_width) - 1;
	dda->side = 0;
	dda->hit = FALSE;
	ray_dir->x = game->dir.x + game->cam_plane.x * dda->camera_x;
	ray_dir->y = game->dir.y + game->cam_plane.y * dda->camera_x;
	dda->map.x = (int) game->player_posx;
	dda->map.y = (int) game->player_posy;
}

static void	set_up_delta_dist(t_dda *dda)
{
	if (dda->ray_dir.x == 0.00)
		dda->delta_dist_x = 1e30;
	else
		dda->delta_dist_x = fabs(1 / dda->ray_dir.x);
	if (dda->ray_dir.y == 0.00)
		dda->delta_dist_y = 1e30;
	else
		dda->delta_dist_y = fabs(1 / dda->ray_dir.y);
}

static void	set_up_side_dist(t_vector *pos, t_dda *dda)
{
	if (dda->ray_dir.x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (pos->x - dda->map.x) * dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = ((1 - (pos->x - dda->map.x)) * dda->delta_dist_x);
	}
	if (dda->ray_dir.y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (pos->y - dda->map.y) * dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (1 - (pos->y - dda->map.y)) * dda->delta_dist_y;
	}
}

static void	dda_loop(t_game *game, t_dda *dda)
{
	while (dda->hit == FALSE)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map.x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map.y += dda->step_y;
			dda->side = 1;
		}
		if (game->map[(int) dda->map.y][(int) dda->map.x] == '1')
			dda->hit = TRUE;
	}
}

void	draw_cross_hair(t_game *game)
{
	int	start;
	int	end;

	start = (game->map_height / 2) - 20;
	end = (game->map_height / 2) - 7;
	while (start < end)
		my_pixel_put(game, game->map_width / 2, start++, 0x39FF14);
	start = (game->map_height / 2) + 7;
	end = (game->map_height / 2) + 20;
	while (start < end)
		my_pixel_put(game, game->map_width / 2, start++, 0x39FF14);
	start = (game->map_width / 2) - 20;
	end = (game->map_width / 2) - 7;
	while (start < end)
		my_pixel_put(game, start++, game->map_height / 2, 0x39FF14);
	start = (game->map_width / 2) + 7;
	end = (game->map_width / 2) + 20;
	while (start < end)
		my_pixel_put(game, start++, game->map_height / 2, 0x39FF14);
}

//transparent pixels in mlx have color values that are less than 0.
//So we only copy the pixels that are non-transparent from the
//hand and gun sprite to the background image buffer.
void	draw_gun(t_game *game)
{
	int	color;
	int	offset;
	int	x;
	int	y;

	x = 0;
	while (x < game->map_width - 1)
	{
		y = 0;
		while (y < game->map_height - 1)
		{
			offset = (game->album[1].tex_width * y) + x;
			color = *(game->album[1].img_pixels_ptr + offset);
			if (color > 0)
				*(game->data.img.img_pixels_ptr + offset) = color;
			y++;
		}
		x++;
	}
}

void	ray_cast(t_game *game)
{
	t_dda		dda;
	t_vector	pos;
	t_tex		tex;
	double		x;

	flush(*game);
	pos = (t_vector){game->player_posx, game->player_posy};
	x = 0;
	while (x < game->map_width)
	{
		init_params_and_vectors(game, &dda, &(dda.ray_dir), x);
		set_up_delta_dist(&dda);
		set_up_side_dist(&pos, &dda);
		dda_loop(game, &dda);
		set_up_start_end(game, &dda);
		set_up_tex_x(game, dda, &tex);
		draw_ceiling_and_floor(game, dda, x);
		texture_loop(game, &tex, dda, x);
		x++;
	}
	draw_cross_hair(game);
	draw_gun(game);
	mlx_put_image_to_window(game->data.mlx_ptr, game->data.win_ptr,
		game->data.img.img_ptr, 0, 0);
}
