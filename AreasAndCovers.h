#pragma once
#include "BasicDef.h"

bool boxArea(vector<double> x, vector<double> center, vector<double> sidesSizes);
bool ballArea(vector<double> x, vector<double> center, double radius);
vector<double> coverBallBoxAreaRG(vector<double> center, vector<double> sidesSizes);