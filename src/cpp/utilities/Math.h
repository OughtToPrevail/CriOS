#ifndef OSTEST_MATH_H
#define OSTEST_MATH_H


class Math
{
public:
	static int squared(int x);
	static unsigned int abs(int x);
	template<class T>
	static T max(T a, T b);

	static int ceil(double x);
};

template<class T>
T Math::max(T a, T b)
{
	return a > b ? a : b;
}

#endif //OSTEST_MATH_H
