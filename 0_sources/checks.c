/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 21:52:23 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/09/04 12:45:29 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_images(t_board *game)
{
	int	sand;
	int	border;
	int	burger;
	int	poorf;

	sand = open("./1_textures/gsand.xpm", O_RDWR);
	border = open("./1_textures/gborder.xpm", O_RDWR);
	burger = open("./1_textures/Burger.xpm", O_RDWR);
	poorf = open("./1_textures/KRAB.xpm", O_RDWR);
	check_krab(game);
	if (sand < 0 || border < 0 || burger < 0 || poorf < 0)
	{
		close(sand);
		close(border);
		close(burger);
		close(poorf);
		ft_printf("Error\nImage file(s) missing\n");
		free(game);
		exit(1);
	}
	close(sand);
	close(border);
	close(burger);
	close(poorf);
}

void	check_krab(t_board *game)
{
	int	krab;
	int	rich_krab;

	rich_krab = open("./1_textures/win.xpm", O_RDWR);
	krab = open("./1_textures/goal.xpm", O_RDWR);
	if (krab < 0 || rich_krab < 0)
	{
		close(krab);
		close(rich_krab);
		ft_printf("Error\nImage file(s) missing\n");
		free(game);
		exit(1);
	}
	close(krab);
	close(rich_krab);
}

void	check_empty_map(t_board *game, int fd)
{
	char	buff;

	if (read(fd, &buff, 1) == 0)
	{
		ft_printf("Error\nEmpty map.\n");
		free(game);
		exit(1);
	}
}

void	check_mapfile(t_board *game, char *map)
{
	int	len;
	int	fd;

	len = 0;
	while (map[len])
		len++;
	if (map[len - 4] != '.' || map[len - 3] != 'b' || map[len - 2] != 'e' 
		|| map[len - 1] != 'r')
	{
		ft_printf("Error\nNot .ber extension !\n");
		free(game);
		exit(1);
	}
	fd = open(map, O_RDWR);
	if (fd < 0)
	{
		ft_printf("Error\nMap is not opened !\n");
		free(game);
		exit(1);
	}
	check_empty_map(game, fd);
	close(fd);
}

void	flood_fill2(t_map *map, int x, int y, char **visited)
{
	if (x < 0 || y < 0 || x >= map->width 
		|| y >= map->height || visited[y][x] == '1' 
		|| map->mapfill[y][x] == '1' || map->mapfill[y][x] == 'E')
		return ;
	visited[y][x] = '1';
	flood_fill2(map, x + 1, y, visited);
	flood_fill2(map, x - 1, y, visited);
	flood_fill2(map, x, y + 1, visited);
	flood_fill2(map, x, y - 1, visited);
}
