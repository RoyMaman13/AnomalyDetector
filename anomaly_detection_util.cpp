#include<iostream>
// Function to find opose value.
float opose(float x[], int n)
{
	float sum = 0;
	for(int i = 0; i < n; i++)
		sum = sum + x[i];
	return sum / n;
}

// Function to find covariance.
float covariance(float* x, float* y, int n)
{
	float sum = 0;
	for(int i = 0; i < n; i++)
		sum = sum + (x[i] - opose(x, n)) *
					(y[i] - opose(y, n));
	return sum / (n - 1);
}