#include "AreasAndCovers.h"
std::mt19937 defaultGen(time(0));
std::uniform_real_distribution<> inSqrDist(-1, 1);

bool boxArea(vector<double> x, vector<double> center, vector<double> sidesSizes)
{
	for (size_t i = 0; i < sidesSizes.size(); ++i)
	{
		if (abs(x[i] - center[i]) > sidesSizes[i] / 2) return false;
	}
	return true;
}
bool ballArea(vector<double> x, vector<double> center, double radius) { return (innerProduct(x - center, x - center) < pow(radius, 2)); }

vector<double> coverBallBoxAreaRG(vector<double> center, vector<double> sidesSizes)
{
	vector<double> v(sidesSizes.size());
	for (size_t i = 0; i < sidesSizes.size(); ++i) 
	{
		v[i] = center[i] + inSqrDist(defaultGen) * sidesSizes[i] / 2;
	}
	return v;
}