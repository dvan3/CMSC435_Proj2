/* -*- c++ -*-
 * Sphere.cpp
 * CMSC 435/634, Spring 2012
 * Dave Van <dvan3@umbc.edu>
 *
 * Sphere class.
 */

#ifndef SPHERE_H
#define SPHERE_H

#include "vec.h"

class Sphere
{
public:
   //default constructor
   Sphere();
   
   //constructor
   Sphere(vec center, double radius, vec color);
   
   vec getCenter();
   double getRadius();
   vec getColor();
   float getRed();
   float getGreen();
   float getBlue();

   void setCenter(vec newCenter);
   void setRadius(double newRadius);
   void setColor(vec newColor);
   
private:
   double mRadius;
   vec mColor;
   vec mCenter;
};

#endif // SPHERE_H

