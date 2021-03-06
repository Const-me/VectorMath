#pragma once
#include "../RegisterTypes.hpp"
#include "BasicMath.hpp"
#include "LoadStore.hpp"

namespace cvm
{
	namespace impl
	{
		// Stuff that's common across all vector types
		template<class tVector, class tStorage>
		class VectorBase
		{
		protected:
			VECTOR m_vec;

			VectorBase() = default;
			VectorBase( VECTOR vec ) : m_vec( vec ) { }
			// Construct by loading
			VectorBase( const tStorage& src ) : m_vec( load( src ) ) { }

			tVector& operator=( const tStorage& src )
			{
				m_vec = load( src );
				return *( tVector* )this;
			}

		public:
			// Basic math
			static tVector zero()
			{
				return tVector{ _mm_setzero_ps() };
			}

			tVector operator+( const tVector& that ) const
			{
				return vectorAdd( m_vec, that );
			}
			void operator+=( const tVector& that )
			{
				m_vec = vectorAdd( m_vec, that );
			}
			tVector operator-( const tVector& that ) const
			{
				return vectorSub( m_vec, that );
			}
			void operator-=( const tVector& that )
			{
				m_vec = vectorSub( m_vec, that );
			}
			tVector operator-() const
			{
				return vectorNeg( m_vec );
			}
			tVector operator*( const tVector& that ) const
			{
				return vectorMul( m_vec, that );
			}
			void operator*=( const tVector& that )
			{
				m_vec = vectorMul( m_vec, that );
			}


			// Store
			void VCALL store( tStorage& dest ) const
			{
				impl::store( m_vec, dest );
			}
			tStorage store() const
			{
				tStorage res;
				store( res );
				return res;
			}

			operator VECTOR() const { return m_vec; }
		};
	}
}