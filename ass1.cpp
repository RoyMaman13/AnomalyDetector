#include <iostream>
#include <cmath>

float var(float *x, int size)
{
    float miu = 0, var = 0;
    for (int i = 1; i <= size; i++)
    {
        miu += x[i - 1];
    }
    miu /= size;
    for (int i = 0; i <= size; i++)
    {
        var += pow(x[i - 1] - miu, 2);
    }
    return var/size;
}