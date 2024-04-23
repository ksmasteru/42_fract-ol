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

double get_zoom_ratio(t_draw *data)
{
  double zoom_ratio;
  double x_min;
  double y_min;
  double x_max;
  double y_max;

  zoom_ratio = 0.7;
  x_min = data->x_min * zoom_ratio;
  y_min = data->y_min * zoom_ratio;
  x_max = data->x_max * zoom_ratio;
  y_max = data->y_max * zoom_ratio;
  double x_step = (x_max - x_min) / WIDTH;
  double y_step = (y_max - y_min) / HEIGHT;
  double value1 = x_max / x_step;
  double WIDTH1 = (double) WIDTH / 2; 
  while (value1 != WIDTH1)
  {
    x_min = data->x_min * zoom_ratio;
    y_min = data->y_min * zoom_ratio;
    x_max = data->x_max * zoom_ratio;
    y_max = data->y_max * zoom_ratio;
    x_step = (x_max - x_min) / WIDTH;
    y_step = (y_max - y_min) / HEIGHT;
    value1 = x_max * x_step;
    WIDTH1 = (double) WIDTH / 2;
    zoom_ratio += 0.01;
  }
  printf("zoom ratio is %f", zoom_ratio);
  return (zoom_ratio);
}
int zoom_in_bonus(t_draw *data, int x, int y)
{
  //mlx_clear_window(data->mlx_ptr, data->win_ptr);
  double x_min_ratio = get_x_min_ratio(data, x, y);
  double x_max_ratio = get_x_max_ratio(data, x, y);
  double y_min_ratio = get_y_min_ratio(data, x, y);
  double y_max_ratio = get_y_max_ratio(data, x, y);
  printf("x_min_ratio x_max_ratio y_min_ratio y_max_ration %f %f %f %f\n", x_min_ratio, x_max_ratio, y_min_ratio, y_max_ratio);
  data->y_min = (data->y_min) * 0.80 * y_min_ratio;
  data->x_min = (data->x_min) * 0.80 * x_min_ratio;
  data->x_max = (data->x_max) * 0.80 * x_max_ratio;
  data->y_max = (data->y_max) * 0.80 * y_max_ratio;
  data->x_step = ((data->x_max) - (data->x_min)) / WIDTH;
  data->y_step = ((data->y_max) - (data->y_min)) / HEIGHT;
  //julia_set(data, 0xffffff);
  //mandelbrot(data);
}
int zoom_out(t_draw *data, int x, int y)
{
  mlx_clear_window(data->mlx_ptr, data->win_ptr);
  data->y_min = (data->y_min) + (data->y_min) * 0.80;
  data->x_min = (data->x_min) + (data->x_min) * 0.80;
  data->x_max = (data->x_max) + (data->x_max) * 0.80;
  data->y_max = (data->y_max) + (data->y_max) * 0.80;
  data->x_step = ((data->x_max) - (data->x_min)) / WIDTH;
  data->y_step = ((data->y_max) - (data->y_min)) / HEIGHT;
  //julia_set(data, 0xffffff);
  mandelbrot(data);  
}
// Function to handle mouse events
void draw_triangle(t_draw *data, int color);
void draw_line(int x1, int y1, int x2, int y2, t_draw *data, int color);


int ft_strcmp(const char *s1, const char *s2)
{
  int i;

  i = 0;
  while (s1[i] && s1[i] == s2[i])
    i++;
  if (s2[i] == '\0' && s1[i] == '\0')
    return (0);
  return (i);
}

void ft_create_img (t_draw *data)
{
  /*image should be created each time the zoom happens*/
  // in this instance it was only created one time ;
  if (data->is_mandelbrot == 0 || data->is_julia == 0)
    data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "title");
  else
    mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
  data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
  data->img.addrs = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.size_line, &data->img.endian);
  /* calculate then put ? or pg(t_ut first*/
  //mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
}


void ft_put_fractal(int ac, char **av, t_draw *data)
{
  /*each fractal return the number i and color based*/

  data->x_max = 2;
  data->y_max = 2;
  data->x_min = -2;
  data->y_min = -2;
  data->shift_side = 0;
  data->shift_up = 0;
  data->ac = ac;
  data->av = av;
  data->iter = 100;
  if (data->is_julia == 0)
  {
    data->c = (t_complex){d_atoi(data->av[2]), d_atoi(data->av[2])};
    /* it still work what calls julia ?*/
    julia_set(data, 0x00000);
  }
  else if (data->is_mandelbrot == 0)
  {
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
    mlx_data.is_mandelbrot = -1;
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