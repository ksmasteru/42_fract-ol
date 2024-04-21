/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 19:05:59 by darian            #+#    #+#             */
/*   Updated: 2024/04/20 09:55:43 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"
# include <X11/keysym.h>
# include "../libft/libft.h"
# include "../ft_printf/src/ft_printf_bonus.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
#define WIDTH 800
#define HEIGHT 800


typedef struct s_image
{
  void *mlx_img;
  char  *addrs;
  int   bpp;
  int size_line;
  int endian;
}t_image;

typedef struct s_draw{
  void *mlx_ptr;
  void *win_ptr;
  t_image img;
  double x_step;
  void  *old_img;
  double y_step;
  double x_min;
  double x_max;
  double y_min;
  double c_real;
  double shift_side;
  double shift_up;
  double c_img;
  double y_max;
  int is_julia;
  int is_mandelbrot;
  int ac;
  char **av;
}t_draw;

typedef struct s_complex{
    double real;
    double img;
}t_complex;
int julia_set(t_draw *data, int color);
int mouse_event(int button, int x, int y, t_draw *data);
int close_win(int keycode, t_draw *draw);
double magn(t_complex a);
t_complex power_2(t_complex a);
int pressed_key_event(int keycode, t_draw *data);
t_complex substraction(t_complex a, t_complex b);
t_complex addition(t_complex a, t_complex b);
double scale(double input, double output_start, double output_end, double input_end);
int color_pixel_julia(t_draw *data, double x, double y ,int iteration);
int get_pixel_location(t_draw *data, double x, int n);
int color_pixel_to_julia(t_draw *data ,double x , double y);
int mandelbrot(t_draw *data);
int zoom_in(t_draw *data, double zoom_ratio);
double  d_atoi(char *str);
int zoom_in_bonus(t_draw *data, int x, int y);
int zoom_out_bonus(t_draw *data, int x, int y);
double get_zoom_ratio(t_draw *data);
void ft_create_img(t_draw *mlx_data);
void ft_put_fractal(int ac, char **av, t_draw *mlx_data);
void ft_events(t_draw *mlx_data);
#endif