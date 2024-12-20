/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meabdelk <meabdelk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:04:01 by meabdelk          #+#    #+#             */
/*   Updated: 2024/12/20 17:24:54 by meabdelk         ###   ########.fr       */
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
    len = ft_strlen(map->line[k - 1]) - 1;
    while(map->line[k - 1][j] && j < len)
    {
       if(map->line[k - 1][j] != '1' && map->line[k - 1][j] != ' ' && map->line[k - 1][j] != '\t')
       {
            printf("Error ! invalid border \n ");
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
            printf("Error ! invalid border \n ");
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
        if(map->line[k][j] != '1' || map->line[k][ft_strlen(map->line[k]) - 2] != '1')
        {
            printf("Error ! not surrounded by walls !");
            free_all(map);
            exit (0);
        }
        k++;
    }
}
