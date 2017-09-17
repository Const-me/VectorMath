#pragma once
#include "impl/BasicMath.hpp"
#include "impl/LoadStore.hpp"
#include "Vector2.hpp"

namespace cvm
{
	class Matrix2:
		public impl::VectorBase4<Vector4>
	{
	public:
		Matrix2() = default;

		Matrix2( const Vector4& that ) : tBase( that ) {}

		Matrix2( const FLOAT4& that ) : tBase( that ) {}

		Matrix2( VECTOR that ) : tBase( that ) {}

		Matrix2( float m00, float m01, float m10, float m11 ) : tBase( impl::set( m00, m01, m10, m11 ) ) { }

		static Matrix2 VCALL identity()
		{
			return Matrix2{ impl::set( 1, 0, 0, 1 ) };
		}
		static Matrix2 VCALL fromRows( VECTOR r1, VECTOR r2 )
		{
			return Matrix2{ _mm_shuffle_ps( r1, r2, _MM_SHUFFLE( 1,0,1,0 ) ) };
		}
		static Matrix2 VCALL fromColumns( VECTOR c1, VECTOR c2 )
		{
			return fromRows( c1, c2 ).transpose();
		}
		Matrix2 invert() const
		{
			// https://www.mathsisfun.com/algebra/matrix-inverse.html
			// However storage order is transposed, so this == [a, c, b, d]
			// http://www.mindcontrol.org/~hplus/graphics/matrix-layout.html

			const Vector2 dc = impl::permute<2, 3, 2, 3>( m_vec ); // [ d, b ]
			const Vector2 ad_bc = impl::vectorMul( m_vec, dc );	// [ a*d, c*b ]
			const VECTOR det = impl::vectorSub( ad_bc, impl::permute<1, 1, 1, 1>( ad_bc ) ); // determinant, in X
			VECTOR mul = _mm_div_ss( _mm_set1_ps( 1 ), det ); // 1.0 / determinant, in X
			mul = impl::permute<0, 0, 0, 0>( mul ); // 1.0 / determinant, in all
			mul = _mm_xor_ps( mul, impl::set( 0, -0.0f, -0.0f, 0 ) );	// 1.0 / determinant, with correct signs
			const VECTOR perm = impl::permute<0, 2, 1, 3>( m_vec ); // [ d, c, b, a ]
			return Matrix2{ impl::vectorMul( mul, perm ) };
		}
		Matrix2 transpose() const
		{
			return Matrix2{ impl::permute<3,1,2,0>( m_vec ) };
		}
		Vector2 operator*( Vector2& src ) const
		{
			const Vector2 x = impl::permute<0, 0, 0, 0>( src );
			const Vector2 y = impl::permute<1, 1, 1, 1>( src );
			const Vector2 row2 = impl::permute<3, 2, 3, 2>( m_vec );
			return x * Vector2{ m_vec } +y * row2;
		}
	};
}