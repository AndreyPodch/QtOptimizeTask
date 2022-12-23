#pragma once
#include "BasicDef.h"
#include "DerivativeOptimizatorInterface.h"
#include "LinearOptimizator.h"
/// <summary>
/// Implement Fisher-Rieves method for multidimensional optimization 
/// </summary>
class GradOptFR : public DerivativeOptimizatorInterface<vector<double>>
{
private:
	/// <summary>
	/// Linear Optimizator that used in optimize function
	/// </summary>
	LinearOptimizator lo;
public:
	GradOptFR(smoothFunction<double, vector<double>> f_, smoothFunction<vector<double>, vector<double>> gradf_, stopCriteria<vector<double>> Stop_,
		linearOptimizeMethod lom_, LinearOptimizeParameters lp_,
		size_t maxIterations_ = MAX_OPTIMIZE_ITERATIONS
		) : DerivativeOptimizatorInterface(f_, gradf_, Stop_, maxIterations_), lo(nullptr, nullptr, lom_, lp_, maxIterations_) {};
	GradOptFR(smoothFunction<double, vector<double>> f_, smoothFunction<vector<double>, vector<double>> gradf_, stopCriteria<vector<double>> Stop_,
		LinearOptimizator lo_, size_t maxIterations_ = MAX_OPTIMIZE_ITERATIONS)
		: DerivativeOptimizatorInterface(f_, gradf_, Stop_, maxIterations_), lo(lo_) {};
    virtual ~GradOptFR() {};
	std::pair<vector<double>, double> optimize(vector<double> x0, inAreaCheck<vector<double>> inArea) final;
};

