#include "LlnearOptimizeMethods.h"

std::pair<double, double> linearSearch(double &a, double &b, std::function <double(double)> f, std::function <double(double)> df, double eps)
{
	double optPoint = a, optValue = f(a);
	for (double i = a; i < b; i += eps)
	{
		double tempf = f(i + eps);
		if (tempf < optValue)
		{
			optPoint = i + eps;
			optValue = tempf;
		}
	}
	return std::make_pair(optPoint, optValue);
}

std::pair<double, double> ternarySearch(double &a, double &b, std::function<double(double)> f, std::function<double(double)> df, double eps)
{
	double optPoint = a, optValue = f(a);
	while(b-a>eps)
	{
		double midLeft = (2 * a + b) / 3, midRight = (a + 2 * b) / 3;
		if (f(midLeft) < f(midRight)) b = midRight;
		else a = midLeft;
	}
	if (f(a) < f(b)) return std::make_pair(a, f(a));
	else return std::make_pair(b, f(b));
	
}

std::pair<double, double> goldenSectionSearch(double &a, double &b, std::function<double(double)> f, std::function<double(double)> df, double eps)
{
	double temp = f(a + (b - a) / GOLDEN_RATIO); bool isLeft = 1;
	while (b - a > eps)
	{
		double midRight = a + (b - a) / GOLDEN_RATIO, midLeft = b - (b - a) / GOLDEN_RATIO;
		double fMidLeft, fMidRight;
		if (isLeft)
		{
			fMidLeft = temp;
			fMidRight = f(midRight);
		}
		else
		{
			fMidLeft = f(midLeft);
			fMidRight = temp;
		}
		if (f(midLeft) < f(midRight))
		{
			b = midRight;
			isLeft = 0;
			temp = fMidLeft;
		}
		else
		{
			a = midLeft;
			isLeft = 1;
			temp = fMidRight;
		}
	}
	if (f(a) < f(b)) return std::make_pair(a, f(a));
	else return std::make_pair(b, f(b));
}

std::pair<double, double> binarySearch(double &a, double &b, std::function<double(double)> f, std::function<double(double)> df, double eps)
{
	double mid = (a + b) / 2;
	if (df(mid) < 0) b = mid;
	else a = mid;
	if (f(a) < f(b)) return std::make_pair(a, f(a));
	else return std::make_pair(b, f(b));
}
