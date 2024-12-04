/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 21:29:04 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/09/05 12:57:25 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_krab_position(t_board *game, int x, int y)
{
	int	new_x;
	int	new_y;

	new_x = x / 68;
	new_y = y / 68;
	game->map->mapfill[new_y][new_x] = 'P';
	game->map->mapfill[game->character->y / 68][game->character->x / 68] = '0';
	game->character->x = x;
	game->character->y = y;
	game->character->points++;
}

void	move_krab(t_board *game, int x, int y)
{
	int	new_x;
	int	new_y;

	new_x = x / 68;
	new_y = y / 68;
	if (game->map->rich)
		return ;
	if (game->map->mapfill[new_y][new_x] == '1')
		return ;
	if (game->map->mapfill[new_y][new_x] == 'E')
	{
		if (game->map->burger > 0)
			ft_printf("Eat all the burgers first!\n");
		else
			handle_exit(game, x, y);
		return ;
	}
	if (game->map->mapfill[new_y][new_x] == 'C')
	{
		game->map->burger--;
		if (game->map->burger == 0)
			game->map->exit_open = 1;
	}
	update_krab_position(game, x, y);
	ft_printf("\rYou have moved %d times", game->character->points);
}

int	direction(int keycode, void *parameter)
{
	t_board	*game;

	game = parameter;
	if (game->map->rich)
	{
		if (keycode == 65307)
			game_over(game);
		return (keycode);
	}
	mlx_clear_window(game->mlx, game->win);
	if (keycode == 65362)
		move_krab(game, game->character->x, game->character->y - 68);
	if (keycode == 65364)
		move_krab(game, game->character->x, game->character->y + 68);
	if (keycode == 65363)
		move_krab(game, game->character->x + 68, game->character->y);
	if (keycode == 65361)
		move_krab(game, game->character->x - 68, game->character->y);
	if (keycode == 65307)
		game_over(game);
	update_map_display(game);
	return (keycode);
}

void	handle_exit(t_board *game, int x, int y)
{
	game->map->rich = 1;
	game->character->points++;
	if (game->character->character)
	{
		mlx_destroy_image(game->mlx, game->character->character);
		game->character->character = NULL;
	}
	game->map->mapfill[game->character->y / 68][game->character->x / 68] = '0';
	game->character->x = x;
	game->character->y = y;
	if (game->poor)
	{
		mlx_destroy_image(game->mlx, game->poor);
		game->poor = NULL;
	}
	game->poor = mlx_xpm_file_to_image(game->mlx, 
			"./1_textures/win.xpm", &game->width, &game->height);
	game->character->character = mlx_xpm_file_to_image(game->mlx, 
			"./1_textures/KRAB.xpm", &game->width, &game->height);
	ft_printf("\rYou have moved %d times\nYOU WON!\n", game->character->points);
	if (game->map->exit_x != -1 && game->map->exit_y != -1)
		mlx_put_image_to_window(game->mlx, game->win, game->poor, 
			game->map->exit_x, game->map->exit_y);
}
int	check_accessibility(t_map *map)
{
	t_access	ac;

	if (!initialize_access(&ac, map))
		return (0);
	if (ac.start_x == -1 || ac.start_y == -1 || !ac.exit_found)
	{
		free_access(&ac, map->height);
		return (0);
	}
	flood_fill2(map, ac.start_x, ac.start_y, ac.v);
	check_accessible_items(map, &ac);
	free_access(&ac, map->height);
	return ((ac.c_a == ac.c_c) && (ac.exit_found == 2));
}