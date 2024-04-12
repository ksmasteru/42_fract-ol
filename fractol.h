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
  int num_points;
  int x_p[4];
  int y_p[4];
  int y_ptr;
  int x_ptr;
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
int color_pixel_julia(void *mlx_ptr, void * win_ptr, double x, double y ,int iteration);
int get_pixel_location(double x, int n);
int color_pixel_to_julia(void *mlx_ptr, void *win_ptr,double x , double y);
int mandelbrot(t_draw *data);
#endif