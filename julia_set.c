#include "fractol.h"

int color_pixel_julia(t_draw *data, double x, double y ,int iteration)
{
    int color;
    double x_step = data->x_step;
    double y_step = data->y_step;
    int pixel_x;
    int pixel_y;
    if (iteration >= 0 && iteration <= 10)
        color = 0x000000;
    else if (iteration >= 10 && iteration <= 20)
        color = 0x404040;
    else if (iteration >= 20 && iteration <= 40)
        color = 0x808080;
    else if (iteration >= 60 && iteration <= 80)
        color = 0xbfbfbf;    
    else if (iteration >= 80 && iteration <= 100)
       color = 0xbfbfbf;
    pixel_x = get_pixel_location(data, x, 1);
    pixel_y = get_pixel_location(data, y, 2);
    //printf("pixels %d %d\n", pixel_x, pixel_y);
    mlx_pixel_put(data->mlx_ptr, data->win_ptr, pixel_x, pixel_y, color);
}

int get_pixel_location(t_draw *data, double x, int n)
{
    int location;
    double x_step = data->x_step;
    double y_step = data->y_step;
    if (n == 1)
    {
        if (x < 0)
            location = (x / x_step) + WIDTH / 2;
        else
            location = WIDTH / 2 + fabs(x / x_step);
    }   
    else
    {
        if (x > 0)
            location = (HEIGHT / 2) - fabs(x / x_step);
        else
            location = fabs(x / x_step) + (HEIGHT / 2);
    }
    return (location);
}
int color_pixel_to_julia(t_draw *data, double x , double y)
{
    double x_step = data->x_step;
    double y_step = data->y_step;
    int pixel_x;
    int pixel_y;
    int color;

    color = 0xffffff;
    pixel_x = get_pixel_location(data, x, 1);
    pixel_y = get_pixel_location(data, y, 2);
    //printf("pixel_x pixel_y %d %d\n",pixel_x, pixel_y);
    mlx_pixel_put(data->mlx_ptr, data->win_ptr, pixel_x, pixel_y, color);
}

int julia_set(t_draw *data, int color)
{

    double y = data->y_min;
    double x = data->x_min;
    t_complex z;
    t_complex c;
    t_complex v;
    if (data->ac != 3)
        return (0);
    c.real = double_atoi((data->av)[1]);
    c.img = double_atoi((data->av)[2]);
    double magnitude;
    int i;
    double y_step = data->y_step;
    double x_step = data->x_step;
    printf("x_step y_step x_min x_max y_min y_max %.9f %.9f %.9f %.9f %.9f %.9f\n",data->x_step,data->y_step,data->x_min, data->x_max, data->y_min, data->y_max);
    while (y <= data->y_max)
    {
        x = data->x_min;
        while (x <= data->x_max)
        {
            z.real = x;
            z.img = y;
            i = 0;
            while (i < 300)
            {
                z = power_2(z);
                z = addition(z, c);
                magnitude = magn(z);
                if (magnitude > 2)
                {
                    color_pixel_julia(data, x, y, i);
                    break;
                }
                i++;
            }
            if (i == 300)
                color_pixel_to_julia(data, x , y);
            x = x + x_step;
        }
        y = y + y_step;
    }
    return (0);
}