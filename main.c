/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meabdelk <meabdelk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:20:48 by meabdelk          #+#    #+#             */
/*   Updated: 2024/12/08 14:46:32 by meabdelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void file_err(int i)
{
    if(i == 1)
    {
        printf("Error ! file \n");
        exit(1);
    }
    if(i == 2)
    {
        printf("Error ! opening file !\n");
        exit( 0);
    }
    if(i == 3)
    {
        printf("Error ! empty map \n");
        exit(1);
    }
}

void check_file(char *file)
{
    int i;
    int j;
    char *str;

    i = ft_strlen(file);
    str = ".cub";
    j = ft_strlen(str);
    if(i <= j)
        file_err(1);
    while(j >= 0)
    {
        if(file[i] != str[j])
        {
           file_err(1);
        }
        i--;
        j--;
    }
    if(i >= 0 && file[i] == '/')
        file_err(1);
}

int ft_countlines(char *av)
{
    int count;
    char *line;
    int fd;

    count = 0;
    fd = open(av, O_RDONLY);
    if(fd == -1)
        file_err(2);
    line = get_next_line(fd);
    while(line)
    {
        count++;
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    if(count == 0)
    {
        printf("error ! empty file \n");
        exit(0);
    }
    return(count);
}

void get_map(char *av, t_map *map)
{
    int fd;
    char *line;
    int i;
    
    i = 0;
    fd = open(av, O_RDONLY);
    if(fd == -1)
        file_err(2);
    map->countlines = ft_countlines(av);
    if(map->countlines == 0)
        file_err(3);
    map->line = malloc(sizeof(char *) * (map->countlines + 1));
    if(!map->line)
        exit(1);
    line = get_next_line(fd);
    if(line[0] == '\n')
    {
        printf("ERROR new_line first row \n");
        free(line);
        exit(1);
    }
    while(line)
    {
        map->line[i] = line;
        i++;
        line = get_next_line(fd);
    }
    map->line[map->countlines] = NULL;
    free(line);
    close(fd);
}

// void check_textures(t_map *map, int *i)
// {
//     int count;

//     count = 0;
//     while(map->line[*i])
//     {
//         printf("line = %s\n", map->line[*i]);
        
//         // Check for "NO", "SO", "WE", "EA" at the start of the line
//         if ((ft_strncmp(map->line[*i], "NO", 2) == 0 && map->line[*i][2] == ' ') ||
//             (ft_strncmp(map->line[*i], "SO", 2) == 0 && map->line[*i][2] == ' ') ||
//             (ft_strncmp(map->line[*i], "WE", 2) == 0 && map->line[*i][2] == ' ') ||
//             (ft_strncmp(map->line[*i], "EA", 2) == 0 && map->line[*i][2] == ' '))
//         {
//             count++;
//         }
        
//         (*i)++;
//     }

//     printf("count == %d\n", count);
//     if(count != 4)
//     {
//         printf("ERROR texture\n");
//     }
// }



void check_textures(t_map *map, int *i)
{
    int count;

    count = 0;
    while(map->line[*i] && *i < 4)
    {
        if((ft_strncmp(map->line[*i], "NO", 2) == 0 
            || ft_strncmp(map->line[*i], "SO", 2) == 0
            || ft_strncmp(map->line[*i], "WE", 2) == 0
            || ft_strncmp(map->line[*i], "EA", 2) == 0 ) && (map->line[*i][2] == ' '))
        {
            check_multiple()
            count++;
        }
        (*i)++;
    }
    if(count != 4)
        printf(" ERROR texture \n");
}

void check_fc(t_map *map, int *i)
{
    int count;

    count = 0;
    (*i)++;
    while(map->line[*i] && count < 2)
    {
        
        printf(" --> line = %s\n", map->line[*i]);
        if((ft_strncmp(map->line[*i], "F", 1) || ft_strncmp(map->line[*i], "C", 1))
            && (map->line[*i][1] == ' '))
        {
            count++;        
        }
        (*i)++;
    }
    if(count != 2)
        printf(" ERROR floor and ceiling \n");
}

void check_map(t_map *map)
{
    int i;

    i = 0;
    check_textures(map, &i);
    // printf("first line = %s\n", map->line[i]);
    while (map->line[i] && ft_strchar(map->line[i], '\n') == 0)
    {
        i++;
    }
    check_fc(map, &i);
    while (map->line[i] && ft_strchar(map->line[i], '\n') == 0)
    {
        i++;
    }
    printf("after line = %s\n", map->line[i + 1]);
    
}

void init_data(t_map *map)
{
    map->countlines = 0;
    map->line = NULL;
}

int main(int ac, char **av)
{
    t_map map;
    
    if(ac <= 1)
        exit(0);
    if(ac != 2)
    {
        printf("Error\nnumber of args\n");
	    exit(0);
    }
    check_file(av[1]);
    init_data(&map);
    get_map(av[1], &map);
    check_map(&map);
    
    return(0);
}
