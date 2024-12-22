/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meabdelk <meabdelk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:08:06 by meabdelk          #+#    #+#             */
/*   Updated: 2024/12/22 12:11:35 by meabdelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
#include <mlx.h>
# include <string.h>
# include <unistd.h>

typedef struct s_count
{
    int no_count;
    int so_count;
    int we_count;
    int ea_count;
    int f_count;
    int c_count;
    
}  t_count;

typedef struct s_map
{
    char **line;
    char **map_copy;
    int countlines;
    int x_p;
    int y_p;
    char *file_name;
    t_count *count;
    char *no_texture;
    char *so_texture;
    char *we_texture;
    char *ea_texture;
    int f_color[3];
    int c_color[3];
    int countlines_map;
    int s;
    int w;
    int e;
    int n;
    void *mlx;
    void *win;
} t_map;


int	ft_strcmp(char *s1, char *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_strchar(char *s, int c);
void free_all(t_map *map);
int check_path(const char *path);
void check_map(t_map *map);
void check_valid(char *line, char **path);
void free_text(char **texture);
char	**ft_split(char const *s, char c);
void ini(t_map *map);
int count_part(char **value);
void check_first_last(t_map *map, int *i);
int skp_spaces(char *line);
void check_map_borders(t_map *map, int *i);
void check_characters(t_map *map, int *i);
void ft_error(t_map *map);
void file_err(int i);
void check_spaces(t_map *map);
void free_map2(t_map *map);
char	*ft_strtrim(char const *s1, char const *set);
int	ft_atoi(const char *str);
int check_digit(char *value);
void	*ft_memset(void *str, int c, size_t n);
int count_comma(char *value);

#endif
