#include "BasicDef.h"
#include "LinearOptimizator.h"
#include "LlnearOptimizeMethods.h"
#include "StochasticOptimizator.h"
#include "StopCriterias.h"
#include "ExampleFunctions.h"
#include "AreasAndCovers.h"
#include "StopCriterias.h"
#include "GradOptFR.h"

//std::mt19937 defaultGen(time(0));
//std::uniform_real_distribution<> inSqrDist(-1, 1);
//
//double f1(vector<double> x)
//{
//	return innerProduct(x,x);
//}
//vector<double> gf1(vector<double> x)
//{
//	return 2 * x;
//}
//double f2(vector<double> x)
//{
//	return pow(x[0]-sqrt(2),2)+pow(x[1]-sqrt(2),2);
//}
//vector<double> gf2(vector<double> x)
//{
//	vector<double> vr(x.size());
//	vr[0] = 2 * x[0] - sqrt(2);
//	vr[1] = 2 * x[1] - sqrt(2);
//	return vr;
//}
//bool circleArea(vector<double> x)
//{
//	return (x[0] * x[0] + x[1] * x[1] < 1);
//}
//bool closeCr(vector<double> x0, double f0, vector<double> x1, double f1)
//{
//	return (abs(f0 - f1) < 1e-9);
//}
//vector<double> randomInSquare()
//{
//	vector<double> rv(2);
//	rv[0] = inSqrDist(defaultGen);
//	rv[1] = inSqrDist(defaultGen);
//	return rv;
//}
int main()
{
	LinearOptimizeParameters lp(1e-3, 1);
	LinearOptimizator lo(nullptr, nullptr, goldenSectionSearch, lp, 15000);
	vector<double> sidesSizes(2);
	sidesSizes[0] = 3; sidesSizes[1] = 3;
	vector<double> center(2);
	center[0] = 1, center[1] = 1;
	inAreaCheck<vector<double>> inArea = [center, sidesSizes](vector<double> x)->bool {return boxArea(x, center, sidesSizes); };
	randomPointInCoveringArea coverArea = [center, sidesSizes]()->vector<double> {return coverBallBoxAreaRG(center, sidesSizes); };
	stopCriteria<vector<double>> absValueStopSE = [](auto x0, auto f0, auto x1, auto f1)->bool { return absValueDiffStop(x0, f0, x1, f1, 1e-6); };
	GradOptFR frOpt(f2, gf2, absValueStopSE, lo, 15000);
	StochasticOptimizator stOpt(f2, absValueStopSE, coverArea, 1e-4, 50);
	vector<double> x0(2);
	x0[0] = 0; x0[1] = 0;
	std::cout << inArea(x0) << std::endl;
	std::cout << "Fisher-Rieves method:" << std::endl;
	std::cout << "Optimal value: " << frOpt.optimize(x0, inArea).second << std::endl;
	const std::deque<vector<double>>* pp = frOpt.getPathPointer();
	std::cout << "Number of iterations: " << frOpt.getNumberOfIterations() << std::endl;
	std::cout << "Stochastic method:" << std::endl;
	std::cout << "Optimal value: " << stOpt.optimize(x0, inArea).second << std::endl;
	std::cout << "Number of iterations: " << stOpt.getNumberOfIterations() << std::endl;
	return 0;
}



//int main1()
//{
//	smoothFunction<double, vector<double>> f;
//	smoothFunction<vector<double>, vector<double>> gf;
//	linearOptimizeMethod lom;
//	stopCriteria<vector<double>> stopCr;
//	inAreaCheck<vector<double>> inArea;
//	randomPointInCoveringArea coverArea;
//	LinearOptimizeParameters lp(0,0);
//	double cutRadius;
//	double stopPrecision;
//	size_t maxIterations;
//	size_t fdim;
//	try
//	{
//		std::cout << "Select a function and enter its number:" << std::endl;
//		std::cout << "1) (x-sqrt(2))^2+(y-sqrt(2))^2" << std::endl;
//		std::cout << "2) (1-x)^2+100(y-x^2)^2" << std::endl;
//		std::cout << "3) x^4+(y-0.5)^2+z^2*w^2" << std::endl;
//		std::cout << "4) exp(xy-y)+(y-2)^2" << std::endl;
//		int a;
//		std::cin >> a;
//		switch (a)
//		{
//		case 1:
//			f = f1;
//			gf = gf1;
//			fdim = 2;
//			break;
//		case 2:
//			f = f2;
//			gf = gf2;
//			fdim = 2;
//			break;
//		case 3:
//			f = f3;
//			gf = gf3;
//			fdim = 4;
//			break;
//		case 4:
//			f = f4;
//			gf = gf4;
//			fdim = 3;
//			break;
//		default:
//			throw("Wrong number");
//		}
//	}
//	catch (...)
//	{
//		std::cout << "Wrong function number" << std::endl;
//		return -1;
//	}
//	try
//	{
//		std::cout << "Select an area and enter its number:" << std::endl;
//		std::cout << "1) Symmetrical box area" << std::endl;
//		std::cout << "2) Ball area" << std::endl;
//		int a;
//		std::cin >> a;
//		vector<double> sidesSizes(fdim);
//		switch (a)
//		{
//		case 1:
//			std::cout << "Please enter " << fdim << " numbers -- sides of box:" << std::endl;
//			for (size_t i = 0; i < fdim; ++i)
//			{
//				std::cin >> sidesSizes[i];
//			}
//			inArea = [sidesSizes](vector<double> x)->bool {return boxArea(x, sidesSizes); };
//			coverArea = [sidesSizes]()->vector<double> {return coverBallBoxAreaRG(sidesSizes); };
//			break;
//		case 2:
//			std::cout << "Please enter radius of ball: " << std::endl;
//			double r;
//			std::cin >> r;
//			for (double el : sidesSizes) el = r;
//			inArea = [r](vector<double> x)->bool {return ballArea(x, r); };
//			coverArea = [sidesSizes]()->vector<double> {return coverBallBoxAreaRG(sidesSizes); };
//			break;
//		default:
//			throw("Wrong number");
//		}
//	}
//	catch (...)
//	{
//		std::cout << "Wrong function number" << std::endl;
//		return -1;
//	}
//	try
//	{
//		std::cout << "Select a linear optimization method and enter its number:" << std::endl;
//		std::cout << "1) Linear search" << std::endl;
//		std::cout << "2) Ternary search" << std::endl;
//		std::cout << "3) Golden section search" << std::endl;
//		std::cout << "4) Binary search" << std::endl;
//		int a;
//		std::cin >> a;
//		vector<double> sidesSizes(fdim);
//		switch (a)
//		{
//		case 1:
//			lom = linearSearch;
//			break;
//		case 2:
//			lom = ternarySearch;
//			break;
//		case 3:
//			lom = goldenSectionSearch;
//			break;
//		case 4:
//			lom = binarySearch;
//			break;
//		default:
//			throw("Wrong number");
//		}
//
//	}
//	catch (...)
//	{
//		std::cout << "Wrong function number" << std::endl;
//		return -1;
//	}
//	try
//	{
//		std::cout << "Select a stop criteria and enter its number:" << std::endl;
//		std::cout << "1) Absolute value difference" << std::endl;
//		std::cout << "2) Absolute point difference" << std::endl;
//		std::cout << "3) Relative value difference" << std::endl;
//		std::cout << "4) Relative point difference" << std::endl;
//		int a;
//		std::cin >> a;
//		std::cout << "Enter stop precision: " << std::endl;
//		std::cin >> stopPrecision;
//		vector<double> sidesSizes(fdim);
//		switch (a)
//		{
//		case 1:
//			stopCr = [stopPrecision](auto x0, auto f0, auto x1, auto f1)->bool {return absValueDiffStop(x0, f0, x1, f1, stopPrecision); };
//			break;
//		case 2:
//			stopCr = [stopPrecision](auto x0, auto f0, auto x1, auto f1)->bool {return absCoordDiffStop(x0, f0, x1, f1, stopPrecision); };
//			break;
//		case 3:
//			stopCr = [stopPrecision](auto x0, auto f0, auto x1, auto f1)->bool {return relValueDiffStop(x0, f0, x1, f1, stopPrecision); };
//			break;
//		case 4:
//			stopCr = [stopPrecision](auto x0, auto f0, auto x1, auto f1)->bool {return relCoordDiffStop(x0, f0, x1, f1, stopPrecision); };
//			break;
//		default:
//			throw("Wrong number");
//		}
//	}
//	catch (...)
//	{
//		std::cout << "Wrong function number" << std::endl;
//		return -1;
//	}
//	try
//	{
//		std::cout << "Enter linear search parameters: searchPrecision and indent: " << std::endl;
//		double a, b;
//		std::cin >> a >> b;
//		lp=LinearOptimizeParameters(a, b);
//		std::cout << "Enter maximum of iterations: " << std::endl;
//		std::cin >> maxIterations;
//		std::cout << "Enter radius of cutting ball in stochastic method: " << std::endl;
//		std::cin >> cutRadius;
//	}
//	catch (...)
//	{
//		std::cout << "Wrong enter parameters" << std::endl;
//		return -1;
//	}
//	//lp.searchPrecision = 1e-3;
//	//lp.indent = 1;
//	//fdim = 2;
//	//lom = goldenSectionSearch;
//	//double r = 3;
//	//vector<double> sidesSizes(fdim);
//	//for (double el : sidesSizes) el = r;
//	//inArea = [r](vector<double> x)->bool {return ballArea(x, r); };
//	//coverArea = [sidesSizes]()->vector<double> {return coverBallBoxAreaRG(sidesSizes); };
//	//cutRadius = 1e-4;
//	//maxIterations = 1000;
//	//f = f2;
//	//gf = gf2;
//	//stopPrecision = 1e-6;
//	//stopCr = [stopPrecision](auto x0, auto f0, auto x1, auto f1)->bool {return absValueDiffStop(x0, f0, x1, f1, stopPrecision); };
//	//std::cout << lp.searchPrecision << " " << lp.indent << std::endl;
//	//std::cout << maxIterations << std::endl;
//	//std::cout << cutRadius << std::endl;
//	LinearOptimizator lo(nullptr, nullptr, lom, lp, maxIterations);
//	GradOptFR frOpt(f, gf, stopCr, lo, maxIterations);
//	StochasticOptimizator stOpt(f, stopCr, coverArea, cutRadius, maxIterations);
//	while (true)
//	{
//		std::cout << "Enter " << fdim << " coordinates of start point:" << std::endl;
//		vector<double> x0(fdim);
//		for (int i = 0; i < x0.size(); ++i) std::cin >> x0[i];
//		print(x0);
//		if (!inArea(x0))
//		{
//			std::cout << "Warning! Start point not in area." << std::endl;
//			continue;
//		}
//		std::cout << "Fisher-Rieves method:" << std::endl;
//		std::cout << "Optimal value: " << frOpt.optimize(x0, inArea).second << std::endl;
//		std::cout << "Number of iterations: " << frOpt.getNumberOfIterations() << std::endl;
//		std::cout << "Stochastic method:" << std::endl;
//		std::cout << "Optimal value: " << stOpt.optimize(x0, inArea).second << std::endl;
//		std::cout << "Number of iterations: " << stOpt.getNumberOfIterations() << std::endl;
//		while (true)
//		{
//			std::cout << "Do you want to repeat at another start point? Y/N";
//			char ch;
//			std::cin >> ch;
//			if ((ch == 'y') || (ch == 'Y')) break;
//			if ((ch == 'n') || (ch == 'N')) return 0;
//		}
//	}
//}