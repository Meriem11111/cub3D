/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meabdelk <meabdelk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:20:48 by meabdelk          #+#    #+#             */
/*   Updated: 2024/12/22 13:02:11 by meabdelk         ###   ########.fr       */
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
    if(i == 4)
    {
        printf("error ! comma count \n");
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
        free(line);
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
    return(i);
}
int count_comma(char *value)
{
    int j;
    int count;
    char *str;
     
    if(!value)
        return(0);
    count = 0;
    j = 0;
    str = ft_strtrim(value, "\n");
    while(str[j])
    {
        if(str[j] == ',')
        {
            count++;
        }
        j++;
    }
    free(str);
    return(count);
}

int check_path(const char *path)
{
    int fd;

    fd = open(path, O_RDONLY);
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
    map->file_name = NULL;
    map->map_copy = NULL;
    map->ea_texture = NULL;
    map->we_texture = NULL;
    map->no_texture = NULL;
    map->so_texture = NULL;
    ft_memset(map->c_color, -1, sizeof(map->c_color));
    ft_memset(map->f_color, -1, sizeof(map->f_color));
    map->count = malloc(sizeof(t_count));
    if(!map->count)
        return;
    map->countlines_map = 0;
    map->s = 0;
    map->w = 0;
    map->e = 0;
    map->n = 0;
    map->x_p = 0;
    map->y_p = 0;
}

void	delete_window(t_map *map)
{
	mlx_destroy_window((map)->mlx, (map)->win);
	exit(0);
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
    map.file_name = av[1];
    check_map(&map);
    map.mlx = mlx_init();
    if (map.mlx == NULL)
	{
		return (1);
	}
    map.win = mlx_new_window(map.mlx, 600, 400, "test");
    mlx_hook(map.win, 17, 0, (void *)delete_window, &map);
    mlx_loop(map.mlx);
    free_all(&map);
    return(0);
}
