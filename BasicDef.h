#pragma once
#include <boost/numeric/ublas/vector.hpp>
#include <utility>
#include <functional>
#include <iterator>
#include <list>
#include <deque>
#include <exception>
#include <random>
#include <ctime>
#include <numbers>
#include <iostream>
using namespace boost::numeric::ublas;


const double GOLDEN_RATIO= 1.61803398874989484820458683436;

const double LINEAR_OPTIMIZE_INDENT = 1;
const double LINEAR_OPTIMIZE_IN_AREA_CHECK_SPLIT_SIZE = 1e-5;
const size_t MAX_OPTIMIZE_ITERATIONS = 20000;
const double STANDART_RADIUS_OF_CUT = 0.03;

void print(vector<double> x);
template <class T, class P> using smoothFunction = std::function<T (P)>;
// template <class T> using stopCriteria = bool(*)(T x0, double f0, T x1, double f1);
template <class T> using stopCriteria = std::function<bool(T x0, double f0, T x1, double f1)>;
template <class T> using inAreaCheck = std::function<bool(T)>;
using randomPointInCoveringArea = std::function<vector<double>()>;
typedef std::pair<double, double>(*linearOptimizeMethod)(double &a, double &b, std::function <double(double)> f, std::function <double(double)> df, double eps);

double innerProduct(vector<double> x, vector<double> y);
double distanceBetween(vector<double> x, vector<double> y);