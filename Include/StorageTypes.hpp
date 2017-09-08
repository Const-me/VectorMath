#pragma once

namespace cvm
{
	// A structure to hold a 3D vector
	struct FLOAT3
	{
		float x;
		float y;
		float z;
		FLOAT3() = default;
		FLOAT3( float _x, float _y, float _z ) : x( _x ), y( _y ), z( _z ) {}
		FLOAT3& operator= ( const FLOAT3& Float3 ) { x = Float3.x; y = Float3.y; z = Float3.z; return *this; }
	};

	// A structure to hold a 4D vector
	struct FLOAT4
	{
		float x;
		float y;
		float z;
		float w;

		FLOAT4() = default;
		FLOAT4( float _x, float _y, float _z, float _w ) : x( _x ), y( _y ), z( _z ), w( _w ) {}

		FLOAT4& operator= ( const FLOAT4& Float4 ) { x = Float4.x; y = Float4.y; z = Float4.z; w = Float4.w; return *this; }
	};

	// A structure to hold a pair of 3D vector
	struct FLOAT3x2
	{
		FLOAT3 a, b;
	};
}