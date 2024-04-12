#include "fractol.h"
// Define window dimensions


void same_x_line(double x1, double y1, double x2, double y2, t_draw *data, int color)
{
  double y;
  double limit;
  y = y1;
  limit = y2;
  if (y1 > y2)
  {
   y = y2;
   limit = y1;
  }
  while (y <= limit)
  {
    mlx_pixel_put(data->mlx_ptr, data->win_ptr, x1 , y, 0x00ff00);
    y = y + 0.2;
  }
}

void same_y_line(double x1, double y1, double x2, double y2, t_draw *data, int color)
{
  double x;
  if (x1 > x2)
  {
    x = x2;
    x2 = x1;
    x1 = x;
  }
  while (x1 <= x2)
  {
    mlx_pixel_put(data->mlx_ptr, data->win_ptr, x1, y1, color);
    x1 = x1 + 0.2;
  }
}

void draw_rectangle(double x1, double y1, double x2 ,double y2, t_draw *data, int color);
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
  (data->x_p)[data->x_ptr] = x;
  (data->y_p)[data->y_ptr] = y;
  mlx_pixel_put(data->mlx_ptr, data->win_ptr,x, y, 0x00ff00);
  //draw_circle(data, x, y, 70, 0x00ff00);
  (data->x_ptr)++;
  (data->y_ptr)++;
  (data->num_points)++;
  if(data->num_points == 2)
    draw_rectangle((data->x_p)[0], (data->y_p)[0], (data->x_p)[1], (data->y_p)[1], data, 0x00ff00);
  if (data->num_points == 3)
  {
    draw_triangle(data, 0x00ff00);
    data->num_points = 0;
    data->x_ptr = 0;
    data->y_ptr = 0;
  }
  return (0);
}

// Function to draw a line between two points
void draw_line(int x1, int y1, int x2, int y2, t_draw *data, int color) {
   // handle points with same x. 
    double x;
    double y;
    double x_1;
    double y_1;
    double x_2;
    double y_2;
    double a;
    double b;
    double holder;
    x_1 = (double)x1;
    y_1 = (double)y1;
    x_2 = (double)x2;
    y_2 = (double)y2;
    if (x_1 == x_2)
      return same_x_line(x1, y1, x2, y2, data, color);
    if (y_1 == y_2)
      return same_y_line(x1, y1, x2, y2, data, color);
    a = (y_1 - y_2) / (x_1 - x_2);
    b = y_1 - (a * x1);
    if (x_1 > x_2)
    {
      x = x_2;
      holder = x_1;
    }
    else
    {
      x = x_1;
     holder = x_2;
    } 
    while (x <= holder)
    {
      y = (a * x) + b;
      mlx_pixel_put(data->mlx_ptr, data->win_ptr, x , y, 0x00ff00);
      x = x + 0.02;
    }
}

void draw_triangle(t_draw *data, int color)
{
  double x1 = (double)(data->x_p)[0];
  double y1 = (double)(data->y_p)[0];
  double x2 = (double)(data->x_p)[1];
  double y2 = (double)(data->y_p)[1];
  double x3 = (double)(data->x_p)[2];
  double y3 = (double)(data->y_p)[2];
  draw_line(x1, y1, x2, y2, data, color);
  draw_line(x1, y1, x3, y3, data, color);
  draw_line(x2, y2, x3, y3, data, color);
}
void draw_circle(t_draw *data, int x_center, int y_center, int radius, int color) {
    int x = radius;
    int y = 0;
    int radius_error = 1 - x;

    while (x >= y) {
        mlx_pixel_put(data->mlx_ptr,data->win_ptr, x + x_center, y + y_center, color);
        mlx_pixel_put(data->mlx_ptr,data->win_ptr,y + x_center, x + y_center, color);
        mlx_pixel_put(data->mlx_ptr,data->win_ptr,  -x + x_center, y + y_center, color);
        mlx_pixel_put(data->mlx_ptr,data->win_ptr, -y + x_center, x + y_center, color);
        mlx_pixel_put(data->mlx_ptr,data->win_ptr,  -x + x_center, -y + y_center, color);
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, -y + x_center, -x + y_center, color);
        mlx_pixel_put(data->mlx_ptr, data->win_ptr,x + x_center, -y + y_center, color);
        mlx_pixel_put(data->mlx_ptr,data->win_ptr,y + x_center, -x + y_center, color);
        
        y++;
        if (radius_error < 0)
            radius_error += 2 * y + 1;
        else {
            x--;
            radius_error += 2 * (y - x + 1);
        }
    }
}


// Function to draw a rectangle with top-left corner (x1, y1) and bottom-right corner (x2, y2)
void draw_rectangle(double x1, double y1, double x2 ,double y2, t_draw *data, int color) {
    // first get the two additional points location then draw 4 lines.
   double x3 = x2;
    double y3 = y1;
   double x4 = x1;
    double y4 = y2;
    for (int i = 0 ; i < 4 ; i++)
   {
      draw_line(x2, y2, x3, y3, data, color);
      draw_line(x1, y1, x4, y4, data, color);
      draw_line(x1, y1,  x3, y3, data, color);
      draw_line(x2, y2, x4, y4, data, color);
    }
}


int main() {
    // Initialize MiniLibX and create window
    t_draw mlx_data;
    mlx_data.num_points = 0;
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
