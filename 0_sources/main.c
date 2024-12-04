/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:39:44 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/09/02 14:31:53 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	so_long(char *mapfile)
{
	t_board	*game;

	game = malloc(sizeof(t_board));
	if (!game)
		exit(1);
	check_images(game);
	check_krab(game);
	check_mapfile(game, mapfile);
	game->map = set_map(mapfile, game);
	render_game(game);
	mlx_hook(game->win, 2, (1L << 0), direction, game);
	mlx_hook(game->win, 17, 0, game_over, game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	if (ac == 2)
		so_long(av[1]);
	else
	{
		ft_printf ("Error\nYou should enter ONE map as an argument\n");
		return (1);
	}
	return (0);
}
