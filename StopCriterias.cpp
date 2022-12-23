#include "StopCriterias.h"

bool absValueDiffStop(vector<double> x0, double f0, vector<double> x1, double f1, double eps) { return abs(f0 - f1) < eps; }
bool absCoordDiffStop(vector<double> x0, double f0, vector<double> x1, double f1, double eps)
{
	vector<double> v = x0 - x1;
	return innerProduct(v, v) < pow(eps, 2);
}
bool relValueDiffStop(vector<double> x0, double f0, vector<double> x1, double f1, double eps) { return abs((f0 - f1) / f1) < eps; }
bool relCoordDiffStop(vector<double> x0, double f0, vector<double> x1, double f1, double eps)
{
	vector<double> v = x0 - x1;
	return innerProduct(v, v) / innerProduct(x1, x1) < pow(eps, 2);
}