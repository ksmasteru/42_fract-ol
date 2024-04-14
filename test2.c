#include "fractol.h"

char *ft_itoa(int n);
void draw_circle(t_draw *data, int x_center, int y_center, int radius, int color);
int key_event(int button, t_draw *data)
{
  int x;
  int y;
  char *buffer;
  buffer = ft_itoa(button);
 /* this logic should be separated from draw line */ 
  x = data->x_p[(data->x_ptr) - 1];
  y = data->y_p[(data->y_ptr) - 1];
  mlx_string_put(data->mlx_ptr, data->win_ptr, x, y,0x00ff00, buffer);
  return (0);
}
// Function to handle mouse events
void draw_triangle(t_draw *data, int color);
void draw_line(int x1, int y1, int x2, int y2, t_draw *data, int color);
int mouse_event(int button, int x, int y, t_draw *data) {
  if (button == 2)
  {
    mlx_clear_window(data->mlx_ptr, data->win_ptr);
    //julia_set(data, 0x00ff00);
    mandelbrot(data);
  }
  if (button == 1)
  {
    mlx_clear_window(data->mlx_ptr, data->win_ptr);
    julia_set(data, 0x00ff00);
  }
  return (0);
}

int main(int ac, char **av) {
    // Initialize MiniLibX and create window
    t_draw mlx_data;
    mlx_data.num_points = 0;
    mlx_data.ac = ac;
    mlx_data.av = av;
    mlx_data.x_ptr = 0;
    mlx_data.y_ptr = 0;
    mlx_data.mlx_ptr = mlx_init();
    mlx_data.win_ptr = mlx_new_window(mlx_data.mlx_ptr, WIDTH, HEIGHT, "Simple Drawing Program");
    // Register mouse event handler
    mlx_mouse_hook(mlx_data.win_ptr, mouse_event, &mlx_data);
    mlx_key_hook(mlx_data.win_ptr, key_event, &mlx_data);
    // Main loop to handle events
    mlx_loop(mlx_data.mlx_ptr);
    return 0;
}