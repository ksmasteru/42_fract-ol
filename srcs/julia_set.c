#include "../includes/fractol.h"

int render(t_image *img, int x, int y, int color)
{
    char    *pixel;
    pixel = img->addrs + img->size_line * y + x * ( img->bpp / 8);
    *(int *)pixel = color;
}

double scale(double input, double output_start, double output_end, double input_end)
{
    double scaled_value;
    double slope = 1.0 * (output_end - output_start) / (input_end);
    scaled_value = output_start + (slope * input);
    return (scaled_value);

}

int calculate_color_value(int x, int y, t_draw *data, t_complex z, t_complex c)
{
    int i;
    t_complex square_z;
    t_complex t;
    i = 0;

    z.real = data->x_min + ((data->x_max  - data->x_min) / (double)(WIDTH) * x);
    z.img =  data->y_max + ((data->y_min - data->y_max) / (double)HEIGHT * y);
    double a;
    double b;
    a = z.real * z.real;
    b = z.img * z.img;
    while ((a + b <= 4) && (i < 100))
    {
        square_z = z;
        z.real = a - b + c.real;
        z.img = 2 * square_z.real * square_z.img + c.img;
        a = z.real * z.real;
        b = z.img * z.img;
        i++;
    }
    return (i);
}

int julia_set(t_draw *data, int color)
{

    double x;
    double y;
    t_complex z;
    t_complex c;
    t_complex v;
    c.real = data->c_real;
    c.img = data->c_img;
    double magnitude;
    int i;
    y = 0;
    while (y <= HEIGHT)
    {
        x = 0;
        while (x <= WIDTH)
        {
            i = calculate_color_value(x, y , data, z , c);
            color = 0x00ff00 + ((0x000000 - 0x00ff00) / (double) 100 * i);
            render(&(data->img), x, y, color);
            x++;
        }
        y++;
    }
    return 0;
}