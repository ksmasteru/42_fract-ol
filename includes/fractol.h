/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 19:05:59 by darian            #+#    #+#             */
/*   Updated: 2024/04/24 22:31:31 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# define WIDTH 800
# define HEIGHT 800

typedef struct s_complex
{
	double		real;
	double		img;
}				t_complex;

typedef struct s_image
{
	void		*mlx_img;
	char		*addrs;
	int			bpp;
	int			size_line;
	int			endian;
}				t_image;

typedef struct s_draw
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_image		img;
	double		x_min;
	double		x_max;
	double		x_step;
	double		y_step;
	double		y_min;
	t_complex	c;
	t_complex	z;
	double		shift_side;
	double		shift_up;
	double		y_max;
	double		iter;
	int			is_julia;
	int			color_val;
	int			is_mandelbrot;
	int			is_burningship;
	int			ac;
	char		**av;
}				t_draw;

int				julia_set(t_draw *data, int color);
int				mouse_event(int button, int x, int y, t_draw *data);
int				close_win(t_draw *draw);
double			magn(t_complex a);
t_complex		power_2(t_complex a);
int				pressed_key_event(int keycode, t_draw *data);
t_complex		substraction(t_complex a, t_complex b);
t_complex		addition(t_complex a, t_complex b);
double			scale(double input, double output_start, double output_end,
					double input_end);
int				color_pixel_julia(t_draw *data, double x, double y,
					int iteration);
int				get_pixel_location(t_draw *data, double x, int n);
int				color_pixel_to_julia(t_draw *data, double x, double y);
int				mandelbrot(t_draw *data);
double			zoom_in(t_draw *data);
double			zoom_out(t_draw *data);
double			d_atoi(char *str);
double			get_af_point_val(char *str);
double			get_be_point_val(char **str, double *af_point_val);
double			get_atoi_sign(char **str);
void			handle_atoi_error(void);
int				atoi_get_sign(char **str);
long			ft_atoi(t_draw *data, char *str);
double			zoom_in_bonus(int x, int y, int button, t_draw *data);
int				zoom_out_bonus(int button, int x, int y, t_draw *data);
double			get_zoom_ratio(t_draw *data);
int				ft_create_img(t_draw *mlx_data);
int				ft_put_fractal(t_draw *mlx_data);
int				ft_events(t_draw *mlx_data);
int				calculate_color_value(int x, int y, t_draw *data);
void			shift_view(int keycode, t_draw *data);
void			shift_view_y(int keycode, t_draw *data);
void			handle_d_atoi_error(void);
double			get_x_min_ratio(double x);
double			get_x_max_ratio(double x);
double			get_y_max_ratio(double y);
double			get_y_min_ratio(double y);
int				burningship(t_draw *data);
void			handle_error(int error_code, t_draw *data);
int				color_value_burningship(t_draw *data);
void			handle_view_iteration(int keycode, t_draw *data);
int				ft_strcmp(char *s1, char *s2);
void			is_fractal(t_draw *data);
#endif