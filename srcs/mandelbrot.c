#include "../includes/fractol.h"


int calculate_color_value_mandelbrot(t_draw *data)
{
    int i;
    t_complex square_z;
    t_complex z;
    double a;
    double b;

    i = 0;
    z = (t_complex){0, 0};
    a = data->c.real * data->c.real;
    b = data->c.img * data->c.img;
    while ((a + b <= 4) && (i < data->iter))
    {
        square_z = z;
        z.real = a - b  + data->c.real;
        z.img = 2 * square_z.real * square_z.img + data->c.img;
        a = z.real * z.real;
        b = z.img * z.img;
        i++;
    }
    return (i);
}
int mandelbrot(t_draw *data)
{

    t_complex z;
    int x;
    int y;
    char *pixel;
    int color;
    int i;
    int a;

    data->is_mandelbrot++;
    i = 0;
    while (i <= HEIGHT * WIDTH)
    {
        x = (i % WIDTH);
        y = (i / HEIGHT);
        data->c.img = data->y_max + ((data->y_min - data->y_max) / (double)HEIGHT * y);
        data->c.real = data->x_min + ((data->x_max  - data->x_min) / (double) WIDTH * x);
        a = calculate_color_value_mandelbrot(data);
        color = 0xff0000 + ((0x000000 - 0xff0000) / data->iter * a);
        pixel = data->img.addrs + data->img.size_line * y + x * (data->img.bpp / 8);
        *(int *)pixel = color;
        i++;
    }
    return 0;
}