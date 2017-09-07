#include <stdio.h>
#include "Include/Vector3.hpp"

using namespace cvm;

int main( int args, char* argv[] )
{
	// printf( "Hello, world.\n" );
	Vector3 a{ 1, 2, 3 };
	Vector3 b{ 4, 5, 6 };
	auto c = ( a + b ).store();
	printf( "%f, %f, %f\n", c.x, c.y, c.z );

	return 0;
}