#pragma once
#include "BasicDef.h"
const double STANDARD_STOP_EPSILON = 1e-12;

bool absValueDiffStop(vector<double> x0, double f0, vector<double> x1, double f1, double eps);
bool absCoordDiffStop(vector<double> x0, double f0, vector<double> x1, double f1, double eps);
bool relValueDiffStop(vector<double> x0, double f0, vector<double> x1, double f1, double eps);
bool relCoordDiffStop(vector<double> x0, double f0, vector<double> x1, double f1, double eps);