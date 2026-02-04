/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:08:43 by nlaporte          #+#    #+#             */
/*   Updated: 2026/02/04 20:05:46 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <math.h>
#include <limits.h>
#include <float.h>

/**
 * @brief check_sphere_hit
 * 
 * Retourne la distance de l'intersection
 * la plus proche pour une sphere et un rayon
 * ou -1 si pas d'intersection
 *
 * Formule pour un point:
 *  P = origin + direction * distance
 *
 * Formule de la sphere
 *  R² = x² + y² + z²
 *
 * Intersection dun point dans une sphere
 * P = origin - sphere + direction * distance
 * 
 * @param t_ray ray
 * @param t_sphere object
 *
 * @return float
 */
float	check_sphere_hit(t_ray ray, t_sphere *object, float *t2)
{
	float	disc;
	t_ray_d	r;
	t_vec3	os;
	t_vec3	c;
	float	t1;

	ft_memset(&r, 0, sizeof(t_ray_d));
	os = (t_vec3){ray.origin.x - object->pos.x, ray.origin.y - object->pos.y, \
	ray.origin.z - object->pos.z};
	c.x = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y + ray.dir.z * ray.dir.z;
	c.y = 2. * (ray.dir.x * os.x + ray.dir.y * os.y + ray.dir.z * os.z);
	c.z = os.x * os.x + os.y * os.y + os.z * os.z - object->r * object->r;
	disc = c.y * c.y - 4. * c.x * c.z;
	if (disc < .0)
		return (-1);
	t1 = (-c.y - sqrtf(disc)) / (2. * c.x);
	*t2 = (-c.y + sqrtf(disc)) / (2. * c.x);
	if (t1 > 0.001)
		return (t1 * .99);
	return (-1);
}

void	manage_checkboard_sphere(t_vec3 uv, t_ray_d *r, t_sphere *s)
{
	long	x;
	long	y;
	int		tmp;

	tmp = s->r + 3;
	tmp = tmp << 3;
	if (s->checkboard_flag)
	{
		x = uv.x * tmp;
		y = uv.y * tmp;
		if ((x + y) % 2)
			r->color = (t_vec3){255, 255, 255};
		else
			r->color = (t_vec3){0, 0, 0};
		return ;
	}
}

/**
 * @brief manage_sphere_texture
 *
 * Chager la texture pour un sphere
 *
 * @param t_ray_d *r 
 * @param t_sphere *s 
 */
void	manage_sphere_texture(t_ray_d *r, t_sphere *s)
{
	t_vec3	uv;

	uv.z = 0;
	uv.x = .5 + atan2(r->n.z, r->n.x) / (2. * M_PI);
	uv.y = .5 - asin(r->n.y) / M_PI;
	if (s->checkboard_flag)
		return (manage_checkboard_sphere(uv, r, s));
	if (s->pal_flag)
	{
		s->color = vec_mul(s->pal(uv.x * uv.y * 4), 255);
		return ;
	}
	pthread_mutex_lock(&s->texture->text_mutex);
	r->reflection = s->texture->reflection;
	r->roughness = s->texture->rougness;
	if (isnan(uv.x) || isnan(uv.y))
		return (ft_memset (&uv, 0, sizeof(t_vec3)), (void) NULL);
	if (s->texture->buf)
		r->color = get_color_img(s->texture, s->texture->buf, uv);
	if (s->texture->buf_n)
		set_normal_from_map(r, s->texture, uv);
	pthread_mutex_unlock(&s->texture->text_mutex);
}

/**
 * @brief set_sphere_data
 *
 *	Charge les valeurs du rayon pour une sphere
 *
 * @param t_ray_d *r 
 * @param t_ray ray 
 * @param t_sphere *s 
 * @param float t[2] 
 */
void	set_sphere_data(t_ray_d *r, t_ray ray, t_sphere *s, float t[2])
{
	float	tmp;

	r->ray = ray;
	r->color = s->color;
	r->obj = s;
	r->reflection = .2;
	r->roughness = .8;
	r->t = t[0];
	r->hp = (t_vec3){ray.origin.x + ray.dir.x * r->t, \
		ray.origin.y + ray.dir.y * r->t, ray.origin.z + ray.dir.z * r->t};
	r->reflection = .24;
	r->roughness = .2;
	r->type = SPHERE;
	r->glass_flag = s->glass_flag;
	r->n = (t_vec3){r->hp.x - s->pos.x, r->hp.y - s->pos.y, \
	r->hp.z - s->pos.z};
	tmp = sqrtf(r->n.x * r->n.x + r->n.y * r->n.y + r->n.z * r->n.z);
	r->n.x /= tmp;
	r->n.y /= tmp;
	r->n.z /= tmp;
	if (s->texture || s->checkboard_flag || s->pal_flag)
		return (manage_sphere_texture(r, s));
}

/**
 * @brief check_all_sphere
 *
 * Verifie sil y a une intersection sur 
 * toutes les spheres
 *
 * @param t_ray ray
 * @param t_list *spheres
 *
 * @return t_ray_d
 */
t_ray_d	check_all_spheres(t_env *env, t_ray ray, t_sphere *last, int light)
{
	t_ray_d		r;
	t_sphere	*s;
	t_list		*spheres;
	float		t[2];

	ft_memset(&r, 0, sizeof(t_ray_d));
	spheres = env->scene.spheres;
	r.t = FLT_MAX;
	while (spheres)
	{
		s = spheres->content;
		if (s != last && !(light == 2 && s->glass_flag))
		{
			t[0] = check_sphere_hit(ray, s, &t[1]);
			if (t[0] < r.t && t[0] != -1)
			{
				set_sphere_data(&r, ray, s, t);
				r.t2 = t[1];
				if (light == 1 && s->glass_flag)
					r = render_glass_ray(env, r, (float [2]){.6, 1.6}, &t[1]);
			}
		}
		spheres = spheres->next;
	}
	return (r);
}
