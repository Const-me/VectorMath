#pragma once
#include "VectorBase.hpp"
#include "Extract.hpp"

namespace cvm
{
	namespace impl
	{
		// Stuff that's common across all 3D vectors
		template<class tVector>
		class VectorBase4:
			public VectorBase<tVector, FLOAT4>
		{
		protected:
			typedef VectorBase4<tVector> tBase;

		public:
			VectorBase4() = default;

			VectorBase4( const tVector& that ) : VectorBase<tVector, FLOAT4>( that ) {}

			// Load float4
			VectorBase4( const FLOAT4& that ) : VectorBase<tVector, FLOAT4>( that ) {}

			VectorBase4( VECTOR that ) : VectorBase<tVector, FLOAT4>( that ) {}

			float getX() const { return extract<0>( m_vec ); }
			float getY() const { return extract<1>( m_vec ); }
			float getZ() const { return extract<2>( m_vec ); }
			float getW() const { return extract<3>( m_vec ); }

			void setX( float a ) { m_vec = insert<0>( m_vec, a ); }
			void setY( float a ) { m_vec = insert<1>( m_vec, a ); }
			void setZ( float a ) { m_vec = insert<2>( m_vec, a ); }
			void setW( float a ) { m_vec = insert<3>( m_vec, a ); }

			tVector normalize3() const
			{
				return normalize3( m_vec );
			}
			tVector normalize4() const
			{
				return normalize4( m_vec );
			}
		};
	}
}