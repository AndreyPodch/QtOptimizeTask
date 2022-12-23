#pragma once
#include "BasicDef.h"
const double LINEAR_SEARCH_SPLIT_SIZE = 1e-4;
const double STANDART_PRECISION = 1e-3;

std::pair<double, double> linearSearch(double &a, double &b, std::function <double(double)> f, std::function <double(double)> df, double eps);
std::pair<double, double> ternarySearch(double &a, double &b, std::function <double(double)> f, std::function <double(double)> df, double eps);
std::pair<double, double> goldenSectionSearch(double &a, double &b, std::function <double(double)> f, std::function <double(double)> df, double eps);
std::pair<double, double> binarySearch(double &a, double &b, std::function <double(double)> f, std::function <double(double)> df, double eps);