/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meriem <meriem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:20:48 by meabdelk          #+#    #+#             */
/*   Updated: 2024/12/13 22:53:08 by meriem           ###   ########.fr       */
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

void ini(t_map *map)
{
    map->count->no_count = 0;
    map->count->so_count = 0;
    map->count->we_count = 0;
    map->count-> ea_count = 0;
    map->count->c_count = 0;
    map->count->f_count = 0;
}

int count_part(char **value)
{
    int i;
     
    if(!value)
        return(0);
    i = 0;
    while(value[i])
    {
        i++;
    }
    // printf("i == %d \n", i);
    return(i);
}

int check_path(const char *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    // int i = 0;
    // while(path[i])
    // {
    //     printf("i == ^[%c]^ \n", path[i]);
    //     i++;
    // }
    if(fd < 0)
    {
        printf("Error ! invalid texture path : %s \n", path);
        return(1);
    }
    close(fd);
    return(0);
}




void init_data(t_map *map)
{
    map->countlines = 0;
    map->line = NULL;
    map->ea_texture = NULL;
    map->we_texture = NULL;
    map->no_texture = NULL;
    map->so_texture = NULL;
    map->c_color = -1;
    map->f_color = -1;
    map->count = malloc(sizeof(t_count));
    if(!map->count)
        return;
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
// printf("----> texture ea ==  main %s \n", map.ea_texture);
//   printf("----> texture we ==  main %s \n", map.we_texture);
//   printf("----> texture no ==  main %s \n", map.no_texture);
//   printf("----> texture so ==  main %s \n", map.so_texture);
//   printf("----> texture f ==  main %s \n", map.f_color);
//     printf("----> texture c ==  main %s \n", map.c_color);
    free_all(&map);
    return(0);
}
