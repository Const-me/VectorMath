#include <stdio.h>
#include <array>
#include "Include/Vector3.hpp"
#include "Include/Line.hpp"
#include "Include/Matrix2.hpp"

using namespace cvm;

template<class T>
void print( const char* lbl, const impl::VectorBase3<T>& v )
{
	printf( "%s = { %f, %f, %f }\n", lbl, v.getX(), v.getY(), v.getZ() );
}

void test1()
{
	Vector3 a{ 1, 2, 3 };
	Vector3 b{ 4, 5, 6 };
	print( "a", a );
	print( "b", b );
	print( "sum", a + b );

	Line l{ a, b };
	print( "tangent", l.tangent() );
	print( "moment", l.moment() );
}

template<class tVec>
Vector2 baricentric( const std::array<tVec, 3>& tri, Vector2 v2 )
{
	const Vector2 a = tri[ 1 ] - tri[ 0 ];
	const Vector2 b = tri[ 2 ] - tri[ 0 ];
	Matrix2 mat = Matrix2::fromColumns( a, b );
	// Matrix2 mat = Matrix2::fromRows( a, b );
	mat = mat.invert();
	mat = mat.transpose();
	v2 -= (VECTOR)tri[ 0 ];
	return mat * v2;
}

template<class tVec>
tVec fromBaricentric( const std::array<tVec, 3>& tri, Vector2 bc )
{
	return tri[ 0 ] +
		( tri[ 1 ] - tri[ 0 ] ) * impl::permute<0, 0, 0, 0>( bc ) +
		( tri[ 2 ] - tri[ 0 ] ) * impl::permute<1, 1, 1, 1>( bc );
};

void test2()
{
	// Matrix2 mat{ 4, 2, 7, 6 };
	// mat = mat.invert();
	const Vector3 t0{ 10, 10, 0 };
	const Vector3 t1{ 50, 0, 0 };
	const Vector3 t2{ 0, 60, 12 };

	const std::array<Vector3, 3> triangle{ t0, t1, t2 };

	const Vector2 vert{ 5, 6 };
	const Vector2 bc = baricentric( triangle, vert );
	const Vector3 res = fromBaricentric( triangle, bc );
	printf( "%f, %f, %f\n", res.getX(), res.getY(), res.getZ() );
}

int main( int args, char* argv[] )
{
	// test1();
	test2();
	return 0;
}