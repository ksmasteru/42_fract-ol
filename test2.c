#include "fractol.h"
char *ft_itoa(int n);
void draw_circle(t_draw *data, int x_center, int y_center, int radius, int color);
int zoom_in(t_draw *data, int x, int y)
{
    mlx_clear_window(data->mlx_ptr, data->win_ptr);
  data->y_min = (data->y_min) * 0.80;
  data->x_min = (data->x_min) * 0.80;
  data->x_max = (data->x_max) * 0.80;
  data->y_max = (data->y_max) * 0.80;
  data->x_step = ((data->x_max) - (data->x_min)) / WIDTH;
  data->y_step = ((data->y_max) - (data->y_min)) / HEIGHT;
  julia_set(data, 0xffffff);
}

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

int zoom_in_bonus(t_draw *data, int x, int y)
{
  mlx_clear_window(data->mlx_ptr, data->win_ptr);
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
  julia_set(data, 0xffffff);
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
int mouse_event(int button, int x, int y, t_draw *data) {
  printf("button used is %d\n", button);
  if (button == 2)
  {
    mlx_clear_window(data->mlx_ptr, data->win_ptr);
    julia_set(data, 0x00ff00);
    //mandelbrot(data);
  }
  if (button == 1)
  {
    mlx_clear_window(data->mlx_ptr, data->win_ptr);
  }
  if (button == 4)
  {
    //zoom_in_bonus(data, x, y);
    zoom_in(data, x, y);
  }
  if (button == 5)
  {
    exit(0);
    zoom_out(data, x, y);
    //zoom_out_bonus(data, x, y);
  }
  return (0);
}

int main(int ac, char **av) {
    // Initialize MiniLibX and create window
    t_draw mlx_data;
    mlx_data.x_max = 2;
    mlx_data.y_max = 2;
    mlx_data.x_min = -2;
    mlx_data.y_min = -2;
    mlx_data.x_step = (mlx_data.x_max - mlx_data.x_min) / WIDTH;
    mlx_data.y_step = (mlx_data.y_max - mlx_data.y_min) / HEIGHT;
    mlx_data.ac = ac;
    mlx_data.av = av;
    mlx_data.mlx_ptr = mlx_init();
    mlx_data.win_ptr = mlx_new_window(mlx_data.mlx_ptr, WIDTH, HEIGHT, "Simple Drawing Program");
    // Register mouse event handler
    mlx_mouse_hook(mlx_data.win_ptr, mouse_event, &mlx_data);
    mlx_loop(mlx_data.mlx_ptr);
    return 0;
}