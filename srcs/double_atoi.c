#include "../includes/fractol.h"

double d_atoi(char *str)
{
    int be_point_val;
    unsigned long af_point_val;
    int sign;
    double res;
    int i;
    unsigned long af_counter;

    af_counter = 1;
    i = 0;
    sign = 1;
    res = 0;
    be_point_val = 0;
    af_point_val = -1;
    while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)) /*value like .3 ?*/
        i++;
    if(str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
        {
            sign *= -1;
        }
        i++;
    }
    while ((str[i] >= '0' && str[i] <= '9') || str[i] == '.') /* , ?*/
    {
        if (str[i] == '.')
        {
            i++;
            af_point_val = 0;
            break;
        }
        be_point_val *= 10;
        be_point_val += str[i] - 48;
        i++;
    }
    while ((af_point_val != -1) && (str[i] >= '0' && str[i] <= '9'))
    {
        af_counter *= 10;
        af_point_val *= 10;
        af_point_val += str[i++] - 48;
    }
    if (str[i] != '\0')
    {
        printf("error\n");
        return (12345674); /* handle error*/
    }
    if (af_counter != 1)
        res = (double)af_point_val / af_counter; /* here swtich*/
    res += be_point_val;
    res *= sign;
    return (res);
}