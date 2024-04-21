#include "../includes/fractol.h"

int mouse_event(int button, int x, int y, t_draw *data) {

  if (button == 2 || button == 1)
  {
    if (button == 2)
      zoom_in(data, 0.8);
    else
      zoom_in(data, 1.25);
    /*t_draw data_1;
    data_1.mlx_ptr = data->mlx_ptr;
    data_1.win_ptr = data->win_ptr;
    data_1.is_mandelbrot = data->is_mandelbrot;
    data_1.is_julia = data->is_julia ;
    data_1.x_max = data->x_max;
    data_1.x_min = data->x_min;
    data_1.x_step = data->x_step;
    data_1.y_step = data->y_step;
    data_1.y_min = data->y_min;
    data_1.y_max = data->y_max;
    data_1.av = data->av;
    data_1.ac = data->ac;*/
    /*data_1.old_img = data->img.mlx_img;*/
    if (data->is_julia  >= 0)
    {
        data->is_julia++;
        ft_create_img(data);
        julia_set(data, 0xffffff);
        mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
        //ft_put_fractal(data->ac, data->av, data);
    }
    else if (data->is_mandelbrot != -1)
    {
        data->is_mandelbrot++;
        //mandelbrot(data);
    }
  }  
    printf("button %d was clicked at postion %d %d\n", button, x, y);
  return (0);
}

int close_win(int keycode, t_draw *draw)
{
	exit(0);
	return (0);
}

int pressed_key_event(int keycode, t_draw *data)
{
  /*works but needs more optimization and be error prone*/
  if (keycode == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr); /* was this windos destroyed ?*/
		exit(0);
	}
  if (keycode == XK_Right || keycode == XK_Left)
  {
    // change the x limits. ?
    if (keycode == XK_Right) // increase x_max and redude x_min
    {
      if (data->x_max != 2 )
      {
        data->x_max += 0.2;
        data->x_min += 0.2;
        if (data->x_max > 2)
          data->x_max = 2;
      }
        //data->shift_side += 0.25;
      else
        return (0);
    }
    else // reduce x_max and increase x_min
    {
      if (data->x_min != -2)
      {
        data->x_min -= 0.2;
        data->x_max -= 0.2;
        if (data->x_min < -2)
          data->x_min = -2;
      }
      else
        return (0);
    }
  }
  if (keycode == XK_Up || keycode == XK_Down)
  {
    if (keycode == XK_Up) /*increase y_max and decrease y_min*/
    {
      if (data->y_max != 2)
      {
        data->y_max += 0.2;
        data->y_min += 0.2;
        if (data->y_max > 2)
          data->y_max = 2;
      }
      else
        return (0);
    }
    else
    {
      if (data->y_min != -2)
      {
        data->y_max -= 0.25;
        data->y_min -= 0.25;
        if (data->y_min < -2)/* an errorm ight happen here if x keeps descreaignm */
          data->y_min = -2;
      }
      else
        return (0);
    }
  }
  if (data->is_julia  >= 0) /*needs more optimization*/
  {
    data->is_julia++;
    ft_create_img(data);
    julia_set(data, 0xffffff);
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



