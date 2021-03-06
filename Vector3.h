#pragma once
#include <stdio.h>
#include <iostream>

using namespace std;

// Three dimensional vector of floats

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
	bool operator == (Vector3 const& v);

	Vector3 cross(const Vector3& v2);
	float dot(const Vector3& v2);
	float sqrdMagnitude(); // length of the vector to the power of 2
	void Normalize(); // normalizes the calling vector
	void Print();
};


