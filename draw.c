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
    // printf("r = %d | g = %d | b = %d  \n", data->map->c_color[0], data->map->c_color[1] , data->map->c_color[2]);
    return((data->map->c_color[0] << 16) | (data->map->c_color[1] << 8) | data->map->c_color[2]);
}

int rgb_f(t_data *data)
{
    // printf("r = %d | g = %d | b = %d  \n", data->map->c_color[0], data->map->c_color[1] , data->map->c_color[2]);
    return((data->map->f_color[0] << 16) | (data->map->f_color[1] << 8) | data->map->f_color[2]);
}

void draw_fc(t_data *data, int x)
{
    int i = 0;
    
    while(i < data->wall->draw_start)
    {
        // printf("  --> d == %d \n", i * screenWidth + x);
        my_mlx_pixel_put(data->img, x, i, rgb_c(data));
        i++;
    }
    i = data->wall->draw_end;
    while(i < screenHeight)
    {
        my_mlx_pixel_put(data->img, x, i, rgb_f(data));
        i++;
    }
}
