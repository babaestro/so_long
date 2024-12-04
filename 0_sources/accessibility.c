/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accessibility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:26:10 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/09/04 12:35:26 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_access_struct(t_access *ac)
{
	ac->i = 0;
	ac->start_x = -1;
	ac->start_y = -1;
	ac->c_c = 0;
	ac->c_a = 0;
	ac->exit_found = 0;
}

int	allocate_visited(t_access *ac, t_map *map)
{
	ac->v = malloc(sizeof(char *) * map->height);
	if (!ac->v)
		return (0);
	ac->i = 0;
	while (ac->i < map->height)
	{
		ac->v[ac->i] = malloc(sizeof(char) * map->width);
		if (!ac->v[ac->i])
		{
			while (ac->i-- > 0)
				free(ac->v[ac->i]);
			free(ac->v);
			return (0);
		}
		ac->i++;
	}
	return (1);
}

void	fill_access_data(t_access *ac, t_map *map)
{
	ac->i = 0;
	while (ac->i < map->height)
	{
		ac->j = 0;
		while (ac->j < map->width)
		{
			ac->v[ac->i][ac->j] = '0';
			if (map->mapfill[ac->i][ac->j] == 'P')
			{
				ac->start_x = ac->j;
				ac->start_y = ac->i;
			}
			else if (map->mapfill[ac->i][ac->j] == 'C')
				ac->c_c++;
			else if (map->mapfill[ac->i][ac->j] == 'E')
				ac->exit_found = 1;
			ac->j++;
		}
		ac->i++;
	}
}

int	initialize_access(t_access *ac, t_map *map)
{
	init_access_struct(ac);
	if (!allocate_visited(ac, map))
		return (0);
	fill_access_data(ac, map);
	return (1);
}

void	check_accessible_items(t_map *map, t_access *ac)
{
	ac->i = 0;
	while (ac->i < map->height)
	{
		ac->j = 0;
		while (ac->j < map->width)
		{
			if (map->mapfill[ac->i][ac->j] == 'C' && ac->v[ac->i][ac->j] == '1')
				ac->c_a++;
			if (map->mapfill[ac->i][ac->j] == 'E' && 
			((ac->i > 0 && 
			ac->v[ac->i - 1][ac->j] == '1') || 
			(ac->i < map->height - 1 && ac->v[ac->i + 1][ac->j] == '1') ||
			(ac->j > 0 && ac->v[ac->i][ac->j - 1] == '1') || 
			(ac->j < map->width - 1 && ac->v[ac->i][ac->j + 1] == '1')))
				ac->exit_found = 2;
			ac->j++;
		}
		ac->i++;
	}
}
