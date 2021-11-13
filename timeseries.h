/*
 * timeseries.h
 *
 * Author: 206312654 Roy Maman
 *         316099548 Yonatan Lahav
 */

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <map>
#include <vector>

using namespace std;

class TimeSeries {

private:
    //Map with the data from the csv.
    map<string, vector<string>> dataMap;
    //Vector with the features of the csv.
    vector<string> featuresVector;
    //Features amount.
    unsigned int rowSize;
public:
    //Constructor.
    explicit TimeSeries(const char *CSVfileName);
    ~TimeSeries()= default;
};


#endif /* TIMESERIES_H_ */
