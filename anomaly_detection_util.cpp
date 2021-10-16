/*
 * animaly_detection_util.cpp
 *
 * Author: 206312654 Roy Maman
 */

#include <math.h>
#include "anomaly_detection_util.h"

float avg(float *x, int size)
{
    if (size != 0)
    {
        float sum = 0;
        for (int i = 0; i < size; i++)
            sum = sum + x[i];
        return sum / size;
    }
}

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


// returns the covariance of X and Y
float cov(float *x, float *y, int n)
{
    if (n > 1)
    {
        float sum = 0;
        for (int i = 0; i < n; i++)
            sum = sum + (x[i] - avg(x, n)) *
                            (y[i] - avg(y, n));
        return sum / (n - 1);
    }
}

// returns the Pearson correlation coefficient of X and Y
float pearson(float *x, float *y, int size)
{
	if (sqrt(var(x, size)) == 0 || sqrt(var(y, size) == 0))
		return 0;
	return cov(x, y, size) / (sqrt(var(x, size)) * sqrt(var(y, size)));
}

// performs a linear regression and returns the line equation
Line linear_reg(Point **points, int size)
{
    float x[size];
    float y[size];
    for (int i = 0; i < size; i++)
    {
        x[i] = points[i]->x;
        y[i] = points[i]->y;
    }
    float a = cov(x, y, size)/var(x, size);
    float b = avg(y, size) - a*avg(x, size);
    return Line(a,b);
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