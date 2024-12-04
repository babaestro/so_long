/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 21:45:07 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/09/04 12:46:48 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free2d(char	**str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_game_map(t_board *game, t_map *map)
{
	int	i;

	i = 0;
	while (map->mapfill[i] != NULL)
	{
		free(map->mapfill[i]);
		i++;
	}
	free(map->mapfill);
	free(map);
	free(game);
	exit(1);
}

void	free_access(t_access *ac, int height)
{
	ac->i = 0;
	while (ac->i < height)
	{
		free(ac->v[ac->i]);
		ac->i++;
	}
	free(ac->v);
}

int	game_over(void *arg)
{
	t_board	*game;

	game = arg;
	mlx_destroy_image(game->mlx, game->character->character);
	free(game->character);
	mlx_destroy_image(game->mlx, game->sand);
	mlx_destroy_image(game->mlx, game->border);
	mlx_destroy_image(game->mlx, game->burger);
	mlx_destroy_image(game->mlx, game->poor);
	mlx_destroy_image(game->mlx, game->rich);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_game_map(game, game->map);
	if (game->poor)
		mlx_destroy_image(game->mlx, game->poor);
	return (1);
}
