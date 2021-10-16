/*
 * animaly_detection_util.cpp
 *
 * Author: write your ID and name here
 */

#include <math.h>
#include "anomaly_detection_util.h"

// returns the variance of X and Y
float var(float *x, int size)
{
	if (size == 0)
		return 0;
	float miu = 0, var = 0;
	for (int i = 1; i <= size; i++)
	{
		miu += x[i - 1];
	}
	miu /= size;
	for (int i = 1; i <= size; i++)
	{
		var += pow(x[i - 1] - miu, 2);
	}
	return var / size;
}

// returns the Pearson correlation coefficient of X and Y
float pearson(float *x, float *y, int size)
{
	if (sqrt(var(x, size)) == 0 || sqrt(var(y, size) == 0))
		return 0;
	return cov(x, y, size) / (sqrt(var(x, size)) * sqrt(var(y, size)));
}

// returns the deviation between point p and the line equation of the points
float dev(Point p, Point **points, int size)
{
	return dev(p,linear_reg(points,size));
}

// returns the deviation between point p and the line
float dev(Point p, Line l)
{
	return abs(l.f(p.x)-p.y);
}
