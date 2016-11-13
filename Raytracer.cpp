/* -*- c++ -*-
 * main.cpp
 * CMSC 435/634, Spring 2012
 * Dave Van <dvan3@umbc.edu>
 * 
 * Main driver class.
 *
 * Discussed designs and vector math with Sean Cosentino
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include "Sphere.h"
#include "vec.h"

using namespace std;

/*
 * Returns the background color
 */
static vec doBackground(string line)
{
   //variables
   string command;
   float r, g, b;
   vec backGround;
 
   //reads the line
   std::stringstream data(line);
   
   //takes in each command and variables
   data >> command >> r >> g >> b;
   
   //setting the background color
   backGround = vec(r, g, b);
   
   return backGround;
}

/*
 * Returns the eye point
 */
static vec doFrom(string line)
{
   //variables
   string command;
   double x, y, z;
   vec eye;
   
   //reads the line
   std::stringstream data(line);
   
   //takes in each command and variables
   data >> command >> x >> y >> z;
   
   //setting the eye point
   eye = vec(x, y, z);
   
   return eye;
}

/*
 * Returns basis vector w
 */
static vec doAt(string line, vec eye)
{
   //variables  
   string command;
   double x, y, z;
   vec w, at;

   //reads the line
   std::stringstream data(line);

   //takes in each command and variables
   data >> command >> x >> y >> z;

   //sets at vector
   at = vec(x, y, z);
   
   //finds g
   vec g = (eye - at);
   
   //normalizing g
   w = -g.normalize();
   
   return w;
}

/*
 * Returns basis vector u
 */
static vec doUp(string line, vec w)
{
   //variables
   string command;
   double x, y, z;
   vec up, u, temp;
   
   //reads the line
   std::stringstream data(line);
   
   //takes in each command and variables
   data >> command >> x >> y >> z;
   
   //setting up vector
   up = vec(x, y, z);
   
   //normalizing cross product of up and w
   u = (up ^ w).normalize();
   
   return u;
}

/*
 * Returns the camera angle
 */
static double doAngle(string line)
{
   //variables
   string command;
   double angle;
   
   //reads the line
   std::stringstream data(line);
   
   //takes in each command and variables
   data >> command >> angle;
   
   return angle;
}

/*
 * Returns hither
 */
static double doHither(string line)
{
   //variables
   string command;
   double hither;
   
   //reads the line
   std::stringstream data(line);
   
   //takes in each command and variables
   data >> command >> hither;
   
   return hither;
}

/*
 * Returns the sphere color
 */
static vec doFill(string line, vec color)
{
   //variables
   string command;
   double r, g, b;
   
   //reads the line
   std::stringstream data(line);
   
   //takes in each command and variables
   data >> command >> r >> g >> b;
   
   //setting the color vector
   color = vec(r, g, b);
   
   return color;
}

bool hitSphere(vec eye, Sphere &s, double uS, double vS, double wS, 
	       vec u, vec v, vec w)
{
   //variable
   bool intersect;
  
   //e + ((u * uS) + (v * vS) + (w * wS))
   vec s1 = eye + ((u * uS) + (v * vS) + (w * wS));
   
   //D Vector
   vec D = s1 - eye;

   //(e - c)
   vec dist = eye - s.getCenter();
   
   //(D * D)
   double dotD = D * D;
    
   //(e - c) * (e - c)
   double dotDist = dist * dist;

   //Radius Squared
   double rSquard = s.getRadius() * s.getRadius();

   //(D * (e - c))
   double q1 = (D * dist);
   
   //(D * (e - c))^2
   double q2 = q1 * q1;
    
   //(D * D)((e - c) * (e - c) - R^2)
   double q3 = dotD * (dotDist - rSquard);
    
   //determinant
   double determinant = q2 - q3;
    
   //determinant is negative
   if(determinant < 0)
   {
      intersect = false; //no intersection
   }
   //determinant is positive
   else if(determinant >= 0)
   {
      intersect = true; //intersection
   }
   
   return intersect;
}

vec sphereIntersect(vec eye, Sphere &s, double uS, double vS, double wS,
		    vec u, vec v, vec w)
{
   double closestPoint;
   vec closestIntersect;

   //e + ((u * uS) + (v * vS) + (w * wS))   
   vec s1 = eye + ((u * uS) + (v * vS) + (w * wS));

   //D Vector
   vec D = s1 - eye;

   //(e - c)
   vec dist = eye - s.getCenter();

   //(D * D)
   double dotD = D * D;

   //(e - c) * (e - c)
   double dotDist = dist * dist;

   //Radius Squared
   double rSquard = s.getRadius() * s.getRadius();
   
   //(D * (e - c))
   double q1 = (D * dist);
   
   //(D * (e - c))^2
   double q2 = q1 * q1;

   //(D * D)((e - c) * (e - c) - R^2)
   double q3 = dotD * (dotDist - rSquard);

   //determinant
   double determinant = q2 - q3;

   //determinant is positive
   if(determinant >= 0)
   {
      //square root the determinant
      double sqrtD = sqrt(determinant);
     
      //add
      double plus = (-(q1) + sqrtD) / dotD;
     
      //subtract
      double minus = (-(q1) - sqrtD) / dotD;
      
      //if plus is smaller
      if(plus < minus)
      {
	 //the closest point
	 closestPoint = plus;
	
	 //the closest intersection
	 closestIntersect = eye + (D * closestPoint);
      }
      else
      {
	 //the closest point
	 closestPoint = minus;
	 
	 //the closest intersection
	 closestIntersect = eye + (D * closestPoint);
      }
   }
   return closestIntersect;
}


int main(int argc, char *argv[])
{
   //if the user didn't provide a filename command line argument
   //print an error and exit
   if(argc < 1)
   {
      cout << "Usage: " << argv[1] << " <Filename>" << endl;
   }
   
   //file to open
   ifstream myFile(argv[1]);
   
   //variables
   string line;
   vec color, eye, w, u, v, closestIntersect, backGround;
   double top, bottom, left, right, hither, angle, uS, vS, wS;
   int numX, numY;
   vector<Sphere> collection;
   
   //if the file is open
   if(myFile.is_open())
   {
      //while there are lines to read
      while(getline(myFile, line))
      {
	 
	 if((line.at(0)) == 'b') /*background*/
	 {
	    backGround = doBackground(line);
	 }
	 else if((line.at(0)) == 'f' && ((line.at(1)) == 'r')) /*from*/
	 {
	    eye = doFrom(line);
	 }
	 else if((line.at(0)) == 'a' && ((line.at(1)) == 't')) /*at*/
	 {
	    w = doAt(line, eye);
	 }
	 else if((line.at(0)) == 'u') /*up*/
	 {
	    u = doUp(line, w);
	    v = w ^ u;
	 }
	 else if(line.at(0) == 'a' && ((line.at(1)) == 'n')) /*angle*/
	 {
	    angle = doAngle(line);
	 }
	 else if((line.at(0)) == 'h') /*hither*/
	 {
	    hither = doHither(line);
	 }
	 else if((line.at(0)) == 'r') /*resolution*/
	 {
	    //variables
	    string command;
	    int resX, resY;
	    
	    //read the line
	    std::stringstream data(line);
	    
	    //take the command and variables
	    data >> command >> resX >>resY;
	    
	    //setting the X,Y resolution
	    numX = resX;
	    numY = resY;
	    
	 }
	 else if((line.at(0)) == 'f') /*fill*/
	 {
	    color = doFill(line, color);
	 }
	 else if((line.at(0)) == 's') /*sphere*/
	 {
	    //variables
	    string command;
	    double x, y, z, r;
	    
	    //read the line
	    std::stringstream data(line);
	    
	    //take in the command and variables
	    data >> command >> x >> y >> z >> r;
	    
	    //create a sphere
	    Sphere sphere(vec(x, y, z), r, color);
	    
	    //push the sphere onto the vector
	    collection.push_back(sphere);
	 }
      }
      
      //calculate the top/right/left/bottom
      top = hither * (tan( angle * M_PI / 360.0 ));
      right = top;
      left = -top;
      bottom = -top;
      
      //pixels
      unsigned char pixels[numY][numX][3];
      
      //***************RAY TRACER**************
      //for every X and Y pixels
      for(int pixelX = 0; pixelX < numX; pixelX++)
      {
	 for(int pixelY = 0; pixelY < numY; pixelY++)
	 {
	    //calculate the u, v, w scalars
	    uS = left + ((right - left) * (pixelX +.5)) / numX;
	    vS = bottom + ((top - bottom) * (pixelY +.5)) / numY;
	    wS = -hither;
	    
	    //set the background
	    pixels[pixelY][pixelX][0] = backGround.x() * 255;
	    pixels[pixelY][pixelX][1] = backGround.y() * 255;
	    pixels[pixelY][pixelX][2] = backGround.z() * 255;
	    
	    //for every sphere in the vector
	    for(unsigned int i = 0; i < collection.size(); i++)
	    {
	       Sphere s1 = collection.at(i);
	       
	       //if the ray hits the sphere
	       if(hitSphere(eye, s1, uS, vS, wS, u, v, w) == true)
	       {
		  //find the closest intersection
		  closestIntersect = sphereIntersect(eye, s1,
						     uS, vS, wS,
						     u, v, w);
		  
		  //fill in the color of the sphere
		  pixels[pixelY][pixelX][0] = color.x() * 255;
		  pixels[pixelY][pixelX][1] = color.y() * 255;
		  pixels[pixelY][pixelX][2] = color.z() * 255;
	       }
	    }
	 }
      }
      
      //PPM FILE CREATION
      FILE *f = fopen("trace.ppm","wb");
      fprintf(f, "P6\n%d %d\n%d\n", numX, numY, 255);
      fwrite(pixels, 1, numY*numX*3, f);
      
      cout << "...DONE" << endl;
      
      //close the files
      fclose(f);       
      myFile.close();
      return 0;
   }
}
