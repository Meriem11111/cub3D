/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meabdelk <meabdelk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 11:06:40 by meabdelk          #+#    #+#             */
/*   Updated: 2025/01/20 16:40:42 by meabdelk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;
	size_t			res;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	res = 0;
	if (n == 0)
		return (0);
	while ((str1[i] == str2[i] && str1[i] != '\0') && i < n)
		i++;
	if (i == n)
		i--;
	res = str1[i] - str2[i];
	return (res);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			break ;
	}
	return (s1[i] - s2[i]);
}

int	ft_strchar(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != (char)c && s[i] != '\0')
		i++;
	if (s[i] == (char)c)
		return (1);
	return (0);
}


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

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*s;
	size_t			i;

	i = 0;
	s = (unsigned char *)str;
	while (i < n)
	{
		s[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
