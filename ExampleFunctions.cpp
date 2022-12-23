#include "ExampleFunctions.h"
double f1(vector<double> x)
{
	return pow(x[0] - sqrt(2), 2) + pow(x[1] - sqrt(2), 2);
}
vector<double> gf1(vector<double> x)
{
	vector<double> vr(x.size());
    vr[0] = 2 * (x[0] - sqrt(2));
    vr[1] = 2 * (x[1] - sqrt(2));
	return vr;
}

double f2(vector<double> x)
{
	return pow(1-x[0],2) + 100*pow((x[1]-x[0]*x[0]),2);
}
vector<double> gf2(vector<double> x)
{
	vector<double> vr(x.size());
	vr[0] = -2*(1-x[0])-400*x[0]*(x[1]-x[0]*x[0]);
	vr[1] = 200 * (x[1] - x[0] * x[0]);
	return vr;
}

double f3(vector<double> x)
{
	return pow(x[0],4)+pow(x[1]-0.5,2)+pow(x[2]*x[3], 2) ;
}
vector<double> gf3(vector<double> x)
{
	vector<double> vr(x.size());
	vr[0] = 4*pow(x[0],3);
	vr[1] = 2*x[1]-1;
	vr[2] = 2 * x[2] * x[3] * x[3];
	vr[3] = 2 * x[3] * x[2] * x[2];
	return vr;
}

double f4(vector<double> x) { return exp(x[0]*x[1]-x[1])+pow(x[1]-2,2); }

vector<double> gf4(vector<double> x)
{
	vector<double> vr(x.size());
	vr[0] = x[1]*exp(x[0] * x[1] - x[1]);
	vr[1] = (x[0]-1)*exp(x[0] * x[1] - x[1])+2*(x[1]-2);
	return vr;
}
