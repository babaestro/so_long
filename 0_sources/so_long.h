/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:08:45 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/09/04 14:22:02 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h> 
# include <fcntl.h>
# include "libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

typedef struct s_character
{
	void	*character;
	int		x;
	int		y;
	int		points;
}	t_character;

typedef struct s_map
{
	char	**mapfill;
	int		height;
	int		width;
	int		krab;
	int		burger;
	int		poorf;
	int		poorfx;
	int		poorfy;
	int		rich;
	int		exit_open;
	int		exit_x;
	int		exit_y;
	int		exit_reached; 
}	t_map;

typedef struct s_board
{
	void		*win;
	void		*mlx;
	void		*sand;
	void		*border;
	void		*burger;
	void		*rich;
	void		*poor;
	int			height;
	int			width;
	t_map		*map;
	t_character	*character;
}	t_board;

typedef struct ac
{
	char	**v;
	int		i;
	int		j;
	int		start_x;
	int		start_y;
	int		c_c;
	int		c_a;
	int		exit_found;
}	t_access;

void	move_krab(t_board *game, int x, int y);
int		direction(int keycode, void *parameter);
void	so_long(char *mapfile);
int		main(int ac, char **av);
void	free_game_map(t_board *game, t_map *map);
void	free2d(char	**str);
int		game_over(void *arg);
void	check_images(t_board *game);
void	check_krab(t_board *game);
void	check_empty_map(t_board *game, int fd);
void	check_mapfile(t_board *game, char *map);
void	render_game(t_board *game);
void	render_map(t_board *game);
void	fill_elements(t_board *game, char c, int x, int y);
void	fill_image(t_board *game, int w, int h);
void	map_height(char *mapfile, t_map *map);
void	map_width(char *mapfile, t_map *map);
int		item_validity(t_map *map, char c, int i, int j);
void	map_validity(t_map *map, t_board *game);
t_map	*set_map(char *mapfile, t_board *game);
void	flood_fill2(t_map *map, int x, int y, char **visited);
void	fill_algo(char **ffill_map, int x, int y, int *reach);
char	**fill_map(t_map *map, int *x, int *y);
int		ft_strlen2d(char **str);
void	handle_exit(t_board *game, int x, int y);
void	update_map_display(t_board *game);
int		check_accessibility(t_map *map);
void	init_access_struct(t_access *access);
int		initialize_access(t_access *access, t_map *map);
void	free_access(t_access *access, int height);
void	check_accessible_items(t_map *map, t_access *access);
void	update_krab_position(t_board *game, int x, int y);

#endif