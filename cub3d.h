/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meriem <meriem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:08:06 by meabdelk          #+#    #+#             */
/*   Updated: 2024/12/13 22:37:23 by meriem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
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
    int countlines;
    t_count *count;
    char *no_texture;
    char *so_texture;
    char *we_texture;
    char *ea_texture;
    int f_color;
    int c_color;
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
#endif
