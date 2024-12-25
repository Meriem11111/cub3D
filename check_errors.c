/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meabdelk <meabdelk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:04:01 by meabdelk          #+#    #+#             */
/*   Updated: 2024/12/25 20:20:49 by meabdelk         ###   ########.fr       */
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
