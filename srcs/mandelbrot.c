#include "../includes/fractol.h"



/*
 *
 * if (n < MAX_ITERATIONS && n > 0) {
    int i = n % 16;
    QColor mapping[16];
    mapping[0].setRgb(66, 30, 15);
    mapping[1].setRgb(25, 7, 26);
    mapping[2].setRgb(9, 1, 47);
    mapping[3].setRgb(4, 4, 73);
    mapping[4].setRgb(0, 7, 100);
    mapping[5].setRgb(12, 44, 138);
    mapping[6].setRgb(24, 82, 177);
    mapping[7].setRgb(57, 125, 209);
    mapping[8].setRgb(134, 181, 229);
    mapping[9].setRgb(211, 236, 248);
    mapping[10].setRgb(241, 233, 191);
    mapping[11].setRgb(248, 201, 95);
    mapping[12].setRgb(255, 170, 0);
    mapping[13].setRgb(204, 128, 0);
    mapping[14].setRgb(153, 87, 0);
    mapping[15].setRgb(106, 52, 3);
    return mapping[i];

    int set_colors[16] = {0x0421E0F, 0x19071A, 0x09012F, 0x040449, 0x000764, 0x0
else return Qt::black;
 */ 
int calculate_color_value_mandelbrot(t_draw *data)
{
    int i;
    t_complex temp_z;
    t_complex z;
    double a;
    double b;

    /*int colors[]= {0x421E0F, 0x19071A, 0x09012F, 0x040449, 0x000764, 0x0C2C8A, 0x1852B1, 0x397DD1, 0x86B5E5, 0xD3ECF8, 0xF1E9BF, 0xF8C95F, 0xFFAA00, 
    0xCC8000, 0x995700, 0x6A3403};*/
    i = -1;
    z = (t_complex){0, 0};
    a = z.real * z.real;
    b = z.img * z.img;
    while ((a + b <= 4) && (++i < data->iter))
    {
        temp_z = z;
        z.real = a - b  + data->c.real;
        z.img = 2 * temp_z.real * temp_z.img + data->c.img;
        a = z.real * z.real;
        b = z.img * z.img;
    }
    if (i == data->iter)
        return (0);
    //return (i + 1 - log(log(a + b) / log(4)));//
    //return (i + 1 - log(log4(a + b)));
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
    i = -1;
    while (++i <= HEIGHT * WIDTH)
    {
        x = (i % WIDTH);
        y = (i / HEIGHT);
        data->c.img = data->y_max + ((data->y_min - data->y_max) / (double)HEIGHT * y);
        data->c.real = data->x_min + ((data->x_max  - data->x_min) / (double) WIDTH * x);
        a = calculate_color_value_mandelbrot(data);
        //color = 0xff0000 + ((0x000000 - 0xff0000) / data->iter * a);
        pixel = data->img.addrs + data->img.size_line * y + x * (data->img.bpp / 8);
        *(int *)pixel = a * 0x10100525;
    }
    return 0;
}
