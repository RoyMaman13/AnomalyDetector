/*
 * timeseries.cpp
 *
 * Author: 206312654 Roy Maman
 *         316099548 Yonatan Lahav
 */

#include "timeseries.h"
#include <fstream>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>

using namespace std;

/**
 * TimeSeries constructor.
 * @param CSVfileName csv file name.
 */
TimeSeries::TimeSeries(const char *CSVfileName) {
    //open the csv file.
    ifstream file(CSVfileName, ios::in);
    //throw error if the given file isn't exist.
    if (!file.is_open())
        cerr << "Cant open file!" << endl;
    string line, value;
    //load to line the first line (features line).
    getline(file, line, '\n');
    stringstream stream(line);
    //split the features line by ',' and push them into featuresVector field.
    while (getline(stream, value, ',')) {
        this->featuresVector.push_back(value);
    }
    int rowCounter = 0;
    //continue to iterate on the csv file from second tow until the end.
    while (getline(file, line, '\n')) {
        stringstream valueStream(line);
        auto it = this->featuresVector.begin();
        //split every line by ',' and push them to the correct key (feature's column).
        while (getline(valueStream, value, ',')) {
            this->dataMap[*it].push_back(value);
            it++;
        }
        rowCounter++;
    }
    //set rowAmount field.
    this->rowsAmount = rowCounter;
}

/**
 * Getter for features field.
 * @return const vector of features field.
 */
const vector<string> &TimeSeries::getFeatures() const {
    return this->featuresVector;
}

/**
 * Getter for feature's values for a given feature name.
 * @param feature feature's name.
 * @return vector<string> of the feature's values.
 */
const vector<string> &TimeSeries::getFeatureValues(const string &feature) const {
    return this->dataMap.at(feature);

}

/**
 * Getter for the rows amount in the TimeSeries table.
 * @return unsigned int that represent the amount of the rows in the table.
 */
unsigned TimeSeries::getRowSize() const {
    return this->rowsAmount;
}





