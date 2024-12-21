/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meabdelk <meabdelk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 00:00:28 by meriem            #+#    #+#             */
/*   Updated: 2024/12/21 11:17:48 by meabdelk         ###   ########.fr       */
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

void free_map2(t_map *map)
{
    int i;

    i = 0;
    while (i < map->countlines_map)
    {
        free(map->map_copy[i]);
        i++;
    }
    free(map->map_copy);
}

void free_text(char **texture)
{
    int i;

    if(!texture)
        return;
    i = 0;
    while (texture[i])
    {
        free(texture[i]);
        i++;
    }
    free(texture);
}

void free_all(t_map *map)
{
    free_map(map);
    free(map->count);
    free(map->we_texture);
    free(map->so_texture);
    free(map->no_texture);
    free(map->ea_texture);
}
