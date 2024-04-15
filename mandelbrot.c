#include "fractol.h"

int mandelbrot(t_draw *data)
{

    t_complex z;
    t_complex c;
    double x;
    double y;
    double x_step;
    double y_step;
    int i;
    double magnitude;
    x_step = data->x_step;
    y_step = data->y_step;
    x = data->x_min;
    y = data->y_min;
    i = 0;
    z.real = 0;
    z.img = 0;
    while(y <= data->y_max)
    {
        c.img = y;
        x = -2;
        while (x <= data->x_max)
        {
            c.real = x;
            i = 0;
            z.real = 0;
            z.img = 0;
            while(i < 200)
            {
                z = power_2(z);
                z = addition(z, c);
                magnitude = magn(z);
                if (magnitude > 2)
                    break;
                i++;
            }
            if ( i == 200)
                color_pixel_to_julia(data, x, y);
            x = x + x_step;
        }
        y = y + y_step;
    }
}