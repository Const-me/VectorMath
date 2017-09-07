#pragma once
#include "../RegisterTypes.hpp"
#include "BasicMath.hpp"

namespace cvm
{
	namespace impl
	{
		// Stuff that's common across all vector types
		template<class tVector>
		class VectorBase
		{
		protected:
			VECTOR m_vec;

		public:
			tVector operator+( const tVector& that ) const
			{
				return vectorAdd( m_vec, that.m_vec );
			}
			void operator+=( const tVector& that )
			{
				m_vec = vectorAdd( m_vec, that.m_vec );
			}
			tVector operator-( const tVector& that ) const
			{
				return vectorSub( m_vec, that.m_vec );
			}
			void operator-=( const tVector& that )
			{
				m_vec = vectorSub( m_vec, that.m_vec );
			}
			tVector operator-() const
			{
				return vectorNeg( m_vec );
			}
		};
	}
}