/*
 * anomaly_detection_util.h
 *
 * Author: 206312654 Roy Maman
 *         316099548 Yonatan Lahav
 */
#include "minCircle.h"
#include <algorithm>
#include <vector>
#include <valarray>


/**
 * getting the distance between two points.
 * @param a first point.
 * @param b second point.
 * @return distance.
 */
float dist(const Point &a, const Point &b) {
    return (float) (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}

/**
 * findMInCircle generate the minimal circle that contain all the point from the given points.
 * @param points the given points that the circle should contain.
 * @param size the amount of points in points array.
 * @return Circle MEC.
 */
Circle findMinCircle(Point **points, size_t size) {
    return findMinCircleHelper(points, {}, size);
}

/**
 * findMinCircleHelper used to help to findMInCircle function by implement the WELZL'S algorithm with
 * recursive iterations.
 * @param points the points that should be inside the MEC.
 * @param boundary the points on the boundary of the circle.
 * @param size the size of the remains points in every iteration.
 * @return return the MEC of all the given points.
 */
Circle findMinCircleHelper(Point **points, vector<Point> boundary, size_t size) {
    if (size == 0 || boundary.size() == 3)
        return createTrivialCircle(boundary);
    unsigned int index = rand() % size;
    Point randomPoint(points[index]->x, points[index]->y);
    swap(points[index], points[size - 1]);
    Circle MEC = findMinCircleHelper(points, boundary, size - 1);
    if (pointIsInsideCircle(MEC, randomPoint))
        return MEC;
    boundary.push_back(randomPoint);
    return findMinCircleHelper(points, boundary, size - 1);
}

/**
 * Checking wether a point is in a given circle or not.
 * @param circle given circle.
 * @param point given point.
 * @return true if inside false if outside.
 */
bool pointIsInsideCircle(Circle circle, Point point) {
    return dist(circle.center, point) <= circle.radius;
}

/**
 * createTrivialCircle generate a trivial circle from the given vector of points.
 * @param points vector of points with 3 points at most.
 * @return Circle MEC that contain the all the points.
 */
Circle createTrivialCircle(vector<Point> &points) {
    if (points.empty())
        return {Point(0, 0), 0};
    else if (points.size() == 1)
        return {points[0], 0};
    else if (points.size() == 2)
        return circleFromTwoPoint(points[0], points[1]);
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            Circle circle = circleFromTwoPoint(points[i], points[j]);
            if (circleIsValid(circle, points))
                return circle;
        }
    }
    return circleFromThreePoint(points[0], points[1], points[2]);
}

/**
 * circleFromThreePoint generate a circle from 3 given points.
 * @param point0  first point.
 * @param point1  second point.
 * @param point2  third point.
 * @return Circle that contain the 3 points.
 */
Circle circleFromThreePoint(Point &point0, Point &point1, Point &point2) {
    Point center = getCircleCenter(point1.x - point0.x, point1.y - point0.y,
                                   point2.x - point0.x, point2.y - point0.y);
    center.x += point0.x;
    center.y += point0.y;
    return {center, dist(center, point0)};
}

/**
 * checking if all the points are inside or on the given circle.
 * @param circle given circle.
 * @param points given points.
 * @return true if the all the points are legal false otherwise.
 */
bool circleIsValid(Circle circle, vector<Point> &points) {
    for (const Point &point: points)
        if (!pointIsInsideCircle(circle, point))
            return false;
    return true;
}

/**
 * creating a circle from two points.
 * @param point1 first point.
 * @param point2 second point.
 * @return the smallest circle which two points can create.
 */
Circle circleFromTwoPoint(const Point &point1, const Point &point2) {
    float x = (point1.x + point2.x) / 2;
    float y = (point1.y + point2.y) / 2;
    Point center(x, y);
    float radius = dist(point1, point2) / 2;
    return {center, radius};
}

/**
 * getting the center of the circle from 3 points.
 * @param bx point1.x - point0.x .
 * @param by point1.y - point0.y .
 * @param cx point2.x - point0.x .
 * @param cy point2.y - point0.y .
 * @return the center point.
 */
Point getCircleCenter(float bx, float by, float cx, float cy) {
    float B = bx * bx + by * by;
    float C = cx * cx + cy * cy;
    float D = bx * cy - by * cx;
    return {(cy * B - by * C) / (2 * D), (bx * C - cx * B) / (2 * D)};
}


