/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meabdelk <meabdelk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 00:00:28 by meriem            #+#    #+#             */
/*   Updated: 2025/02/02 21:30:31 by meabdelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_map(t_map *map)
{
    int i;

    i = 0;
    while (i < map->countlines)
    {
        free(map->line[i]);
        i++;
    }
    free(map->line);
}

void freee(t_map *map)
{
    free_map(map);
    free(map->count);
}

void free_all(t_map *map)
{
    mlx_destroy_image(map->data->mlx, map->data->img->img_e);
    mlx_destroy_image(map->data->mlx, map->data->img->img_n);
    mlx_destroy_image(map->data->mlx, map->data->img->img_s);
    mlx_destroy_image(map->data->mlx, map->data->img->img_w);
    mlx_destroy_image(map->data->mlx, map->data->img->img);
    mlx_destroy_window(map->data->mlx, map->data->mlx_win);
    mlx_destroy_display(map->data->mlx);
    free(map->data->img);
    free_map(map);
    free(map->data->minimap);

    free(map->count);
}