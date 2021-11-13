/*
 * SimpleAnomalyDetector.h
 *
 * Author: 206312654 Roy Maman
 *         316099548 Yonatan Lahav
 */

#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>

struct correlatedFeatures {
    string feature1, feature2;  // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
};


class SimpleAnomalyDetector : public TimeSeriesAnomalyDetector {
    vector<correlatedFeatures> cf;
public:
    SimpleAnomalyDetector();

    virtual ~SimpleAnomalyDetector();

    virtual void learnNormal(const TimeSeries &ts);

    virtual vector<AnomalyReport> detect(const TimeSeries &ts);

    vector<correlatedFeatures> getNormalModel() {
        return cf;
    }

    float calculateThreshold(Line lineReg, vector<Point *> &pointsVector, size_t size);
};


#endif /* SIMPLEANOMALYDETECTOR_H_ */
