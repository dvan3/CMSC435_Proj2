/* -*- c++ -*-
 * Sphere.cpp
 * CMSC 435/634, Spring 2012
 * Dave Van <dvan3@umbc.edu>
 *
 * Sphere class.
 */

#include "Sphere.h"
#include "vec.h"
#include <iostream>

using namespace std;

//default contructor
Sphere::Sphere()
{

}

//contructor
Sphere::Sphere(vec center, double radius, vec color)
{
    mCenter = center ;
    mRadius = radius;
    mColor = color;
}

double Sphere::getRadius()
{
    return mRadius;
}

vec Sphere::getCenter()
{
    return mCenter;
}

vec Sphere::getColor()
{
    return mColor;

}

float Sphere::getRed()
{
   return mColor.x();
}

float Sphere::getGreen()
{
   return mColor.y();
}

float Sphere::getBlue()
{
   return mColor.z();
}

void Sphere::setCenter(vec newCenter)
{
    mCenter = newCenter;
}

void Sphere::setRadius(double newRadius)
{
    mRadius = newRadius;
}

void Sphere::setColor(vec newColor)
{
    mColor = newColor;
}
