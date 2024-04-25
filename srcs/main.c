#include "../includes/fractol.h"

void draw_circle(t_draw *data, int x_center, int y_center, int radius, int color);
double get_x_min_ratio(t_draw *data, double x, double y)
{
  double x_min_ratio;

  if (x > WIDTH / 2)
    x_min_ratio = fabs(2 * x / WIDTH);
  else if( x < WIDTH / 2)
    x_min_ratio = fabs((2 * x / WIDTH));
  else
    x_min_ratio = 1;
  return (x_min_ratio);
}

double get_x_max_ratio(t_draw *data, double x, double y)
{
  double x_max_ratio;
  if (x > WIDTH / 2)
    x_max_ratio = fabs((WIDTH - x) / (WIDTH / 2));
  else if (x < WIDTH / 2)
    x_max_ratio = fabs(2 * (WIDTH -x) / (WIDTH));
  else
    x_max_ratio = 1;
  return (x_max_ratio);
}

double get_y_max_ratio(t_draw *data, double x, double y)
{
  double y_max_ratio;
  if (y < HEIGHT / 2)
    y_max_ratio = (HEIGHT - y) / (HEIGHT / 2);
  else if (y >  HEIGHT / 2)
    y_max_ratio = (HEIGHT - y) / (HEIGHT / 2);
  else
    y_max_ratio = 1;
  return (y_max_ratio);
}
double get_y_min_ratio(t_draw *data, double x, double y)
{
  double y_min_ratio;
  if (y < HEIGHT / 2)
    y_min_ratio = fabs((2 * y) / HEIGHT);
  else if (y > HEIGHT / 2)
    y_min_ratio = fabs((2 * y) / HEIGHT);
  else
    y_min_ratio = 1;
  return (y_min_ratio);
}


void ft_create_img (t_draw *data)
{
  char *title_mandelbrot = "Mandelbrot Fractal";
  char *title_julia = "Julia Fractal";
  char *title;
  title = title_mandelbrot;
  if (data->is_mandelbrot == 0 || data->is_julia == 0)
  {
    if (data->is_julia == 0)
      title = title_julia;
    data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, title);
  }
  else
    mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
  data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
  data->img.addrs = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.size_line, &data->img.endian);
}


void ft_put_fractal(int ac, char **av, t_draw *data)
{
  data->x_max = 2;
  data->y_max = 2;
  data->x_min = -2;
  data->y_min = -2;
  data->shift_side = 0;
  data->shift_up = 0;
  data->ac = ac;
  data->av = av;
  data->iter = 50;
  if (data->is_julia == 0)
  {
    data->c = (t_complex){d_atoi(data->av[2]), d_atoi(data->av[3])};
    /* it still work what calls julia ?*/
    julia_set(data, 0x00000);
  }
  else if (data->is_mandelbrot == 0)
  {
    data->x_max = 2;
    data->x_min = -2;
    data->y_max = 2;
    data->y_min = -2;
    mandelbrot(data);
  }
  mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
}

void ft_events(t_draw *data)
{
    /* when to use function pointer ? */
    mlx_mouse_hook(data->win_ptr, mouse_event, data);
    mlx_hook(data->win_ptr, 17, 0, close_win, data);
    mlx_key_hook(data->win_ptr, pressed_key_event, data);
}
int main(int ac, char **av) {
    t_draw mlx_data;
    mlx_data.is_julia = -1;
    mlx_data.scale = 0.9;
    mlx_data.is_mandelbrot = -1;
    mlx_data.shift_value_x = 0;
    mlx_data.shift_value_y = 0;
    if (ac == 2  || ac == 4)
    {
      if (ac == 4 &&  strcmp("julia", av[1]) == 0)
        mlx_data.is_julia = 0;
      else if (ac == 2 && strcmp("mandelbrot", av[1]) == 0)
        mlx_data.is_mandelbrot = 0;
    }
    if (mlx_data.is_mandelbrot == 0 || mlx_data.is_julia == 0)
    {
        mlx_data.mlx_ptr = mlx_init();
        ft_create_img(&mlx_data); /* each function shoulld fail error*/
        ft_put_fractal(ac, av, &mlx_data);
        ft_events(&mlx_data);
        mlx_loop(mlx_data.mlx_ptr); /* how does mlx_loop works ? will ft_)craete_img get created again ?*/
    }
    else
      printf("Availabe parameters : \njulia real_number imaginary_number.\nmandelbrot\nnewton\n");
    return (0);
}
