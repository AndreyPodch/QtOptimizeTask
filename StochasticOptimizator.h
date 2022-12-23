#pragma once
#include "BasicDef.h"
#include "OptimizatorInterface.h"
/// <summary>
/// Implement multidimensional optimization by stochastic method
/// </summary>
class StochasticOptimizator: public OptimizatorInterface<vector<double>> 
{
private:
	/// <summary>
	/// Radius of cutted circle in optimization
	/// </summary>
	double radiusOfCut;
	/// <summary>
	/// Method that gives a random point in area, thats cover optimization area
	/// </summary>
	randomPointInCoveringArea randomPt;
	bool isNotCutted(std::list<vector<double>>& v, vector<double> x0) const;
public:
	StochasticOptimizator(smoothFunction<double, vector<double>> f_, stopCriteria<vector<double>> Stop_, randomPointInCoveringArea randomPt_,
		double radiusOfCut_=STANDART_RADIUS_OF_CUT, size_t maxIterations_ = MAX_OPTIMIZE_ITERATIONS) 
		: OptimizatorInterface(f_, Stop_, maxIterations_), randomPt(randomPt_), radiusOfCut(radiusOfCut_){};
    virtual ~StochasticOptimizator() {};
	std::pair<vector<double>, double> optimize(vector<double> x0, inAreaCheck<vector<double>> inArea);
	void setFunction(smoothFunction<double, vector<double>> f_) { f = f_; };
};

