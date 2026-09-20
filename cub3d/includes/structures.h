/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 00:00:00 by souichou          #+#    #+#             */
/*   Updated: 2026/01/22 02:53:39 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

/*
** ============================================================================
** CONSTANTS & CONFIGURATION
** ============================================================================
*/

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define TEXTURE_SIZE 64
# define FOV 66
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03
# define COLLISION_BUFFER 0.2

/*
** MLX Key Codes 
*/
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

/*
** Map Characters
*/
# define CHAR_WALL '1'
# define CHAR_EMPTY '0'
# define CHAR_SPACE ' '
# define CHAR_NORTH 'N'
# define CHAR_SOUTH 'S'
# define CHAR_EAST 'E'
# define CHAR_WEST 'W'

/*
** Cardinal Directions (for texture selection)
*/
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

/*
** ============================================================================
** MLX & IMAGE STRUCTURES
** ============================================================================
*/

/*
** t_image - Image buffer structure for MLX
** Contains pointer to image data and metadata for pixel manipulation
*/
typedef struct s_image
{
	void		*img_ptr;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_image;

/*
** t_mlx - MLX context and window management
** Holds all MLX-related pointers and main image buffer
*/
typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_image		frame;
}				t_mlx;

/*
** ============================================================================
** TEXTURE & COLOR STRUCTURES
** ============================================================================
*/

/*
** t_textures - Wall texture data for each cardinal direction
** Each texture is loaded from XPM file specified in .cub config
*/
typedef struct s_textures
{
	t_image		north;
	t_image		south;
	t_image		east;
	t_image		west;
	char		*north_path;
	char		*south_path;
	char		*east_path;
	char		*west_path;
}				t_textures;

/*
** t_colors - Floor and ceiling RGB colors
** Converted to MLX integer format during initialization
*/
typedef struct s_colors
{
	int			floor_r;
	int			floor_g;
	int			floor_b;
	int			floor_color;
	int			floor_set;
	int			ceiling_r;
	int			ceiling_g;
	int			ceiling_b;
	int			ceiling_color;
	int			ceiling_set;
}				t_colors;

/*
** ============================================================================
** MAP STRUCTURES
** ============================================================================
*/

/*
** t_map - Game map data and dimensions
** Grid is stored as 2D char array, validated during parsing
*/
typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			player_found;
	char		player_dir;
	int			player_x;
	int			player_y;
}				t_map;

/*
** ============================================================================
** PLAYER STRUCTURES
** ============================================================================
*/

/*
** t_player - Player state and camera parameters
** Position uses floating point for smooth movement
** Direction and plane vectors define FOV and orientation
*/
typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		move_speed;
	double		rot_speed;
	int			move_forward;
	int			move_backward;
	int			move_left;
	int			move_right;
	int			rotate_left;
	int			rotate_right;
}				t_player;

/*
** ============================================================================
** RAYCASTING STRUCTURES
** ============================================================================
*/

/*
** t_ray - Single ray calculation data
** Contains all intermediate and final values for one vertical screen line
*/
typedef struct s_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
}				t_ray;

/*
** t_texture_draw - Texture sampling parameters for wall rendering
** Used during vertical line drawing to map texture to screen
*/
typedef struct s_texture_draw
{
	double		step;
	double		tex_pos;
}				t_texture_draw;

/*
** ============================================================================
** MAIN GAME STRUCTURE
** ============================================================================
*/

/*
** t_game - Master game state container
** Aggregates all subsystems and manages game loop
*/
typedef struct s_game
{
	t_mlx		mlx;
	t_player	player;
	t_map		map;
	t_textures	textures;
	t_colors	colors;
	int			config_parsed;
	int			initialized;
}				t_game;

#endif
