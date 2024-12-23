/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meabdelk <meabdelk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:18:10 by meriem            #+#    #+#             */
/*   Updated: 2024/12/23 13:20:18 by meabdelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_range(int range)
{
    if(range < 0 || range > 255)
    {
        printf("error ! invalid color range \n");
        
        return(1);
    }
    return(0);
}

char **check_format_color(char *line, int flag)
{
    char **value;
    char **color_parts;
    
    if(count_comma(line) != 2)
        file_err(4);
    if(flag == 0)
        value = ft_split(line, 'F');
    else 
        value = ft_split(line, 'C');
    if(!value || count_part(value) < 2)
    {
        printf("Error! invalid format\n");
        free_text(value);
        exit(1);
    }
    color_parts = ft_split(value[1], ',');
    free_text(value);
    if(!color_parts )
    {
        printf("Error! invalid color format \n");
        free_text(color_parts);
        exit(1);
    }
    return(color_parts);
}


// char **check_format_color(char *line)
// {
//     char **value;
//     char **color_parts;
    
//     value = ft_split(line, ' ');
//     if(!value || count_part(value) != 2)
//     {
//         printf("Error! invalid format\n");
//         free_text(value);
//         exit(1);
//     }
//     color_parts = ft_split(value[1], ',');
//     free_text(value);
//     if(!color_parts || count_part(color_parts) != 3)
//     {
//         printf("Error! invalid color format \n");
//         free_text(color_parts);
//         exit(1);
//     }
//     return(color_parts);
// }

void check_valid_color(char *line, int *color, int flag)
{
    char **value;
    int i;
    int j;
    
    value = check_format_color(line, flag);
    i = 0;
    j = 0;
    while(i < 3)
    {
        value[i] = ft_strtrim(value[i], " \n");
        if(value[i][j] == '+')
            j++;
        skp_spaces(value[i]);
        if(check_digit(&value[i][j]) != 0)
        {
            printf("Error: Color values must be digits\n");
            free_text(value);
            exit(1);
        }
        color[i] = ft_atoi(value[i]);
        if(check_range(color[i]) != 0)
        {
            free_text(value);
            exit(1);
        }
        i++;
    }
    free_text(value);
}

void check_valid(char *line, char **path)
{
    char **value;
    char *temp;

    value = ft_split(line, ' ');
    if(!value || count_part(value) != 2)
    {
        printf("Error ! invalid texture \n");
        free_text(value);
        exit(1);
    }
    temp = ft_strdup(value[1]);
    *path = ft_strtrim(temp, "\n");
    free(temp);
    if(!*path)
    {
       free_text(value);
       exit(1);
    }
    free_text(value);
    if(check_path(*path) != 0)
    {
       free_text(path);
        exit(1);
    }
}

void f_c_check(t_map *map, int *i, int j)
{
    if(ft_strncmp(&map->line[*i][j], "F", 1) == 0 && (map->line[*i][j + 1] == ' '))
    {
        check_valid_color(map->line[*i], map->f_color, 0);
        map->count->f_count++;
    }
    else if(ft_strncmp(&map->line[*i][j], "C", 1) == 0 && (map->line[*i][j + 1] == ' ' ))
    {
        check_valid_color(map->line[*i], map->c_color , 1);
        map->count->c_count++;
    }
}

void process_line(t_map *map, int *i, int j)
{
    if(ft_strncmp(&map->line[*i][j], "NO", 2) == 0 && (map->line[*i][j + 2] == ' '))
    {
        check_valid(map->line[*i], &map->no_texture);
        map->count-> no_count++;
    }
    else if(ft_strncmp(&map->line[*i][j], "SO", 2) == 0 && (map->line[*i][j + 2] == ' '))
    {
        check_valid(map->line[*i], &map->so_texture);
        map->count->so_count++;
    }
    else if(ft_strncmp(&map->line[*i][j], "WE", 2) == 0 && (map->line[*i][j + 2] == ' '))
    {
        check_valid(map->line[*i], &map->we_texture);
        map->count->we_count++;
    }
    else if(ft_strncmp(&map->line[*i][j], "EA", 2) == 0 && (map->line[*i][j + 2] == ' '))
    {
        check_valid(map->line[*i], &map->ea_texture);
        map->count->ea_count++;
    }
    else if(ft_strncmp(&map->line[*i][j], "F", 1) == 0 || ft_strncmp(&map->line[*i][j], "C", 1) == 0)
        f_c_check(map, i, j);
    (*i)++;
}

void check_multiple(t_map *map)
{
    int i;
    int j;

    i = 0;
    ini(map);
    while(map->line[i])
    {
        j = skp_spaces(map->line[i]);
        process_line( map, &i, j);
    }
    if(map->count->no_count != 1 || map->count->so_count != 1 || map->count->we_count != 1 
        || map->count->ea_count != 1 || map->count->f_count != 1 || map->count->c_count != 1)
    {
        printf("Error textures !! \n");
        free(map->count);
        exit(1);
    }
}


void check_textures(t_map *map, int *i)
{
    int count;
    int j;
    
    count = 0;
    j = 0;
    while(map->line[*i] && *i < 4)
    {
        j = skp_spaces(map->line[*i]);
        if((ft_strncmp(&map->line[*i][j], "NO", 2) == 0 
            || ft_strncmp(&map->line[*i][j], "SO", 2 ) == 0
            ||ft_strncmp(&map->line[*i][j], "WE", 2) == 0
            || ft_strncmp(&map->line[*i][j], "EA", 2) == 0 ) && (map->line[*i][j + 2] == ' '))
        {
            count++;
        }
        (*i)++;
    }   
    if(count != 4)
    {
        printf(" ERROR texture \n");
        free_all(map);
        exit(0);
    }
}

void check_fc(t_map *map, int *i)
{
    int count;
    int j;

    count = 0;
    while(map->line[*i] && count < 2)
    {
        j = skp_spaces(map->line[*i]);
        if((ft_strncmp(&map->line[*i][j], "F", 1) || ft_strncmp(&map->line[*i][j], "C", 1))
            && (map->line[*i][j + 1] == ' '))
        {
            count++;        
        }
        (*i)++;
    }
    if(count != 2)
    {
        printf(" ERROR floor and ceiling \n");
        free_all(map);
        exit(0); 
    }    
}

void skp_line(t_map *map, int *i)
{
    while (map->line[*i])
    {
        if(map->line[*i][0] == '\n')
        {
            (*i)++;
        }
        else
            break;
    }
}

void get_len(t_map *map)
{
    int count;
    int i;
    int j;

    count = 0;
    i = 0;
    while(map->map_copy[i])
    {
        j = 0;
        while(map->map_copy[i][j] != '\0')
        {
            count++;
            j++;
        }
        if(map->len < count)
        {
            map->len = count;
        }
        count = 0;
        i++;
    }
}

void get_map2(t_map *map, int *i)
{
    int j;
    int k;
    
    j = *i;
    k = 0;
    if(map->countlines_map == 0)
        file_err(3);
    map->map_copy = malloc(sizeof(char *) * (map->countlines_map + 1));
    if(!map->map_copy)
        exit(1);
    while(map->line[j])
    {
        map->map_copy[k] = map->line[j];
        j++;
        k++;
    }
    map->map_copy[k] = NULL;
    get_len(map);
    
}

void check_player(t_map *map, int j, int i)
{
    if(map->map_copy[i + 1][j] == '1' && map->map_copy[i - 1][j] == '1'
        && map->map_copy[i][j + 1] == '1' && map->map_copy[i][j - 1] == '1' )
    {
        printf("Error ! player surrounded by walls \n");
        free_all(map);
        exit(0);
    }
}
void pos_player(t_map *map)
{
    int i;
    int j;
    int len;

    i = 0;
    while(i < map->countlines_map)
    {
        j = 0;
        len = ft_strlen(map->map_copy[i]) - 1;
        while (j < len)
        {
            if(map->map_copy[i][j] == 'N' || map->map_copy[i][j] == 'S' 
                || map->map_copy[i][j] == 'E' || map->map_copy[i][j] == 'W')
            {
                map->x_p = j;
                map->y_p = i;
                check_player(map, map->x_p, map->y_p);
                return;
            }
            j++;
        }
        i++;
    }
}

void check_valid_map(t_map *map, int *i)
{
    check_first_last(map, i);
    check_map_borders(map, i);
    check_characters(map, i);
    get_map2(map, i);
    pos_player(map);
    check_spaces(map);
}

void check_map(t_map *map)
{
    int i;

    i = 0;
    check_textures(map, &i);
    skp_line(map, &i);
    check_fc(map, &i);
    check_multiple(map);
    skp_line(map, &i);
    if (!map->line[i])
    {
		printf("Map doesn't exist!\n");
        free_all(map);
        exit(1);
    }
    check_valid_map(map, &i);
}
