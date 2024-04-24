#include "../includes/fractol.h"

void shift_view(int keycode, t_draw *data)
{
    double shift_value_x;
    double shift_value_y;
    double scale = zoom_in(data, 1);

    // shift_value_x = fabs(0.2 + (data->x_max * 0.25));
    // shift_value_y = fabs(0.2 + (data->y_max * 0.25));
    // the more i zoom the lesser the value gets
    
    shift_value_x = 0.20 * scale;
    shift_value_y = 0.20 * scale;
    printf("scale is %f\n", scale);
    if (keycode == XK_Right || keycode == XK_Up)
    {
        if (keycode == XK_Right)
        {
            data->x_max -= shift_value_x;
            data->x_min -= shift_value_x;

        }
        else
        {
            data->y_max -= shift_value_y;
            data->y_min -= shift_value_y;
        }
    }
    else if (keycode == XK_Down || keycode == XK_Left)
    {
        if (keycode == XK_Left)
        {
            data->x_max += shift_value_x;
            data->x_min += shift_value_x;
        }
        else
        {  
            data->y_max += shift_value_y;
            data->y_min += shift_value_y;
        }
    }
    printf("data->x_max %f data->x_min %f data->y_max %f data->y_min %f\n", data->x_max ,data->x_min, data->y_max, data->y_min);

}
