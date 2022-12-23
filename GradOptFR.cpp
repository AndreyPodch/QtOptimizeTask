#include "GradOptFR.h"
std::pair<vector<double>, double> GradOptFR::optimize(vector<double> x0, inAreaCheck<vector<double>> inArea)
{
	numberOfIterations = 0;
	vector<double> p = -fDiff(x0); // Set start direction
	vector<double> x1 = x0;
	path.clear();
	path.push_back(x0);
	size_t curIter = 0;
	do
	{
		x0 = x1;
		// Optimize by direction
		lo.DerivativeOptimizatorInterface::setFunctionAndDifferential(
			[x0, this, p](double x)->double {return f(x0 + x * p); },
			[x0, this, p](double x)->double {return innerProduct(fDiff(x0 + x * p), -p); }
		);
		inAreaCheck<double> inSegment = [x0, inArea, this, p](double x)->bool {return inArea(x0 + x * p); };
		double alpha = lo.optimize(0,inSegment).first;
		x1 = x0 + alpha * p; // Get new point
		vector<double> nextGrad = fDiff(x1);
		// print(nextGrad);
		// print(p);
		//std::cout << innerProduct(nextGrad, nextGrad) << " " << innerProduct(p, p) << std::endl;
		double beta = innerProduct(nextGrad, nextGrad) / innerProduct(p, p);
		p = beta * p - fDiff(x0); // Calculate new direction
		//std::cout << x0[0] << " " << x0[1] << std::endl;
		//std::cout << fDiff(x0)[0] << " " << fDiff(x0)[1] << std::endl;
		/*std::cout << x1[0] << " " << x1[1] << std::endl;*/
		//std::cout << fDiff(x1)[0] << " " << fDiff(x1)[1] << std::endl;
		// print(x0);
		// print(x1);
		path.push_back(x1);
		if (curIter++ > maxIterations) break;
	} while (!Stop(x0,f(x0),x1,f(x1)));
	numberOfIterations = curIter;
	return std::make_pair(x1, f(x1));
}