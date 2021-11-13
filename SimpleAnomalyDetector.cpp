/*
 * SimpleAnomalyDetector.cpp
 *
 * Author: 206312654 Roy Maman
 *         316099548 Yonatan Lahav
 */

#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    //init 2D array by ts.
    float array[ts.getFeatures().size()][ts.getRowSize()];
    size_t i = 0, j = 0;
    for (const string &feature: ts.getFeatures()) {
        for (const string &value: ts.getFeatureValues(feature)) {
            array[i][j] = stof(value);
            j++;
        }
        i++;
        j = 0;
    }

    for (i = 0; i < ts.getFeatures().size(); ++i) {
        float maxPearson = 0.9;
        size_t c = (-1);
        for (j = i + 1; j < ts.getFeatures().size(); ++j) {
            float tempPearson = abs(pearson(array[i], array[j], ts.getRowSize()));
            if (tempPearson > maxPearson) {
                maxPearson = tempPearson;
                c = j;
            }
        }
        if (c != (-1)) {
            correlatedFeatures correlatedFeature;
            correlatedFeature.feature1 = ts.getFeatures()[i];
            correlatedFeature.feature2 = ts.getFeatures()[c];
            correlatedFeature.corrlation = maxPearson;
            vector<Point *> pointsVector;
            for (size_t k = 0; k < ts.getRowSize(); ++k) {
                pointsVector.push_back(new Point(array[i][k], array[c][k]));
            }
            correlatedFeature.lin_reg = linear_reg(pointsVector, ts.getRowSize());
            correlatedFeature.threshold = calculateThreshold(correlatedFeature.lin_reg, pointsVector, ts.getRowSize());
            this->cf.push_back(correlatedFeature);
        }
    }
}


vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    // TODO Auto-generated destructor stub
}

float SimpleAnomalyDetector::calculateThreshold(Line lineReg, vector<Point *> &pointsVector, size_t size) {
    float max = 0;
    float tempDev;
    for (Point *point: pointsVector) {
        tempDev = dev(*point, lineReg);
        max = (max < tempDev) ? tempDev : max;
    }
    return max;
}

