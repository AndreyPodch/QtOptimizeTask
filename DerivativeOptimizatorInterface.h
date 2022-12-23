#pragma once

#include "BasicDef.h";
#include "OptimizatorInterface.h"
template <class T>
/// <summary>
/// Class for optimization with existed (or approximate calculated) derivative (or gradient)
/// </summary>
/// <typeparam name="T"></typeparam>
class DerivativeOptimizatorInterface: public OptimizatorInterface<T>
{
protected:
	/// <summary>
	/// Derivative or gradient of f function
	/// </summary>
	smoothFunction<T, T> fDiff;
public:
	DerivativeOptimizatorInterface<T>(smoothFunction<double, T> f_, smoothFunction<T, T> fDiff_, stopCriteria<T> Stop_, 
		size_t maxIterations_ = MAX_OPTIMIZE_ITERATIONS) : OptimizatorInterface<T>(f_, Stop_, maxIterations_), fDiff( fDiff_ ) {};
    virtual ~DerivativeOptimizatorInterface<T>() = default;
	void setFunctionAndDifferential(smoothFunction<double, T> f_, smoothFunction<T, T> fDiff_) { OptimizatorInterface<T>::f = f_; fDiff = fDiff_; }
};

