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
    //Map with the data from the csv.
    map<string, vector<string>> dataMap;
    //Vector with the features of the csv.
    vector<string> featuresVector;
    //Features amount.
    unsigned int rowsAmount;
public:
    explicit TimeSeries(const char *CSVfileName);

    ~TimeSeries() = default;

    const vector<string> &getFeatures() const;

    const vector<string> &getFeatureValues(const string &feature) const;

    unsigned getRowSize() const;
};


#endif /* TIMESERIES_H_ */
