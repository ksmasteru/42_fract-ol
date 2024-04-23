#include "../includes/fractol.h"

int mouse_event(int button, int x, int y, t_draw *data) {

  if (button == 2 || button == 1)
  {
    if (button == 2)
      zoom_in(data, 0.8);
    else
      zoom_in(data, 1.25);
    if (data->is_julia  >= 0) /*this mf*/
    {
        ft_create_img(data);
        julia_set(data, 0xffffff);
        mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
    }
    else if (data->is_mandelbrot >= 0)
    {
        ft_create_img(data);
        mandelbrot(data);
        mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
    }
  }  
  return (0);
}

int close_win(int keycode, t_draw *draw)
{
	exit(0);
	return (0);
}

int pressed_key_event(int keycode, t_draw *data)
{
  double zoom_value;
  // works but needs more optimization and be error prone
  if (keycode == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr); /* was this windos destroyed ?*/
		exit(0);
	}
  if (keycode == XK_Right || keycode == XK_Left)
  {
    // change the x limi
    zoom_value = data->x_max * 0.25;    
    if (keycode == XK_Right) // increase x_max and redude x_min
    {
      data->x_max += zoom_value;
      data->x_min += zoom_value;
      //printf("data x_max is %.6f and data->x_min is %.6f\n", data->x_max, data->x_min);
    }
    else // reduce x_max and increase x_min
    {
      data->x_max -= zoom_value;
      data->x_min -= zoom_value;
      //printf("data x_max is %.6f and data->x_min is %.6f\n", data->x_max, data->x_min);
    }
  }
  else if (keycode == XK_Up || keycode == XK_Down)
  {
    zoom_value = data->y_max * 0.25;
    if (keycode == XK_Up) /*increase y_max and decrease y_min*/
    {
      data->y_max += zoom_value;
      data->y_min += zoom_value;
    }
      else
    {  
      data->y_max -= zoom_value;
      data->y_min -= zoom_value;
    }
  }
  if (keycode == XK_1)
    data->iter += 50;
  if (keycode == XK_2)
  {
    if (data->iter < 50)
      data->iter -= 50;
  }
  if (data->is_julia  >= 0 || data->is_mandelbrot >= 0) 
  {
    ft_create_img(data);
    if (data->is_julia >= 0)
      julia_set(data, 0xffffff);
    else
      mandelbrot(data);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
  }
	return (0);
}

int zoom_in(t_draw *data, double zoom_ratio)
{
  /*should protect bounds? mixming arrow and zoom might cause crash*/
  data->y_min = (data->y_min) * zoom_ratio;
  data->x_min = (data->x_min) * zoom_ratio;
  data->x_max = (data->x_max) * zoom_ratio;
  data->y_max = (data->y_max) * zoom_ratio;
}



