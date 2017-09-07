#include <stdio.h>
#include "Include/Vector3.hpp"

using namespace cvm;

int main( int args, char* argv[] )
{
	Vector3 a{ 1, 2, 3 };
	Vector3 b{ 4, 5, 6 };
	Vector3 c = a + b;
	printf( "%f, %f, %f\n", c.getX(), c.getY(), c.getZ() );
	return 0;
}