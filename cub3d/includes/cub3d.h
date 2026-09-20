/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 00:00:00 by souichou          #+#    #+#             */
/*   Updated: 2026/01/22 00:00:00 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
** ============================================================================
** SYSTEM INCLUDES
** ============================================================================
*/

# include "mlx.h"
# include "structures.h"
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/*
** ============================================================================
** LOCAL INCLUDES
** ============================================================================
*/

# include "structures.h"

/*
** ============================================================================
** MATH CONSTANTS
** ============================================================================
*/

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

/*
** ============================================================================
** MAIN & INITIALIZATION (main.c)
** ============================================================================
*/

int		check_file_extension(char *filename);
int		validate_arguments(int ac, char **av);
int		setup_window(t_game *game);
int		init_mlx(t_game *game);

/*
** ============================================================================
** CLEANUP FUNCTIONS (cleanup.c, cleanup2.c)
** ============================================================================
*/

void	destroy_texture(t_mlx *mlx, t_image *img);
void	cleanup_textures(t_game *game);
void	cleanup_map(t_game *game);
void	free_textures_paths(t_game *game);
void	cleanup_mlx(t_game *game);
void	cleanup_game(t_game *game);
void	cleanup_and_exit(t_game *game, int exit_code);

/*
** ============================================================================
** EVENT HANDLERS (event_hooks.c)
** ============================================================================
*/

int		key_press_handler(int keycode, t_game *game);
int		key_release_handler(int keycode, t_game *game);
int		handle_close(t_game *game);
void	register_hooks(t_game *game);

/*
** ============================================================================
** GAME MANAGEMENT (game_management.c, game_management_utils.c)
** ============================================================================
*/

void	rotate_player(t_game *game, double angle);
int		move_player(t_game *game, double move_x, double move_y);
void	process_movement_input(t_game *game);
int		game_loop(t_game *game);
void	update_factor(double delta, int *sign);
int		check_wall_collision(t_game *game, double x, double y);
int		try_move_x(t_game *game, double move_x, double buffer);
int		try_move_y(t_game *game, double move_y, double buffer);

/*
** ============================================================================
** MOVEMENT FUNCTIONS (movement.c)
** ============================================================================
*/

void	handle_forward_movement(t_game *game);
void	handle_backward_movement(t_game *game);
void	handle_strafe_left(t_game *game);
void	handle_strafe_right(t_game *game);

/*
** ============================================================================
** INITIALIZATION (init_game.c, init_game_utils.c)
** ============================================================================
*/

int		load_texture(t_mlx *mlx, t_image *img, char *path);
int		load_all_textures(t_game *game);
int		init_player(t_game *game);
int		init_textures(t_game *game);
int		init_game_state(t_game *game);
void	set_player_direction(t_game *game, char dir);
void	calculate_plane_vector(t_game *game);
void	set_movement_speed(t_game *game);
int		rgb_to_mlx_color(int r, int g, int b);
void	init_colors(t_game *game);
int		validate_texture_size(t_image *img);

/*
** ============================================================================
** PARSING - CONFIG FILE (parse_elements.c)
** ============================================================================
*/

int		parse_element_line(char *line, t_game *game);
int		read_and_parse(int fd, t_game *game);
int		parse_config_file(char *filename, t_game *game);

/*
** ============================================================================
** PARSING - TEXTURES (parse_textures.c)
** ============================================================================
*/

int		parse_texture_north(char *line, t_game *game);
int		parse_texture_south(char *line, t_game *game);
int		parse_texture_west(char *line, t_game *game);
int		parse_texture_east(char *line, t_game *game);

/*
** ============================================================================
** PARSING - COLORS (parse_colors.c, parse_colors_utils.c)
** ============================================================================
*/

int		parse_rgb_values(char *line, int *r, int *g, int *b);
int		parse_floor_color(char *line, t_game *game);
int		parse_ceiling_color(char *line, t_game *game);
int		validate_color_range(int r, int g, int b);
int		parse_color_component(char *str, int *i, int *value);
int		expect_comma(char *str, int *i);

/*
** ============================================================================
** PARSING - MAP (parse_map.c, parse_map_utils.c)
** ============================================================================
*/

int		check_cell_enclosed(t_game *game, int x, int y);
int		check_map_enclosed(t_game *game);
int		find_player_position(t_game *game);
int		validate_map_characters(t_game *game);
int		validate_map(t_game *game);
int		is_valid_map_char(char c);
int		is_player_char(char c);
int		check_player_spawn(t_game *game);
int		is_walkable_char(char c);
int		finalize_map(t_game *game, char **map_lines, int map_count);

/*
** ============================================================================
** PARSING - UTILITIES (parse_utils.c)
** ============================================================================
*/

void	preprocess_line(char *line);
int		is_map_line(char *line);
void	free_map_lines(char **map_lines, int count);
int		validate_all_elements(t_game *game);
void	skip_whitespace(char *str, int *i);

/*
** ============================================================================
** RAYCASTING (raycast.c, raycast_utils.c)
** ============================================================================
*/

void	init_ray(t_ray *ray, t_game *game, int x);
void	calculate_delta_dist(t_ray *ray);
void	calculate_step_and_side_dist(t_ray *ray, t_game *game);
void	perform_dda(t_ray *ray, t_game *game);
void	calculate_wall_distance(t_ray *ray, t_game *game);
int		check_wall_hit(t_ray *ray, t_game *game);
void	calculate_line_height(t_ray *ray);
void	calculate_draw_limits(t_ray *ray);
int		determine_wall_face(t_ray *ray);
void	calculate_wall_x(t_ray *ray, t_game *game);

/*
** ============================================================================
** RENDERING (render.c)
** ============================================================================
*/

int		render_frame(t_game *game);
void	draw_wall_column(t_game *game, t_ray *ray, t_image *tex, int x);
void	render_floor_ceiling(t_game *game);

/*
** ============================================================================
** TEXTURES (textures.c, textures_utils.c)
** ============================================================================
*/

t_image	*select_texture(t_game *game, t_ray *ray);
int		calculate_texture_x(t_ray *ray, t_image *texture);
void	init_texture_draw(t_texture_draw *tex, t_ray *ray, t_image *img);
int		sample_texture(t_image *texture, int x, int y);
void	put_pixel_to_image(t_image *img, int x, int y, int color);
int		get_pixel_from_image(t_image *img, int x, int y);

/*
** ============================================================================
** UTILITIES (utils.c, utils2.c)
** ============================================================================
*/

int		print_error(char *message);
void	exit_with_error(t_game *game, char *message);
int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *str);
char	*ft_substr(char *str, int start, int len);
int		ft_atoi(const char *str);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_isdigit(int c);

/*
** ============================================================================
** GET NEXT LINE (gnl.c)
** ============================================================================
*/

char	*get_next_line(int fd);
void	drain_gnl(int fd);
char	*strndup_gnl(const char *s, int n);
void	copy_buffers_gnl(char *dst, char *src, ssize_t len);

#endif
