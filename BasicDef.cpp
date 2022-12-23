#include "BasicDef.h"
void print(vector<double> x)
{
	for (double el : x) std::cout << el << " "; 
	std::cout << std::endl; 
}
double innerProduct(vector<double> x, vector<double> y)
{
	if (x.size() != y.size()) throw std::out_of_range("Wrong vector sizes in scalar product");
	double sp = 0;
	for (int i = 0; i < x.size(); ++i) sp += x[i] * y[i];
	return sp;
}

double distanceBetween(vector<double> x, vector<double> y)
{
	if (x.size() != y.size()) throw std::out_of_range("Wrong vector sizes in distance calculate");
	double dist = 0;
	for (int i = 0; i < x.size(); ++i) dist += (x[i] - y[i]) * (x[i] - y[i]);
	return dist;
}
