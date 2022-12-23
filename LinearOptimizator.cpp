#include "LinearOptimizator.h"

std::pair<double, double> LinearOptimizator::optimize(double x0, inAreaCheck<double> inArea)
{
    double leftInArea, rightInArea;
    bool leftFounded = 0, rightFounded = 0;
    double li = -lp.indent, ri = lp.indent;
    while (!(leftFounded && rightFounded)) // Looking for segment, that lies in area
    {
        if (!leftFounded && inArea(li))
        {
            leftFounded=true;
            leftInArea=li;
        }
        if (!rightFounded && inArea(ri))
        {
            rightFounded = true;
            rightInArea = ri;
        }
        li += lp.searchPrecision;
        ri -= lp.searchPrecision;
    }
    return lom(leftInArea, rightInArea, f, fDiff, lp.searchPrecision);
}
