/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 22:14:51 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/09/04 11:35:15 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_height(char *mapfile, t_map *map)
{
	char	*str;
	int		fd;

	map->height = 0;
	fd = open(mapfile, O_RDONLY);
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		map->height++;
		free(str);
		str = NULL;
	}
	free(str);
	map->mapfill = malloc(sizeof(char *) * (map->height + 1));
	map->mapfill[map->height] = NULL;
	close(fd);
}

void	map_width(char *mapfile, t_map *map)
{
	char	*str;
	int		fd;
	int		i;
	int		j;

	i = 0;
	fd = open(mapfile, O_RDONLY);
	while (i < map->height)
	{
		str = get_next_line(fd);
		map->mapfill[i] = malloc(ft_strlen(str) + 1);
		j = 0;
		while (str[j] && str[j] != '\n')
		{
			map->mapfill[i][j] = str[j];
			j++;
		}
		map->mapfill[i][j] = '\0';
		free(str);
		str = NULL;
		i++;
	}
	close(fd);
}

int	item_validity(t_map *map, char c, int i, int j)
{
	map->rich = 0;
	if (c != 'C' && c != 'P' && c != '1' && c != '0' && c != 'E')
	{
		ft_printf("Error\nInvalid map.\n");
		return (1);
	}
	if ((i == 0 || j == 0 || i == map->height - 1 || j == map->width) 
		&& (c != '1'))
	{
		ft_printf("Error\nInvalid map.\n");
		return (1);
	}
	if (c == 'C')
		map->burger++;
	if (c == 'P')
		map->krab++;
	if (c == 'E')
		map->poorf++;
	return (0);
}

void	map_validity(t_map *map, t_board *game)
{
	int		i;
	size_t	len;
	int		j;

	map->burger = 0;
	map->krab = 0;
	map->poorf = 0;
	len = ft_strlen(map->mapfill[0]);
	map->width = len;
	i = -1;
	while (++i < map->height)
	{
		if (ft_strlen(map->mapfill[i]) != len)
		{
			ft_printf("Error\nInvalid map.\n");
			free_game_map(game, map);
			exit(1);
		}
		j = -1;
		while (map->mapfill[i][++j])
		{
			if (item_validity(map, map->mapfill[i][j], i, j) == 1)
				free_game_map(game, map);
		}
	}
}

t_map	*set_map(char *mapfile, t_board *game)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->exit_open = 0;
	map_height(mapfile, map);
	map_width(mapfile, map);
	map_validity(map, game);
	if (map->burger == 0 || map->krab != 1 || map->poorf != 1)
	{
		ft_printf("Error\nInvalid map.\n");
		free_game_map(game, map);
		exit(1);
	}
	map->exit_x = -1;
	map->exit_y = -1;
	map->exit_open = 0;
	map->exit_reached = 0;
	if (!check_accessibility(map))
	{
		ft_printf("Error\nInvalid map: Some collectibles are not accessible.\n");
		free_game_map(game, map);
		exit(1);
	}
	return (map);
}
