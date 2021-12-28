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
        float maxPearson = 0.5;
        size_t c = (-1);
        for (j = i + 1; j < ts.getFeatures().size(); ++j) {
            float tempPearson = abs(pearson(array[i], array[j], ts.getRowSize()));
            if (tempPearson > maxPearson) {
                maxPearson = tempPearson;
                c = j;
            }
        }
        if (c != (-1)) {
            vector<Point *> pointsVector;
            for (size_t k = 0; k < ts.getRowSize(); ++k) {
                pointsVector.push_back(new Point(array[i][k], array[c][k]));
            }
//            correlatedFeatures correlatedFeature;
//            correlatedFeature.feature1 = ts.getFeatures()[i];
//            correlatedFeature.feature2 = ts.getFeatures()[c];
//            correlatedFeature.corrlation = maxPearson;
//            correlatedFeature.lin_reg = linear_reg(pointsVector, ts.getRowSize());
//            correlatedFeature.threshold =
//                    calculateThreshold(correlatedFeature.lin_reg, pointsVector, ts.getRowSize()) * 1.1;
//            this->cf.push_back(correlatedFeature);
            insertCF(ts.getFeatures()[i], ts.getFeatures()[c], maxPearson, ts, pointsVector);
            for (Point *point: pointsVector)
                delete point;
        }
    }
}

void SimpleAnomalyDetector::insertCF(string feature1, string feature2, float corrlation, const TimeSeries &ts,
                                     vector<Point *> &pointsVector) {
    if (corrlation > 0.9) {
        correlatedFeatures correlatedFeature;
        correlatedFeature.feature1 = feature1;
        correlatedFeature.feature2 = feature2;
        correlatedFeature.corrlation = corrlation;
        correlatedFeature.lin_reg = linear_reg(pointsVector, ts.getRowSize());
        correlatedFeature.threshold =
                calculateThreshold(correlatedFeature.lin_reg, pointsVector, ts.getRowSize()) * 1.1;
        this->cf.push_back(correlatedFeature);
    }
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

void SimpleAnomalyDetector::detectHelper(correlatedFeatures &correlatedFeature, string feature1, string feature2,
                                         vector<AnomalyReport> &anomalyReports, int i) {
    if (abs(stof(feature2) - correlatedFeature.lin_reg.f(stof(feature1))) > correlatedFeature.threshold) {
        string description = correlatedFeature.feature1 + "-" + correlatedFeature.feature2;
        anomalyReports.push_back(AnomalyReport(description, i + 1));
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    vector<AnomalyReport> anomalyReports;
    for (correlatedFeatures correlatedFeature: this->cf) {
        vector<string> feature1 = ts.getFeatureValues(correlatedFeature.feature1);
        vector<string> feature2 = ts.getFeatureValues(correlatedFeature.feature2);
        for (int i = 0; i < feature1.size(); i++) {
//            if (abs(stof(feature2[i]) - correlatedFeature.lin_reg.f(stof(feature1[i]))) > correlatedFeature.threshold) {
//                string description = correlatedFeature.feature1 + "-" + correlatedFeature.feature2;
//                anomalyReports.push_back(AnomalyReport(description, i + 1));
            detectHelper(correlatedFeature, feature1[i], feature2[i], anomalyReports, i);
//            }
        }
    }
    return anomalyReports;
}

