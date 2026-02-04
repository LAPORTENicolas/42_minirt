/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:01:01 by nlaporte          #+#    #+#             */
/*   Updated: 2026/02/04 20:45:27 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../lib/libft/libft.h"
# include <X11/Xlib.h>
# include <X11/extensions/XShm.h>
# include <pthread.h>

# define WIDTH 600
# define HEIGHT 600
# define MAX_THREAD 8
# define EPS 1e-4
# define ZOOM_STEP 0.5f
# define ZOOM_STEP 0.5f
# define ROT_SENS 0.1
# define TRANS_SENS 0.05
# define ROT_ANGLE 0.0872664625995
# define PHI 0.523598775597
# define INT_DIV2 429496731.
# define EXP_RENDER 0
# define FRAME_TARGET 100
# define SPECULAR_COEF .2
# define TWOP 6.28318530718
# define SCALE 4
# define BOUNCES 2

typedef enum s_selected_obj
{
	NO_OBJ,
	SPHERE_OBJ,
	PLANE_OBJ,
	CYLINDER_OBJ,
	CONE_OBJ,
	LIGHT_OBJ,
}	t_selected_obj;

typedef enum s_screen_mode
{
	CAMERA_MODE,
	EDIT_MODE
}	t_screen_mode;

typedef enum s_obj_type
{
	AMB_LIGHT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,
	TEXTURE
}	t_obj_type;

typedef enum s_key
{
	ESC_KEY = 65307,
	W_KEY = 119,
	A_KEY = 97,
	S_KEY = 115,
	D_KEY = 100,
	R_KEY = 114,
	M_KEY = 109,
	Z_KEY = 122,
	Q_KEY = 113,
	E_KEY = 101,
	C_KEY = 99,
	L_KEY = 108,
	P_KEY = 112,
	N_KEY = 110,
	O_KEY = 111,
	I_KEY = 105,
	UP_KEY = 65362,
	DOWN_KEY = 65364,
	RIGHT_KEY = 65363,
	LEFT_KEY = 65361
}	t_key;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_quat
{
	float	w;
	float	x;
	float	y;
	float	z;
}	t_quat;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	origin_loc;
	t_vec3	dir;
	t_vec3	dir_loc;
	float	mul;
	float	reflection;
	int		mirror;
}	t_ray;

typedef struct s_cylinder
{
	t_obj_type			type;
	t_vec3				pos;
	t_vec3				axis;
	t_quat				q;
	int					glass_flag;
	int					checkboard_flag;
	int					pal_flag;
	int					hit_type;
	float				r;
	float				height;
	t_vec3				color;
	t_vec3				x;
	t_vec3				y;
	t_vec3				top;
	t_vec3				bottom;
	struct s_texture	*texture;
	t_vec3				(*pal)(float);
}	t_cylinder;

typedef struct s_plane
{
	t_obj_type			type;
	int					glass_flag;
	int					checkboard_flag;
	int					pal_flag;
	t_vec3				pos;
	t_vec3				n;
	t_vec3				color;
	t_quat				q;
	struct s_texture	*texture;
	t_vec3				(*pal)(float);
}	t_plane;

typedef struct s_sphere
{
	t_obj_type			type;
	int					glass_flag;
	int					checkboard_flag;
	int					pal_flag;
	float				r;
	t_vec3				pos;
	t_vec3				color;
	t_quat				q;
	struct s_texture	*texture;
	t_vec3				(*pal)(float);
}	t_sphere;

typedef struct s_cone
{
	t_obj_type			type;
	int					glass_flag;
	int					checkboard_flag;
	int					pal_flag;
	int					hit_type;
	float				r;
	float				height;
	float				phi;
	float				k;
	t_vec3				pos;
	t_vec3				color;
	t_vec3				axis;
	t_quat				q;
	t_vec3				(*pal)(float);
	struct s_texture	*texture;
}	t_cone;

typedef struct s_light
{
	t_vec3	pos;
	t_vec3	color;
	float	brightness;
}	t_light;

typedef struct s_amb_light
{
	t_vec3	color;
	float	brightness;
}	t_amb_light;

typedef struct s_texture
{
	void	*mlx;
	void	*img;
	char	*buf;
	void	*img_n;
	char	*buf_n;
	char	*name;
	float	rougness;
	float	reflection;
	int		bpp;
	int		lb;
	int		endian;
	int		scale;
	int		w;
	int		h;
	pthread_mutex_t	text_mutex;
}	t_texture;

typedef struct s_ray_d
{
	t_ray		ray;
	float		t;
	float		t2;
	int			glass_flag;
	t_obj_type	type;
	t_vec3		hp;
	t_vec3		hp_loc;
	t_vec3		n;
	t_vec3		color;
	float		roughness;
	float		reflection;
	void		*obj;
}	t_ray_d;

typedef struct s_scene
{
	t_amb_light	amb_light;
	t_list		*spheres;
	t_list		*planes;
	t_list		*cylinders;
	t_list		*cones;
	t_list		*lights;
	t_list		*textures;
}	t_scene;

typedef struct s_win
{
	void	*win;
	void	*img;
	char	*buf;
	t_vec3	*img_buf;
	t_vec3	*img_buf_render;
	int		bpp;
	int		lb;
	int		endian;
	int		width;
	int		height;
	int		count;
	int		need_reset;
}	t_win;

typedef struct s_parsing
{
	int	amb_light_bool;
	int	cam_bool;
	int	light_bool;
	int	line;
	int	fd;
}	t_parsing;

typedef struct s_cam
{
	t_vec3	pos;
	t_vec3	forward;
	t_vec3	up;
	t_vec3	right;
	t_vec3	world_up;
	float	fov;
	float	yaw;
	float	pitch;
}	t_cam;

typedef struct s_task
{
	struct s_env	*env;
	pthread_t 		th_ray;
	int				start;
	int				end;
	int				*count;
	int				state;
} t_task;

typedef struct s_env
{
	void			*mlx;
	t_win			win;
	t_scene			scene;
	t_cam			camera;
	t_cam			origin;
	char			*file;
	int				z_key_pressed;
	int				screen_mode;
	int				mouse_x;
	int				mouse_y;
	int				mouse_left;
	int				mouse_right;
	int				size;
	int				reset;
	int				litle_resolution;
	int				threads_done;
	int				nb_threads;
	t_list			*light_to_move;
	t_light			*light_to_move2;
	void			*obj;
	t_selected_obj	selected_obj;
	t_sphere		*backup_sphere;
	t_plane			*backup_plane;
	t_cylinder		*backup_cylinder;
	t_cone			*backup_cone;
	t_task			*threads;
	pthread_mutex_t	done_mutex;
	pthread_cond_t	done_cond;
	pthread_mutex_t	reset_mutex;
	pthread_cond_t	reset_cond;
}	t_env;

typedef struct s_img
{
	XImage			*image;
	void			*pix;
	void			*gc;
	int				size_line;
	int				bpp;
	int				width;
	int				height;
	int				type;
	int				format;
	char			*data;
	XShmSegmentInfo	shm;
}				t_img;

// init.c
int			init_env(t_env *env, char *str);
int			init_tasks(t_env *env);

// window.c
int			init_win(t_env *env, int width, int height);
void		put_buffer_to_mlx(t_win *win, int render_amount);
void		put_pixel(t_env *env, t_vec3 color, int i);
void		put_pixel_in_render(t_env *env);
void		exit_mlx(t_env *env);

// free_utils.c
void		free_backup_obj(t_env *env);
void		free_lists(t_env *env);

// parsing.c
t_texture	*find_texture(t_env *env, char *s);
int			prepare_parsing(t_env *env, char *name);
int			create_amb_light(t_env *env, char **split, t_parsing *parsing);
int			create_camera(t_env *env, char **split, t_parsing *parsing);
int			create_light(t_env *env, char **split, t_parsing *parsing);
int			create_cylinder(t_env *env, char **split, int line);
int			create_sphere(t_env *env, char **split, int line);
int			create_plane(t_env *env, char **split, int line);
int			create_cone(t_env *env, char **split, int line);
int			create_texture(t_env *env, char **split, int line);
void		init_cylinder(t_cylinder *cyl, char **split);
void		init_cone(t_cone *cone, char **split);

// create_obj_texture.c
int			add_plane_texture(t_env *env, char **split, \
		t_plane *plane, int line);
int			add_sphere_texture(t_env *env, char **split, \
		t_sphere *sphere, int line);
int			add_cyl_texture(t_env *env, char **split, \
		t_cylinder *cyl, int line);
int			add_cone_texture(t_env *env, char **split, \
		t_cone *cone, int line);

// vector_parsing
int			parse_vector_int(char *s, t_vec3 *r, int line);
int			parse_vector_float(char *s, t_vec3 *r, float n[2], int line);

// render.c
void		render(t_env *env);
void		execute_thread(t_task *task);
void		execute_task(t_env *env);
void		put_screen_mode_info(t_env *env);

// threads.c
int			create_threads(t_task *threads, int nb_threads, int size);
void		join_threads(t_env *env);

// conversions.c
void		coordinate_from_index(t_env *env, int index, float *x, float *y);
void		coordinate_from_mouse(t_env *env, float *x, float *y);
float		calc_rad(float degree);

// keyboard.c
void		keyboard_hook(int key, t_env *env);
void		keyboard_release(int key, t_env *env);

// mouse_hooks.c
int			mouse_move(int x, int y, void *param);
int			mouse_hook(int button, int x, int y, void *param);
int			mouse_release(int button, int x, int y, void *param);

// mouse_utils.c
void		handle_camera_mouse(int button, t_env *env);
void		handle_edit_mouse(int button, t_env *env);

// vec_utils1.c
float		vec_length(t_vec3 v);
float		vec_length2(t_vec3 v);
float		vec_dot(t_vec3 a, t_vec3 b);
t_vec3		normalize(t_vec3 v);
t_vec3		vec_add(t_vec3 a, t_vec3 b);

// vec_utils2.c
t_vec3		vec_sub(t_vec3 a, t_vec3 b);
t_vec3		vec_mul(t_vec3 a, float t);
t_vec3		vec_mul_vec(t_vec3 a, t_vec3 b);
t_vec3		vec_cross(t_vec3 a, t_vec3 b);
t_vec3		vec_fmin(float max, t_vec3 a);

// quat_utils.c
t_quat		q_conj(t_quat q);
t_quat		q_mul(t_quat p, t_quat q);
t_quat		normalize_q(t_quat q);
t_quat		identity_q(void);
t_quat		quat_axis_angle(t_vec3 axis, float angle);
t_quat		quat_from_to(t_vec3 from, t_vec3 to);

// cylinder.c
t_ray_d		check_all_cylinders(t_env *env, t_ray ray, \
		t_cylinder *last, int light);

// cylinder_utils.c
void		set_cyl_data(t_ray_d *r, t_cylinder *cyl, float t);
float		cylinder_height(t_ray ray, t_cylinder *cyl, float t);
t_vec3		cylinder_normal_local(t_vec3 p_local, int hit_type);
void		cylinder_hp_n(t_cylinder *cyl, t_ray_d *r, float t);
float		cyl_t_world(t_cylinder *cyl, t_ray ray, t_vec3 *hp_loc, \
		float t);

// cylinder_texture.c
void		manage_cyl_texture(t_ray_d *r, t_cylinder *cyl);
void		cyl_checkboard_disk(t_ray_d *r, float radius);
void		cyl_checkboard_side(t_vec3 uv, t_ray_d *r);

// sphere.c
t_ray_d		check_all_spheres(t_env *env, t_ray ray, t_sphere *last, int light);
float		check_sphere_hit(t_ray ray, t_sphere *object, float *t2);
float		check_sphere_hit(t_ray ray, t_sphere *object, float *t2);

// plane.c
t_ray_d		check_all_planes(t_ray ray, t_list *planes, \
		t_plane *last, int light);
void		manage_texture_plane(t_vec3 uv, t_ray_d *r, t_plane *p);
// plane_utils.c
float		plane_t_world(t_plane *plane, t_ray ray, float t);

// cone.c 
t_ray_d		check_all_cones(t_env *env, t_ray ray, t_cone *last, int light);

// cone_utils.c 
void		calc_abc_cone(t_ray ray, float *val, float k);
float		cone_height(t_ray ray, t_cone *cone, float t);
float		cone_t_world(t_cone *cone, t_ray ray, float t);

// cone_data.c
void		set_cone_data(t_ray_d *r, t_cone *cone, float t);
t_vec3		cone_normal_local(t_cone *co, t_vec3 p_local);
void		cone_hp_n(t_cone *co, t_ray_d *closest, float t);

// cone_texture.c
void		manage_cone_texture(t_ray_d *r, t_cone *co);
void		cone_checkboard_side(t_vec3 uv, t_ray_d *r, t_cone *cone);
void		cone_checkboard_disk(t_ray_d *r, float radius);

// obj_utils.c
t_vec3		get_color_img(t_texture *t, char *buf, t_vec3 uv);
void		set_normal_from_map(t_ray_d *r, t_texture *texture, t_vec3 uv);

// obj_move.c
void		move_z_obj(t_env *env, int direction);
void		move_obj(int key, t_env *env, t_vec3 *objpos);
void		keyboard_move_object(int key, t_env *env);

// obj_resize.c
void		resize_object(t_env *env, int direction);

// obj_select.c
void		select_object(t_env *env);

// obj_rotate.c
t_vec3		quat_rotate_vec(t_quat q, t_vec3 v);
void		rotate_obj(int key, t_env *env);

// snapshot.c
void		snapshot_obj(t_env *env, void *obj);
void		copy_sphere(t_env *env, t_sphere *sphere);
void		copy_plane(t_env *env, t_plane *plane);	
void		copy_cylinder(t_env *env, t_cylinder *cylinder);

// restore_obj.c
void		restore_sphere(t_env *env, t_sphere *sphere);
void		restore_plane(t_env *env, t_plane *plane);
void		restore_cylinder(t_env *env, t_cylinder *cylinder);
void		restore_obj(t_env *env, void *obj);

// light.c
t_vec3		check_all_light(t_env *env, t_scene *scene, t_ray_d ray);
void		manage_light_pos(int key, t_env *env);
// texture.c
void		free_texture(void *p);

// cam_utils.c
void		define_worldup(t_vec3 *world_up, t_vec3 forward);
void		restore_origin_cam(t_env *env);
void		copy_origin_cam(t_env *env);

// cam_move.c
void		zoom_in(t_cam *camera);
void		zoom_out(t_cam *camera);
void		rotate_camera(t_cam *camera, int dx, int dy);
void		keyboard_move_camera(int key, t_env *env);

// build_pixels_utils.c
t_vec3		reflect(t_vec3 I, t_vec3 N, float rougness);
t_vec3		refract(t_vec3 I, t_vec3 N, float eta);
t_vec3		get_random_vec(float dispertion);
t_ray_d		get_pixel_color(t_env *env, t_ray ray, void *last);

// build_pixels.c
t_ray_d		check_all_objects(t_env *env, t_ray ray, void *last, int light);
t_vec3		reflect(t_vec3 I, t_vec3 N, float rougness);
t_ray_d		get_pixel_color(t_env *env, t_ray ray, void *last);
t_vec3		render_one_pixel(t_env *env, t_ray ray);

// generate_ray.c
t_ray		gen_world_ray(t_env *env, float x, float y);
void		gen_local_ray(t_ray *ray, t_quat object_q, t_vec3 object_pos);

// bmp_convert.c
int			make_screen_shoot(t_env *env);

// color_palette.c`
t_vec3		palette1(float t);
t_vec3		palette2(float t);
t_vec3		palette3(float t);
t_vec3		palette4(float t);
t_vec3		palette5(float t);

// glass.c
void		render_glass(t_env *env, t_ray_d *l_ray);
t_ray_d		render_glass_ray(t_env *env, t_ray_d l_ray, \
		float n[2], float *last_t);

#endif // minirt.h
