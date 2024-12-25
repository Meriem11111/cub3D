/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meabdelk <meabdelk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:03:04 by meabdelk          #+#    #+#             */
/*   Updated: 2024/12/25 11:58:14 by meabdelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void to_right(t_map *map)
{
    int x;
    int y;

    x = map->x_p;
    y = map->y_p;
    printf("right\n");
    if(map->map_copy[y][x + 1] != '1' && map->map_copy[y][x+1] != ' ' && map->map_copy[y][x + 1] != '\t')
    {
        map->map_copy[y][x + 1] = map->map_copy[y][x];
        map->map_copy[y][x] = '0';
        map->x_p = x + 1;
    }
}

void to_left(t_map *map)
{
    int x;
    int y;
    
    x = map->x_p;
    y = map->y_p;
    printf("left\n");
    if(map->map_copy[y][x -1] != '1' && map->map_copy[y][x - 1] != ' ' && map->map_copy[y][x - 1] != '\t')
    {
        map->map_copy[y][x - 1] = map->map_copy[y][x];
        map->map_copy[y][x] = '0';
        map->x_p = x - 1;
    }
}

void to_down(t_map *map)
{
    int x;
    int y;
    
    x = map->x_p;
    y = map->y_p;
    printf("down\n");
    if(map->map_copy[y + 1][x] != '1' && map->map_copy[y +1][x] != ' ' && map->map_copy[y +1][x] != '\t')
    {
        map->map_copy[y + 1][x] = map->map_copy[y][x];
        map->map_copy[y][x] = '0';
        map->y_p = y + 1 ;
    }
}

void to_up(t_map *map)
{
    int x;
    int y;
    
    x = map->x_p;
    y = map->y_p;
    printf("up\n");
    if(map->map_copy[y - 1][x] != '1' && map->map_copy[y - 1][x] != ' ' && map->map_copy[y - 1][x] != '\t')
    {
        map->map_copy[y - 1][x] = map->map_copy[y][x];
        map->map_copy[y][x] = '0';
        map->y_p = y - 1;
    }
}
