#pragma once
#include "../RegisterTypes.hpp"
#include "BasicMath.hpp"

namespace cvm
{
	namespace impl
	{
		template<int n>
		inline float VCALL extract( VECTOR a );

		template<int n>
		inline VECTOR VCALL insert( VECTOR a, float b );

#if CVM_SSE
		template<>
		inline float VCALL extract<0>( VECTOR a )
		{
			return _mm_cvtss_f32( a );
		}
		template<>
		inline VECTOR VCALL insert<0>( VECTOR a, float b )
		{
			return _mm_move_ss( a, _mm_set_ss( b ) );
		}

#if __SSE4_1__
		template<int n>
		inline float VCALL extract( VECTOR a )
		{
			static_assert( n >= 0 && n < 4, "Index out of range" );
			float res;
			_MM_EXTRACT_FLOAT( res, a, n );
			return res;
		}
		template<int n>
		inline VECTOR VCALL insert( VECTOR a, float b )
		{
			static_assert( n >= 0 && n < 4, "Index out of range" );
			__m128 i = _mm_set_ss( b );
			// https://msdn.microsoft.com/en-us/library/bb514071%28v=vs.120%29.aspx
			return _mm_insert_ps( a, i, n << 4 );
		}
#else // __SSE4_1__
		template<int n>
		inline float VCALL extract( VECTOR a )
		{
			static_assert( n >= 0 && n < 4, "Index out of range" );
			return _mm_cvtss_f32( permute<n, n, n, n>( a ) );
		}
		// Permute the vector, set the 1st component to the specified float, permute again
		template<int imm>
		inline VECTOR VCALL insertSse1( VECTOR a, float b )
		{
			a = permute<imm>( a );
			a = _mm_move_ss( a, _mm_set_ss( b ) );
			return permute<imm>( a );
		}
		template<>
		inline VECTOR VCALL insert<1>( VECTOR a, float b )
		{
			return insertSse1<_MM_SHUFFLE( 3, 2, 0, 1 )>( a, b );
		}
		template<>
		inline VECTOR VCALL insert<2>( VECTOR a, float b )
		{
			return insertSse1<_MM_SHUFFLE( 3, 0, 1, 2 )>( a, b );
		}
		template<>
		inline VECTOR VCALL insert<3>( VECTOR a, float b )
		{
			return insertSse1<_MM_SHUFFLE( 0, 2, 1, 3 )>( a, b );
		}
#endif // __SSE4_1__

#elif CVM_NEON
		template<int n>
		inline float VCALL extract( VECTOR a );
		{
			static_assert( n >= 0 && n < 4, "Index out of range" );
			return vgetq_lane_f32( a, n );
		}
		template<int n>
		inline VECTOR VCALL insert( VECTOR a, float b )
		{
			static_assert( n >= 0 && n < 4, "Index out of range" );
			return vsetq_lane_f32( b, a, n );
		}
#else
		static_assert( false, "Unknown target" );
#endif
	}
}