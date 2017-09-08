#pragma once
#include "VectorBase.hpp"
#include "Extract.hpp"

namespace cvm
{
	namespace impl
	{
		// Stuff that's common across all 3D vectors
		template<class tVector>
		class VectorBase3: public VectorBase<tVector, FLOAT3>
		{
		protected:
			typedef VectorBase3<tVector> tBase;

		public:
			VectorBase3() = default;

			VectorBase3( const tVector& that ) : VectorBase<tVector, FLOAT3>( that ) {}

			// Load float3 from RAM, set W to 0
			VectorBase3( const FLOAT3& that ) : VectorBase<tVector, FLOAT3>( that ) {}

			VectorBase3( VECTOR that ) : VectorBase<tVector, FLOAT3>( that ) {}

			float getX() const { return extract<0>( m_vec ); }
			float getY() const { return extract<1>( m_vec ); }
			float getZ() const { return extract<2>( m_vec ); }

			void setX( float a ) { m_vec = insert<0>( m_vec, a ); }
			void setY( float a ) { m_vec = insert<1>( m_vec, a ); }
			void setZ( float a ) { m_vec = insert<2>( m_vec, a ); }

			tVector normalize() const
			{
				return normalize3( m_vec );
			}
			VECTOR VCALL lengthSquared() const
			{
				return dot3( m_vec, m_vec );
			}
			VECTOR VCALL length() const
			{
				return _mm_sqrt_ps( lengthSquared() );
			}
		};
	}
}