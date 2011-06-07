#include "a.h"

int funcion_b(int x)
{
	if (x == 1) return 1;
	if (x % 2 == 0) return 1+funcion_a(x/2);
	else return 1+funcion_a(3*x+1);
}

