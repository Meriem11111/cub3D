/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meabdelk <meabdelk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:20:48 by meabdelk          #+#    #+#             */
/*   Updated: 2025/01/22 22:01:04 by meabdelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void file_err(int i)
{
    if(i == 1)
    {
        printf("Error\n file \n");
        exit(0);
    }
    if(i == 2)
    {
        printf("Error\n opening file !\n");
        exit( 0);
    }
    if(i == 3)
    {
        printf("Error\n empty map !\n");
        exit(0);
    }
    if(i == 4)
    {
        printf("Error\n comma count !\n");
        exit(0);
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


//put lines in char**map and the rest in textures and floor/ceiling
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
        exit(0);
    line = get_next_line(fd);
    // if(line[0] == '\n')
    // {
    //     printf("ERROR new_line first row \n");
    //     free(line);
    //     exit(1);
    // }
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
    map->count->ea_count = 0;
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



int get_longest_line(char **line)
{
	int i;
	int j;
	int longest;

	i = 0;
	j = 0;
	longest = 0;
	while(line[i])
	{
		while(line[i][j])
		{
			j++;
		}
		if(j > longest)
			longest = j;
		j = 0;
		i++;
	}
	return (longest);
}

void parse_map(t_map *map, int i)
{
	int j;
	int size;

	j = i;
	size = 0;
	int l = get_longest_line(map->line);
    map->map_j = l;
	while (map->line[j])
	{
		size++;
		j++;
	}
    map->map_i = size;
	printf("size is is %d\n", size);
	map->map = malloc(sizeof(char *) * (size + 1));
	j = 0;
	while (j < size)
	{
		map->map[j] = malloc(sizeof(char) * (l + 1));
		j++;
	}
	j = 0;
	l = 0;
	while (map->line[i])
	{
		while (map->line[i][j])
		{
			map->map[l][j] = map->line[i][j];
			j++;
		}
		map->map[l][j] = '\0';
		// printf("l is %d map is %s\n",l,  map->map[l]);
		i++;
		l++;
		j = 0;
	}
	map->map[size] = NULL;
}

// void check_map(t_map *map)
// {
//     int i;

//     i = 0;
//     check_textures(map, i);
//     check_fc(map, i);
//     check_multiple(map);
//      if(ft_get_map(map, &i) != 1)
//     {
//         check_valid_map(map, &i);
//     } 
//     else
//     {
// 		printf("Map doesn't exist!\n");
//         free_all(map);
//         exit(0);
//     }
// 	parse_map(map, i + 1);
//     // printf("after line = %s\n", map->line[i + 1]);
    
// }

void init_data(t_map *map)
{
    map->countlines = 0;
    map->line = NULL;
    map->count = malloc(sizeof(t_count));
    if(!map->count)
        return;
    map->map_i = 0;
    map->map_j = 0;
    map->map_copy = NULL;
    map->ea_texture = NULL;
    map->we_texture = NULL;
    map->no_texture = NULL;
    map->so_texture = NULL;
    ft_memset(map->c_color, -1, sizeof(map->c_color));
    ft_memset(map->f_color, -1, sizeof(map->f_color));
    map->countlines_map = 0;
    map->s = 0;
    map->w = 0;
    map->e = 0;
    map->n = 0;
    map->x_p = 0;
    map->y_p = 0;
}

void create_image(t_data *data)
{
	t_mlx *img;

    img = malloc(sizeof(t_mlx));

    img->img = mlx_new_image(data->mlx, screenWidth, screenHeight);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								&img->endian);
    data->img = img;
}

int left(t_data *data)
{
    printf("\n\n posx before %f\n", data->posx);
    if(data->posx - 0.5 <= 0.0)
    {
        printf("rorororo\n");
        return 1;
    }
    data->posx -= 0.5;
    printf("\n\n posx after %f\n", data->posx);
    raycast(data);
    mlx_clear_window(data->mlx, data->mlx_win);
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0); 
    return 0;                                           
}

int right(t_data *data)
{
    data->posx += 1;
    if (data->posx >= data->map->map_j)
        return 1;
    raycast(data);
    mlx_clear_window(data->mlx, data->mlx_win);
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0); 
    return 0;
}

int front(t_data *data)
{
    data->posy -= 1;
    raycast(data);
    mlx_clear_window(data->mlx, data->mlx_win);
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0); 
    return 0;
//     raycast(data);
//     mlx_clear_window(data->mlx, data->mlx_win);
//     mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);    
}

int back(t_data *data)
{
    data->posy += 1;
    raycast(data);
    mlx_clear_window(data->mlx, data->mlx_win);
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0); 
    return 0;
    // raycast(data);
    // mlx_clear_window(data->mlx, data->mlx_win);
    // mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);    
}

int ray(int keycode ,t_data *data)
{
    // raycast(data);
    // (int)data;
    // printf("key is %d\n", keycode);
    // mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
    // mlx_clear_window(data->mlx, data->mlx_win);
    if (keycode == 119)
		if(front(data) == 1)
            return 0;
	if (keycode == 115)
		if (back(data) == 1)
            return 0;
	if (keycode == 97)
		if (left(data) == 1)
            return 0;
	if (keycode == 100)
		if (right(data) == 1)
            return 0;
	if (keycode == 65307)
    {
        mlx_destroy_window(data->mlx, data->mlx_win);
		exit(1);
    }
	return 0;
}


int delete_window(t_data *data)
{
    mlx_destroy_window(data->mlx, data->mlx_win);
	exit(1);
}
void    create_window(t_data *data, t_map *map, t_wall *wall)
{
    // void	*mlx;
	// void	*mlx_win;
	// t_map   map;
    // printf("map --> %s\n", map->map[0]);
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, screenWidth, screenHeight, "Hello world!");
	// draw_a_line(&img);
    ray_data_init(data, map, wall);
    player_init(data);
    data_init(data);
    raycast(data);
    mlx_clear_window(data->mlx, data->mlx_win);
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
    mlx_key_hook(data->mlx_win, &ray, data);
    mlx_hook(data->mlx_win, 17, 0, (void *)delete_window, data);
	mlx_loop(data->mlx);
}

int main(int ac, char **av)
{
    t_map map;
    t_wall wall;
    t_data data;
 
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
    create_window(&data, &map, &wall);
    free_all(&map);
    return(0);
}
