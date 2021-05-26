#pragma once

//simple easing class
//modifies a value t between 0 and 1 to a non linear output
class Easing
{
public:
	static float EaseIn(float t);
	static float EaseOut(float t);
private:
	Easing();
};

