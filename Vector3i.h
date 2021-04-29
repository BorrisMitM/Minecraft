#pragma once
#include <stdio.h>
#include <iostream>

using namespace std;

// ---------------------------------------------------------------------------------------------

class Vector3i
{
public:
	int		x;
	int		y;
	int		z;

	Vector3i();
	Vector3i(int x, int y, int z);
	Vector3i operator + (Vector3i const& v);
	Vector3i operator - (Vector3i const& v);
	Vector3i& operator += (Vector3i const& v);
	Vector3i& operator -= (Vector3i const& v);
	Vector3i operator * (float const& v);

	void Print();
};


