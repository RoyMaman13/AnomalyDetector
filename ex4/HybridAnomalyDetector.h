/*
 * SimpleAnomalyDetector.cpp
 *
 * Author: 206312654 Roy Maman
 *         316099548 Yonatan Lahav
 */

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector : public SimpleAnomalyDetector {
public:
    HybridAnomalyDetector();

    virtual ~HybridAnomalyDetector();

    virtual void
    insertCF(string feature1, string feature2, float corrlation, const TimeSeries &ts, vector<Point *> &pointsVector);

    virtual void detectHelper(correlatedFeatures &correlatedFeature, string feature1, string feature2,
                              vector<AnomalyReport> &anomalyReports, int i);

    float calculateThreshold(Circle mec, vector<Point *> &pointsVector, size_t size);

};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
