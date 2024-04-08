#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int nub_len(int n)
{
	int i;

	i = 0;
	if (n <= 0) /*handles the 0 case */
	{
		n *= -1;
		i++;
	}
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char *ft_itoa(int n)
{
	/* n = -12345 */
	char *res;
	int i;
	int lent;
	int sign;
	
	i = 0;
	lent = nub_len(n);
	res = (char*)malloc(sizeof(char) * (lent + 1));
	if (!res)
		return (NULL);
	if (n < 0)
	{
		res[0] = '-';
		n *= -1;
	}
	res[lent + 1] = '\0';
	if (n == 0)
		res[0] = 48;
	/* Star from the end */
	i = lent;
	while (n > 0) /* TEST */
	{
		res[i] = (n % 10) + 48;
		n /= 10;
		i--;
	}
	return (res);
}
/*
int main()
{
	char *a = ft_itoa(-123004);
	char *b = ft_itoa(-0);
	char *c = ft_itoa(+1233);
	printf("-123004 -0 +1233 %s %s %s", a, b, c);
}*/
