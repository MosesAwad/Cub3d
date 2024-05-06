
#include "cub3d.h"

void    set_up_images(t_game *game)
{
    game->album[0].img = mlx_xpm_file_to_image(
        game->data.mlx_ptr, "images/brick.xpm",
            &(game->album[0].tex_width), &(game->album[0].tex_height));

    if (game->album[0].img)
    {
        printf("Img ptr aint null and img width x height -> %d x %d\n", game->album[0].tex_width, game->album[0].tex_height); 
    }
    game->album[0].img_pixels_ptr = (int *)mlx_get_data_addr(game->album[0].img,
            &(game->album[0].bits_per_pixel), &(game->album[0].line_len),
                &(game->album[0].endian));
}