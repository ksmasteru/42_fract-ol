#include "../includes/fractol.h"


double scale(double input, double output_start, double output_end, double input_end)
{
    double scaled_value;
    double slope = 1.0 * (output_end - output_start) / (input_end);
    scaled_value = output_start + (slope * input);
    return (scaled_value);
}

int calculate_color_value(int x, int y, t_draw *data)
{
    int i;
    t_complex square_z;
    t_complex z;
    double a;
    double b;

    i = -1;
    z.real = data->x_min + ((data->x_max  - data->x_min) / (double)(WIDTH) * x);
    z.img =  data->y_max + ((data->y_min - data->y_max) / (double)HEIGHT * y);
    a = z.real * z.real;
    b = z.img * z.img;
    while ((a + b <= 4) && (++i < data->iter))
    {
        square_z = z;
        z.real = a - b + data->c.real;
        z.img = 2 * square_z.real * square_z.img + data->c.img;
        a = z.real * z.real;
        b = z.img * z.img;
    }
    return (i);
}

int get_color_value(int x, int y, t_draw *data)
{
    int i;
    t_complex square_z;
    t_complex z;
    double a;
    double b;
    
    i = 0;
    z.real = data->x_min + ((data->x_max  - data->x_min) / (double)(WIDTH) * x);
    z.img =  data->y_max + ((data->y_min - data->y_max) / (double)HEIGHT * y);    
    a = z.real * z.real;
    b = z.img * z.img;
    while ((a + b <= 4) && (++i < data->iter))
    {
        square_z = z;
        z.real = 3;
    }
}
int julia_set(t_draw *data, int color)
{

    int x;
    int y;
    int i;
    char *pixel;
    int a;
    data->is_julia++;

    i = -1;
    while (++i <= HEIGHT * WIDTH)
    {
        x = (i % WIDTH);
        y = (i / WIDTH);
        a = calculate_color_value(x, y , data);
        color = 0xff0000 + ((0x000000 - 0xff0000) / data->iter * a);
        pixel = data->img.addrs + data->img.size_line * y + x * (data->img.bpp / 8);
        *(int *)pixel = color;
    }
    return 0;
}

