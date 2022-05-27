#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double number();
double factor();
double expr();
double brackets();
double trans();
double stack[256] = { 0 };
int ss1, ss2, t;
double n;
int p = 0;

int main()
{
	char cc;
	int k;
	ss1 = 0;
	ss2 = 0;
	t = 0;
	printf("Введите систему счисления ввода: ");
	cc = getchar();
	k = 0;
	while (cc != '\n')
	{
			ss1 = ss1*10 + (cc - '0');
			k++;
			cc = getchar();
	}
	if (k == 0)
		ss1 = 10;
	//printf("%d", ss1);
	printf("Введите систему счисления вывода: ");
	cc = getchar();
	k = 0;
	while (cc != '\n')
	{
			ss2 = ss2*10 + (cc - '0');
			k++;
			cc = getchar();
	}
	if (k == 0)
		ss2 = 10;
//	printf("%d", ss2);
	printf("Введите точность представления результата: ");
	cc = getchar();
	k = 0;
	while (cc != '\n')
	{
			t = t*10 + (cc - '0');
			k++;
			cc = getchar();
	}
	if (k == 0)
		t = 6;
	//printf("%d", t)	;
	printf("Введите выражение: ");
	n = expr();
	if (ss2 != 10)
			trans();
	else
			printf("%.*f\n", t, n);
	return 0;
}

void push(double x)
{
    stack[p++] = x;
}

double pop()
{
    double a;
    a = stack[--p];
    return(a);
}

double trans()
{
		double l, h, j;
		int i, l1;
		if (n < 0)
    {
        printf("-");
         n *= (-1);
    }
		l = n;
		l1 = (int) n;
		// int через d, float и double через f
		while (l1>0)
		{
			j = l1%ss2;
			push(j);
			l1 = l1/ss2;
		}
		while (p != 0)  /*из стека*/
		{
				l1 = pop();
				if (l1 > 9)
						l1 += 55;
				else
						l1 += '0';
				printf("%c", (int)l1);
		}
		//если есть дробная часть
		if (t > 0)
		{
				n = l - (int)l;
        printf(".");
				i = 0;
				while (i < t)
				{
					n *= ss2;
					l = (int)n;
					h = l;
					if (h >= 10)
						h += 55;
					else
						h += '0';
					printf("%c", (int)h);
					i++;
					n -= l;
				}
		}
}

double number()
{
	double result = 0.0;
	double k;
	int sign = 1;
	char c;
	k = ss1;
	c = getchar();
	while (c == ' ')
		c = getchar();
	if (c == '-')
		sign = -1;
	else
		ungetc(c, stdin);
	while (1)
	{
		c = getchar();
		while (c == ' ')
			c = getchar();
		if (c >= '0' && c <= '9')
			result = result * ss1 + (c - '0');
		else if (c >= 'A' && c <= 'z')
			result = result * ss1 + (c - 55);
		else
		{
			ungetc(c, stdin);
			break;
		}
	}
		c = getchar();
	if (c == '.')
	{
		while (1)
		{
			c = getchar();
			if (c >= '0' && c <= '9')
			{
				result += (c - '0') / k;
				k *= ss1;
			}
			else if (c >= 'A' && c <= 'z')
			{
				result += (c - 55) / k;
				k *= ss1;
			}
			else
			{
				ungetc(c, stdin);
				break;
			}
		}
	}
	else
		ungetc(c, stdin);
	  return sign * result;
}

double factor()
{
	double result = brackets();
	double temp;
	char c;

	while (1)
	{
		c = getchar();
		while (c == ' ')
			c = getchar();
		switch (c)
		{
		case '*':
			result *= brackets();
			break;
		case '/':
			temp = brackets();
			result /= temp;
			break;
		default:
			ungetc(c, stdin);
			return result;
		}
	}
}

double expr()
{
	double result = factor();
	char c;

	while (1)
	{
		c = getchar();
		while (c == ' ')
			 c = getchar();
		switch (c)
		{
		case '+':
			result += factor();
			break;
		case '-':
			result -= factor();
			break;
		default:
			ungetc(c, stdin);
			return result;
		}
	}
}

double brackets()
{
	double result;
	int sign = 1;
	char c;
			c = getchar();
	while (c == ' ')
			c = getchar();
	if (c == '-')
	{
		sign = -1;
		c = getchar();
	}

	while (c == ' ')
		 c = getchar();
	if (c == '(')
	{
		result = sign * expr();
		c = getchar();
		return result;
	}
	else
	{
		ungetc(c, stdin);
		return sign * number();
	}
}
