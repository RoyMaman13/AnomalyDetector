/*
 * anomaly_detection_util.h
 *
 * Author: 206312654 Roy Maman
 *         316099548 Yonatan Lahav
 */
#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"

using namespace std;


// ------------ DO NOT CHANGE -----------

class Circle {
public:
    Point center;
    float radius;

    Circle() : center(0, 0), radius(0) {}

    Circle(Point c, float r) : center(c), radius(r) {}
};

// --------------------------------------
float dist(const Point &a, const Point &b);

Circle findMinCircle(Point **points, size_t size);

Circle findMinCircleHelper(Point **points, vector<Point> boundary, size_t size);

Circle createTrivialCircle(vector<Point> &points);

Circle circleFromTwoPoint(const Point &point1, const Point &point2);

bool circleIsValid(Circle circle, vector<Point> &vector);

Circle circleFromThreePoint(Point &point0, Point &point1, Point &point2);

Point getCircleCenter(float bx, float by, float cx, float cy);

bool pointIsInsideCircle(Circle circle, Point point);

// you can add here additional methods

#endif /* MINCIRCLE_H_ */
