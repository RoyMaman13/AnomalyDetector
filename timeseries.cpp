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
    //continue to iterate on the csv file from second tow until the end.
    while (getline(file, line, '\n')) {
        stringstream valueStream(line);
        auto it = this->featuresVector.begin();
        //split every line by ',' and push them to the correct key (feature's column).
        while (getline(valueStream, value, ',')) {
            this->dataMap[*it].push_back(value);
            it++;
        }
    }
    //set row size field.
    this->rowSize=this->featuresVector.capacity();
}





