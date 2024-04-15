#ifndef FRACTOL_H
#define FRACTOL_H

#define WIDTH 800
#define HEIGHT 800
#include "mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>

typedef struct s_draw{
  void *mlx_ptr;
  void *win_ptr;
  double x_step;
  double y_step;
  double x_min;
  double x_max;
  double y_min;
  double y_max;
  int ac;
  char **av;
}t_draw;

typedef struct s_complex{
    double real;
    double img;
}t_complex;
int julia_set(t_draw *data, int color);
double magn(t_complex a);
t_complex power_2(t_complex a);
t_complex substraction(t_complex a, t_complex b);
t_complex addition(t_complex a, t_complex b);
double double_atoi(char *str);
int color_pixel_julia(t_draw *data, double x, double y ,int iteration);
int get_pixel_location(t_draw *data, double x, int n);
int color_pixel_to_julia(t_draw *data ,double x , double y);
int mandelbrot(t_draw *data);
int zoom_in(t_draw *data, int x, int y);
int zoom_in_bonus(t_draw *data, int x, int y);
int zoom_out_bonus(t_draw *data, int x, int y);

#endif