/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meriem <meriem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:18:10 by meriem            #+#    #+#             */
/*   Updated: 2024/12/14 01:01:33 by meriem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_check(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}
int	ft_strlen2(const char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*p;
	int		i;
	int		l;
	int		j;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	if (!s1[i])
		return (ft_strdup(""));
	while (ft_check(set, s1[i]))
		i++;
	l = ft_strlen2(s1);
	while (ft_check(set, s1[l - 1]))
		l--;
	p = (char *)malloc(l - i + 1);
	if (!p)
		return (0);
	j = 0;
	while (i < l)
		p[j++] = s1[i++];
	p[j] = '\0';
	return (p);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

int check_digit(char *value)
{
    int i;

    i = 0;
    while(value[i])
    {
        if(value[i] >= '0' && value[i] <= '9')
            i++;
        else
            return(1);
    }
    return(0);
}

int check_range(int range)
{
    printf("range %d\n", range);
    if(range < 0 || range > 255)
    {
        printf("error ! invalid color range \n");
        
        return(1);
    }
    return(0);
}

char **check_format_color(char *line)
{
    char **value;
    
    value = ft_split(line, ' ');
    if(!value || count_part(value) != 2)
    {
        printf("Error! invalid format\n");
        free_text(value);
        exit(1);
    }
    value = ft_split(value[1], ',');
    if(!value || count_part(value) != 3)
    {
        printf("Error! invalid color format \n");
        free_text(value);
        exit(1);
    }
    return(value);
}
void check_valid_color(char *line, int *color)
{
    char **value;
    int i;
    
    value = check_format_color(line);
    i = 0;
    while(i < 3)
    {
        value[i] = ft_strtrim(value[i], " \n");
        if(check_digit(value[i]) != 0)
        {
            printf("Error: Color values must be digits\n");
            free_text(value);
            exit(1);
        }
        *color = ft_atoi(value[i]);
        if(check_range(*color) != 0)
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

    value = ft_split(line, ' ');
    if(!value || count_part(value) != 2)
    {
        printf("Error ! invalid texture \n");
        free_text(value);
        exit(1);
    }
    *path = ft_strtrim(ft_strdup(value[1]), "\n");
   // printf("Trimmed path: '%s'\n", *path);  // Check the path after trimming.
    if(!*path)
    {
       free_text(value);
       exit(1);
    }
    free_text(value);
    if(check_path(*path) != 0)
    {
        exit(1);
    }
}

void f_c_check(t_map *map, int *i)
{
    if(ft_strncmp(map->line[*i], "F", 1) == 0 && (map->line[*i][1] == ' '))
    {
        check_valid_color(map->line[*i], &map->f_color);
        map->count->f_count++;
    }
    else if(ft_strncmp(map->line[*i], "C", 1) == 0 && (map->line[*i][1] == ' '))
    {
        check_valid_color(map->line[*i], &map->c_color);
        map->count->c_count++;
    }
}

void process_line(t_map *map, int *i)
{
    if(ft_strncmp(map->line[*i], "NO", 2) == 0 && (map->line[*i][2] == ' '))
    {
        check_valid(map->line[*i], &map->no_texture);
        map->count-> no_count++;
    }
    else if(ft_strncmp(map->line[*i], "SO", 2) == 0 && (map->line[*i][2] == ' '))
    {
        check_valid(map->line[*i], &map->so_texture);
        map->count->so_count++;
    }
    else if(ft_strncmp(map->line[*i], "WE", 2) == 0 && (map->line[*i][2] == ' '))
    {
        check_valid(map->line[*i], &map->we_texture);
        map->count->we_count++;
    }
    else if(ft_strncmp(map->line[*i], "EA", 2) == 0 && (map->line[*i][2] == ' '))
    {
        check_valid(map->line[*i], &map->ea_texture);
        map->count->ea_count++;
    }
    else if(ft_strncmp(map->line[*i], "F", 1) == 0 || ft_strncmp(map->line[*i], "C", 1) == 0)
        f_c_check(map, i);
    (*i)++;
}

void check_multiple(t_map *map)
{
    int i;

    i = 0;
    ini(map);
    while(map->line[i])
    {
        process_line( map, &i);
    }
    if(map->count->no_count != 1 || map->count->so_count != 1 || map->count->we_count != 1 
        || map->count->ea_count != 1 || map->count->f_count != 1 || map->count->c_count != 1)
    {
        printf("Error multiple textures !! \n");
        free(map->count);
        exit(1);
    }
}


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
        
       // printf(" --> line = %s\n", map->line[*i]);
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
    check_multiple(map);
    while (map->line[i] && ft_strchar(map->line[i], '\n') == 0)
    {
        i++;
    }
    //printf("after line = %s\n", map->line[i + 1]);
    // check_valid(map);
}
