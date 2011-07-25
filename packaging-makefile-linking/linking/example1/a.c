#include "b.h"

int funcion_a(int x)
{
	if (x == 1) return 1;
	if (x % 2 == 0) return 1+funcion_b(x/2);
	else return 1+funcion_b(3*x+1);
}

