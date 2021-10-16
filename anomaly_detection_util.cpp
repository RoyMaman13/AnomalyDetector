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
    return 0;
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
    return 0;
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
    return 0;
}

// returns the deviation between point p and the line
float dev(Point p, Line l)
{
    return 0;
}