#include "fractol.h"

int color_pixel_julia(void *mlx_ptr, void * win_ptr, double x, double y ,int iteration)
{
    int color;
    double x_step = 0.005;
    double y_step = 0.005;
    int pixel_x;
    int pixel_y;
    if (iteration >= 0 && iteration <= 20)
        color = 0xf2f2f2;
    else if (iteration >= 20 && iteration <= 40)
        color = 0xe5e5e5;
    else if (iteration >= 60 && iteration <= 80)
        color = 0xbfbfbf;    
    else if (iteration >= 80 && iteration <= 100)
       color = 0x999999;
    pixel_x = get_pixel_location(x, 1);
    pixel_y = get_pixel_location(y, 1);
    printf("pixels %d %d\n", pixel_x, pixel_y);
    color = 0xffffff;
    mlx_pixel_put(mlx_ptr, win_ptr, pixel_x, pixel_y, color);
}

int get_pixel_location(double x, int n)
{
    int location;
    double x_step = 0.005;
    double y_step = 0.005;
    if (n == 1)
    {
        if (x < 0)
            location = (x / x_step) + 400;

        else

            location = 400 + fabs(x / x_step);
    }   
    else
    {
        if (x > 0)
            location = 400 - fabs(x / x_step);
        else
            location = fabs(x / x_step) + 400;
    }
    return (location);
}
int color_pixel_to_julia(void *mlx_ptr, void *win_ptr,double x , double y)
{
    double x_step = 0.005;
    double y_step = 0.005;
    int pixel_x;
    int pixel_y;
    int color;

    color = 0xffffff;
    pixel_x = get_pixel_location(x, 1);
    pixel_y = get_pixel_location(y, 2);
    mlx_pixel_put(mlx_ptr, win_ptr, pixel_x, pixel_y, color);
}

int julia_set(t_draw *data, int color)
{

    double y = -2;
    double x = -2;
    t_complex z;
    t_complex c;
    t_complex v;
    c.real = -0.4;
    c.img = 0.6;
    double magnitude;
    int i;
    double y_step = 0.005;
    double x_step = 0.005;
    while (y < 2)
    {
        x = -2;
        while (x < 2)
        {
            z.real = x;
            z.img = y;
            i = 0;
            while (i < 100)
            {
                z = power_2(z);
                z = addition(z, c);
                magnitude = magn(z);
                if (magnitude > 2)
                    break;
                i++;
            }
            if (i == 100)
                color_pixel_to_julia(data->mlx_ptr, data->win_ptr, x , y);
            x = x + x_step;
        }
        y = y + y_step;
    }
    return (0);
}