#include "../includes/fractol.h"
int mandelbrot(t_draw *data)
{

    t_complex z;
    t_complex c;
    double x;
    double y;
    int i;
    double magnitude;
    i = 0;
    z.real = 0;
    z.img = 0; 
    y = 0;
    if (data->is_mandelbrot == 0)
        data->win_ptr =  mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "MandelBrot");
    data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
    data->img.addrs = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.size_line, &data->img.endian);
    while(y <= HEIGHT)
    {
        c.img = scale(y, data->y_max, data->y_min, HEIGHT);
        x = 0;
        while (x <= WIDTH)
        {
            c.real = scale(x, data->x_min, data->x_max, WIDTH);
            i = 0;
            z.real = 0;
            z.img = 0;
            while(i < 100)
            {
                z = power_2(z);
                z = addition(z, c);
                magnitude = magn(z);
                if (magnitude > 2)
                    break;
                i++;
            }
            if (i == 100)
            {
                printf("hi");
                //color_pixel_to_julia(data, x, y);
            }
            x++;
        }
        y++;
    }
    mlx_mouse_hook(data->win_ptr, mouse_event, data);
    mlx_hook(data->win_ptr, 17, 0, close_win, data);
    mlx_key_hook(data->win_ptr, pressed_key_event, data);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
    mlx_loop(data->mlx_ptr);
    mlx_destroy_display(data->mlx_ptr);
    free(data->mlx_ptr);
    return 0;
}