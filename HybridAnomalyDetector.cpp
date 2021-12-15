/*
 * SimpleAnomalyDetector.cpp
 *
 * Author: 206312654 Roy Maman
 *         316099548 Yonatan Lahav
 */
#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() {
}

HybridAnomalyDetector::~HybridAnomalyDetector() {
}

void HybridAnomalyDetector::insertCF(string feature1, string feature2, float corrlation, const TimeSeries &ts,
                                     vector<Point *> &pointsVector) {
    Point *points[pointsVector.size()];
    int i = 0;
    for (Point *point: pointsVector) {
        points[i] = point;
        i++;
    }
    SimpleAnomalyDetector::insertCF(feature1, feature2, corrlation, ts, pointsVector);
    if (corrlation > 0.5 && corrlation < 0.9) {
        correlatedFeatures correlatedFeature;
        correlatedFeature.feature1 = feature1;
        correlatedFeature.feature2 = feature2;
        correlatedFeature.corrlation = corrlation;
        correlatedFeature.lin_reg = Line();
        correlatedFeature.mec = findMinCircle(points, pointsVector.size());
        correlatedFeature.threshold =
                calculateThreshold(correlatedFeature.mec, pointsVector, ts.getRowSize()) * 1.1;
        this->cf.push_back(correlatedFeature);
    }
}


float HybridAnomalyDetector::calculateThreshold(Circle mec, vector<Point *> &pointsVector, size_t size) {
    float max = 0;
    float tempDist;
    for (Point *point: pointsVector) {
        tempDist = dist(*point, mec.center);
        max = (max < tempDist) ? tempDist : max;
    }
    return max;
}

void HybridAnomalyDetector::detectHelper(correlatedFeatures &correlatedFeature, string feature1, string feature2,
                                         vector<AnomalyReport> &anomalyReports, int i) {
    if (correlatedFeature.corrlation > 0.9)
        SimpleAnomalyDetector::detectHelper(correlatedFeature, feature1, feature2, anomalyReports, i);
    else if (correlatedFeature.corrlation > 0.5 && correlatedFeature.corrlation < 0.9)
        if (abs(dist(Point(stof(feature1), stof(feature2)), correlatedFeature.mec.center) >
                correlatedFeature.threshold)) {
            string description = correlatedFeature.feature1 + "-" + correlatedFeature.feature2;
            anomalyReports.push_back(AnomalyReport(description, i + 1));
        }
}




