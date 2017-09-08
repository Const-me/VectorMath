#include <stdio.h>
#include "Include/Vector3.hpp"
#include "Include/Line.hpp"

using namespace cvm;

template<class T>
void print( const char* lbl, const impl::VectorBase3<T>& v )
{
	printf( "%s = { %f, %f, %f }\n", lbl, v.getX(), v.getY(), v.getZ() );
}

int main( int args, char* argv[] )
{
	Vector3 a{ 1, 2, 3 };
	Vector3 b{ 4, 5, 6 };
	print( "a", a );
	print( "b", b );
	print( "sum", a + b );

	Line l{ a, b };
	print( "tangent", l.tangent() );
	print( "moment", l.moment() );

	return 0;
}