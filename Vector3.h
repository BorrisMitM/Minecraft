#pragma once
#include <stdio.h>
#include <iostream>

using namespace std;

// ---------------------------------------------------------------------------------------------

class Vector3
{
public:
	float		x;
	float		y;
	float		z;

	Vector3();
	Vector3(float x, float y, float z);
	Vector3 operator + (Vector3 const& v);
	Vector3 operator - (Vector3 const& v);
	Vector3& operator += (Vector3 const& v);
	Vector3& operator -= (Vector3 const& v);
	Vector3 operator * (float const& v);

	Vector3 cross(const Vector3& v2);
	void Normalize();
	void Print();
};


