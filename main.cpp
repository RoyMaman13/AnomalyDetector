#include <iostream>
#include "anomaly_detection_util.h"
int main(int argc, char const *argv[])
{
    float test[] = {1, 2, 3, 4, 5, 6};
    std::cout << var(test, 6);
    return 0;
}
