/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meabdelk <meabdelk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:37:18 by meabdelk          #+#    #+#             */
/*   Updated: 2025/01/20 16:37:30 by meabdelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int rgb_c(t_data *data)
{
    return((data->map->c_color[0] << 16) | (data->map->c_color[1] << 8) | data->map->c_color[2]);
}

int rgb_f(t_data *data)
{
    return((data->map->f_color[0] << 16) | (data->map->f_color[1] << 8) | data->map->f_color[2]);
}

void draw_fc(t_data *data, int x, double *y)
{
    int i = 0;
    
    while(i < data->wall->draw_start)
    {
        my_mlx_pixel_put(data->img, x, i, rgb_c(data));
        i++;
        (*y)++;
    }
    i = data->wall->draw_end;
    while(i < screenHeight)
    {
        my_mlx_pixel_put(data->img, x, i, rgb_f(data));
        i++;
    }
}



void load_tex(t_data *data)
{

    if (data->img == NULL)
    {
        return;
    }
    
    
        data->img->img_w = mlx_xpm_file_to_image(data->mlx, "./textures/tex4.xpm", &data->img->win_width, &data->img->win_height);
   
        data->img->img_e = mlx_xpm_file_to_image(data->mlx,"./textures/tex4.xpm", &data->img->win_width, &data->img->win_height);
   
        data->img->img_n = mlx_xpm_file_to_image(data->mlx, "./textures/tex4.xpm", &data->img->win_width, &data->img->win_height);
   
        data->img->img_s = mlx_xpm_file_to_image(data->mlx, "./textures/tex4.xpm", &data->img->win_width, &data->img->win_height);
}


void init_img(t_data *data)
{
    data->img->add_pxl_e = mlx_get_data_addr(data->img->img_e, &data->img->bits_per_pixel_e, &data->img->line_length_e, &data->img->endian_e);
    data->img->add_pxl_w = mlx_get_data_addr(data->img->img_w, &data->img->bits_per_pixel_w, &data->img->line_length_w, &data->img->endian_w);
    data->img->add_pxl_s = mlx_get_data_addr(data->img->img_s, &data->img->bits_per_pixel_s, &data->img->line_length_s, &data->img->endian_s);
    data->img->add_pxl_n = mlx_get_data_addr(data->img->img_n, &data->img->bits_per_pixel_n, &data->img->line_length_n, &data->img->endian_n);
}

void render_wall(t_data *data, int x)
{
    double distance;
   double off_y;
    double y;
    // int color = 0;

    y = 0;
    draw_fc(data, x, &y);
    init_img(data);
    // printf("Texture Width: %d, Height: %d\n", data->img->win_width, data->img->win_height);
printf("prepwalldist: %f, line_length: %f\n", data->prepwalldist, data->wall->line_length);
    
    // printf("end = %f\n", data->wall->draw_end);
    // printf("wall = %f\n", data->wall->line_length);
    // printf("y = %f\n", y);
    while(y <= data->wall->draw_end)
    {
       distance = y + ((data->wall->line_length / 2) -  (screenHeight / 2));
       off_y = distance * ((double)data->img->win_height / data->wall->line_length);

        if(data->side == 0 && data->stepx == -1)
        {
            // color = 0xFF0000; // RED
            // my_mlx_pixel_put(data->img, x, y, color);
            draw_w(data, x, y, (int)off_y);
        }
        else if(data->side == 0 && data->stepx == 1)
        {
            // color = 0xFFFF00; // Yellow
            // my_mlx_pixel_put(data->img, x, y, color);
            //printf("----%f\n", off_y);
          draw_e(data, x, y, (int)off_y);
        }
        else if(data->side == 1 && data->stepy == -1)
        {
            // color = 0x0000FF; // Blue
            // my_mlx_pixel_put(data->img, x, y, color);
           draw_n(data, x, y, (int)off_y);
        }
        else if(data->side == 1 && data->stepy == 1)
        {
            // color = 0xFFB6C1;// pink
            // my_mlx_pixel_put(data->img, x, y, color);
            draw_s(data, x, y, (int)off_y);
        }
        y++;
    }
    printf("***************\n");

}

void draw_w(t_data *data, int x, int y, int tex_y)
{
    int color;
    double tex_x;
    double wall_x;

    if (data->side == 0) 
        wall_x = data->posy + data->prepwalldist * data->raydirY;
    else // Vertical wall
        wall_x = data->posx + data->prepwalldist * data->raydirX;

    wall_x -= floor(wall_x); 
    tex_x = (int)(wall_x * (double)data->img->win_width);

    if (data->side == 0 && data->raydirX > 0) 
        tex_x = data->img->win_width - tex_x - 1;
    if (data->side == 1 && data->raydirY < 0) 
        tex_x = data->img->win_width - tex_x - 1;

    if (tex_y >= 0 && tex_y < data->img->win_height && tex_x >= 0 && tex_x < data->img->win_width)
    {
        color = *(int *)(data->img->add_pxl_w + ((int)tex_y * data->img->line_length_w + (int)tex_x * (data->img->bits_per_pixel_w / 8)));
        my_mlx_pixel_put(data->img, x, y, color);
    }
}

void draw_s(t_data *data, double x, double y, double tex_y)
{
    int color;
    double tex_x;
    double wall_x;

    if (data->side == 0) // Horizontal wall
        wall_x = data->posy + data->prepwalldist * data->raydirY;
    else // Vertical wall
        wall_x = data->posx + data->prepwalldist * data->raydirX;

    wall_x -= floor(wall_x); 
    tex_x = (int)(wall_x * (double)data->img->win_width);

    
    if (data->side == 0 && data->raydirX > 0) 
        tex_x = data->img->win_width - tex_x - 1;
    if (data->side == 1 && data->raydirY < 0) 
        tex_x = data->img->win_width - tex_x - 1;

    if (tex_y >= 0 && tex_y < data->img->win_height && tex_x >= 0 && tex_x < data->img->win_width)
    {
        color = *(int *)(data->img->add_pxl_s + ((int)tex_y * data->img->line_length_s + (int)tex_x * (data->img->bits_per_pixel_s / 8)));
        my_mlx_pixel_put(data->img, x, y, color);
    }
}

void draw_e(t_data *data, double x, double y, double tex_y)
{
    int color;
    double tex_x;
    double wall_x;

    if (data->side == 0) // Horizontal wall
        wall_x = data->posy + data->prepwalldist * data->raydirY;
    else // Vertical wall
        wall_x = data->posx + data->prepwalldist * data->raydirX;

    wall_x -= floor(wall_x); 
    tex_x = (int)(wall_x * (double)data->img->win_width);

  
    if (data->side == 0 && data->raydirX > 0) 
        tex_x = data->img->win_width - tex_x - 1;
    if (data->side == 1 && data->raydirY < 0) 
        tex_x = data->img->win_width - tex_x - 1;

    if (tex_y >= 0 && tex_y < data->img->win_height && tex_x >= 0 && tex_x < data->img->win_width)
    {
        color = *(int *)(data->img->add_pxl_e + ((int)tex_y * data->img->line_length_e + (int)tex_x * (data->img->bits_per_pixel_e / 8)));
        my_mlx_pixel_put(data->img, x, y, color);
    }
}

void draw_n(t_data *data, double x, double y, double tex_y)
{
    int color;
    double tex_x;
    double wall_x;

    if (data->side == 0) // Horizontal wall
        wall_x = data->posy + data->prepwalldist * data->raydirY;
    else // Vertical wall
        wall_x = data->posx + data->prepwalldist * data->raydirX;

    wall_x -= floor(wall_x); 
    tex_x = (int)(wall_x * (double)data->img->win_width);

    
    if (data->side == 0 && data->raydirX > 0) 
        tex_x = data->img->win_width - tex_x - 1;
    if (data->side == 1 && data->raydirY < 0) 
        tex_x = data->img->win_width - tex_x - 1;

    if (tex_y >= 0 && tex_y < data->img->win_height && tex_x >= 0 && tex_x < data->img->win_width)
    {
        color = *(int *)(data->img->add_pxl_n + ((int)tex_y * data->img->line_length_n + (int)tex_x * (data->img->bits_per_pixel_n / 8)));
        my_mlx_pixel_put(data->img, x, y, color);
    }
}

