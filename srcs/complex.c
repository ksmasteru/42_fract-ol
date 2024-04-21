#include "../includes/fractol.h"

t_complex addition(t_complex a, t_complex b)
{
    t_complex result;
    result.real = a.real + b.real;
    result.img = a.img + b.img;
    return result;
}

t_complex substraction(t_complex a, t_complex b)
{
    t_complex result;
    result.real = a.real - b.real;
    result.img = a.img - b.img;
    return result;
}

t_complex power_2(t_complex a)
{
    t_complex result;
    // result = pow(real, 2) - pow(img, 2) + 2 * real * img
    result.real = pow(a.real, 2) - pow(a.img, 2);
    result.img = 2 * a.real * a.img;
    return (result);
}
double magn(t_complex a)
{
    double result;
    double before_res = pow(a.real, 2) + pow(a.img, 2);
    result = sqrt(pow(a.real, 2) + pow(a.img, 2));
    return (result);
}