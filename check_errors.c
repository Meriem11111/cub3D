/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meabdelk <meabdelk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:04:01 by meabdelk          #+#    #+#             */
/*   Updated: 2024/12/30 09:48:02 by meabdelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_last(t_map *map, int *i)
{
    int k;
    int j;
    int len;
   

    k = *i;
    j = 0;
    while(map->line[k])
    {
        k++;
    }
    map->countlines_map = k - (*i);
    len = ft_strlen(map->line[k - 1]) - 1;
    while(map->line[k - 1][j] && j < len)
    {
       if(map->line[k - 1][j] != '1' && map->line[k - 1][j] != ' ' && map->line[k - 1][j] != '\t')
       {
            printf("Error \n invalid border \n ");
            free_all(map);
            exit(0);
       }
       j++;
    }
}

void check_first_last(t_map *map, int *i)
{
    int k;
    int j;
    int len;

    k = *i;
    j = 0;
    len = ft_strlen(map->line[k]) - 1;
    while(map->line[k][j] && j < len)
    {
       if(map->line[k][j] != '1' && map->line[k][j] != ' ' && map->line[k][j] != '\t')
       {
            printf("Error \n invalid border \n ");
            free_all(map);
            exit(0);
       }
       j++;
    }
    check_last(map, i);
}

int skp_spaces(char *line)
{
    int i;

    i = 0;
    while(line[i] == ' ' || line[i] == '\t')
    {
        i++; 
    }
    return(i);
}

void check_map_borders(t_map *map, int *i)
{
    int k;
    int j;
    
    k = *i;
    while(map->line[k])
    {
        j = skp_spaces(map->line[k]);
        if (map->line[k][0] == '\n') 
        {
            k++;
            continue;
        }
        if(map->line[k][j] != '1' || (map->line[k][ft_strlen(map->line[k]) - 2] != '1' 
            && map->line[k][ft_strlen(map->line[k]) - 2] != ' ' && map->line[k][ft_strlen(map->line[k]) - 2] != '\t'))
        {
            printf("Error\n Invalid map !\n");
            printf(" -------->k == %d \n", k);
            free_all(map);
            exit (0);
        }
        k++;
    }
}

void check_characters(t_map *map, int *i)
{
    int k;
    int j;

    k = *i;
    while (map->line[k])
    {
        j = ft_strlen(map->line[k]) - 2;
        while(j >= 0)
        {
            if(map->line[k][j] == 'S')
                map->s++;
            else if(map->line[k][j] == 'W')
                map->w++;
            else if(map->line[k][j] == 'E')
                map->e++;
            else if(map->line[k][j] == 'N')
                map->n++;
            else if(map->line[k][j] != '1' && map->line[k][j] != '0'
                && map->line[k][j] != ' ' && map->line[k][j] != '\t')
            {
                printf("Error\n Unknown character \n");
                free_all(map);
                exit(0);
            }
            j--;
        }
        k++;
    }
    ft_error(map); 
}

void ft_error(t_map *map)
{
    int count;

    count = map->e + map->w + map->n + map->s;
    if(count == 0)
    {
        printf("error \n missing player !\n");
        free_all(map);
        exit(0);
    }
    else if(count != 1)
    {
        printf("error \n more than one player found!\n");
        free_all(map);
        exit(0);
    }
}

void verify_space(t_map *map, int i, int j)
{
    if((map->map_copy[i + 1][j] == ' ' || map->map_copy[i + 1][j] == '\t' ||  map->map_copy[i + 1][j] == '\n') 
        || (map->map_copy[i - 1][j] == ' ' || map->map_copy[i - 1][j] == '\t' ||  map->map_copy[i - 1][j] == '\n') 
        || (map->map_copy[i][j + 1] == ' ' || map->map_copy[i][j + 1] == '\t' ||  map->map_copy[i][j + 1] == '\n') 
        || (map->map_copy[i][j - 1] == ' ' || map->map_copy[i][j - 1] == '\t'||  map->map_copy[i][j - 1] == '\n' ))
        {
            printf("Error\n '0' is surrounded by spaces at line %d, column %d\n", i, j);
            free_all(map);
            exit(0); 
        }
    
}

void check_spaces(t_map *map)
{
    int i;
    int j;
    int len;
    
    i = 0;
    while(i < map->countlines_map)
    {
        j = 0;
        len = ft_strlen(map->map_copy[i]) -1;
        while(j < len)
        {
            if(map->map_copy[i][j] == '0')
            {
                verify_space(map, i, j);
            }
            j++;  
        }
        i++;
    }
}


// #include <math.h>
// #include <stdio.h>
// #include <stdlib.h>

// #define RAY_COUNT 320   // Number of rays for the field of view
// #define FOV 1.047198    // Field of View (60 degrees in radians)
// #define MOVE_SPEED 5.0  // Player's move speed
// #define ROT_SPEED M_PI / 36  // Rotation speed (5 degrees)

// typedef struct s_map {
//     double player_x;
//     double player_y;
//     double rot_angle;
//     char **map;  // Map representation ('1' = wall, '0' = open space)
//     int map_width;
//     int map_height;
// } t_map;

// // Check if the ray hits a wall (simple version)
// int hit_wall(double ray_x, double ray_y, t_map *map)
// {
//     if (ray_x < 0 || ray_x >= map->map_width || ray_y < 0 || ray_y >= map->map_height)
//         return 1;  // Hit a wall (out of bounds)
//     if (map->map[(int)ray_y][(int)ray_x] == '1')  // Wall hit
//         return 1;
//     return 0;  // No collision
// }

// // Cast rays and check for walls
// void cast_rays(t_map *map)
// {
//     double ray_angle;
//     double ray_x, ray_y;
//     double distance_to_wall;
//     double step_size = 0.1;  // How much we move along each ray

//     // Loop through each ray (for each pixel on the screen)
//     for (int i = 0; i < RAY_COUNT; i++) {
//         // Calculate the angle for this ray
//         ray_angle = map->rot_angle + (FOV / 2) - (i * (FOV / RAY_COUNT));
        
//         // Initialize ray position (starting from the player's position)
//         ray_x = map->player_x;
//         ray_y = map->player_y;

//         // Move along the ray in small steps
//         while (!hit_wall(ray_x, ray_y, map)) {
//             ray_x += cos(ray_angle) * step_size;  // Move right or left (X)
//             ray_y += sin(ray_angle) * step_size;  // Move up or down (Y)
//         }

//         // Calculate the distance to the wall (using the Pythagorean theorem)
//         distance_to_wall = sqrt((ray_x - map->player_x) * (ray_x - map->player_x) +
//                                 (ray_y - map->player_y) * (ray_y - map->player_y));

//         // Here, you can store the distance or use it to draw the ray (optional)
//         printf("Ray %d: Hit wall at distance: %.2f\n", i, distance_to_wall);
//     }
// }
