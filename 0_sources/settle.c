/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 22:19:18 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/09/04 12:40:15 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fill_image(t_board *game, int w, int h)
{
	game->height = game->map->height * 68;
	game->width = game->map->width * 68;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->width, game->height, "so_long");
	game->sand = mlx_xpm_file_to_image(game->mlx, 
			"./1_textures/gsand.xpm", &w, &h);
	game->border = mlx_xpm_file_to_image(game->mlx, 
			"./1_textures/gborder.xpm", &w, &h);
	game->burger = mlx_xpm_file_to_image(game->mlx, 
			"./1_textures/Burger.xpm", &w, &h);
	game->poor = mlx_xpm_file_to_image(game->mlx, 
			"./1_textures/goal.xpm", &w, &h);
	game->rich = mlx_xpm_file_to_image(game->mlx, 
			"./1_textures/win.xpm", &w, &h);
	game->character = ft_calloc(1, sizeof(t_character));
	game->character->x = 0;
	game->character->y = 0;
	game->character->points = 0;
	game->character->character = mlx_xpm_file_to_image(game->mlx, 
			"./1_textures/KRAB.xpm", &w, &h);
}

void	fill_elements(t_board *game, char c, int x, int y)
{
	int	index_x;
	int	index_y;

	index_x = x / 68;
	index_y = y / 68;
	if (index_x < 0 || index_y < 0 || index_x >= game->map->width 
		|| index_y >= game->map->height)
	{
		ft_printf("Error: limits reached (%d, %d)\n", index_x, index_y);
		return ;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->sand, x, y);
	if (c == '1')
		mlx_put_image_to_window(game->mlx, game->win, game->border, x, y);
	else if (c == 'C')
		mlx_put_image_to_window(game->mlx, game->win, game->burger, x, y);
	else if (c == 'E')
		mlx_put_image_to_window(game->mlx, game->win, game->poor, x, y);
	else if (c == 'P')
	{
		game->character->x = x;
		game->character->y = y;
		mlx_put_image_to_window(game->mlx, game->win, 
			game->character->character, x, y);
	}
}

void	render_map(t_board *game)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	y = 0;
	while (game->map->mapfill[i])
	{
		j = 0;
		x = 0;
		while (game->map->mapfill[i][j])
		{
			fill_elements(game, game->map->mapfill[i][j], x, y);
			x = x + 68;
			j++;
		}
		y = y + 68;
		i++;
	}
}

void	render_game(t_board *game)
{
	int	w;
	int	h;

	w = 0;
	h = 0;
	fill_image(game, w, h);
	render_map(game);
}

void	update_map_display(t_board *game)
{
	int		x;
	int		y;
	char	element;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			element = game->map->mapfill[y][x];
			fill_elements(game, element, x * 68, y * 68);
			x++;
		}
		y++;
	}
	if (game->map->exit_open)
	{
		if (game->map->exit_x != -1 && game->map->exit_y != -1)
			mlx_put_image_to_window(game->mlx, game->win, game->poor, 
				game->map->exit_x, game->map->exit_y);
	}
}
