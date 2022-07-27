#pragma once
#include <iostream>
#include<highgui.h>

#include <windows.h>
#include <vector>   
#include "math.h"   
#include "Test.h"


using namespace std;
using namespace cv;

struct Point3D {
	double x;
	double y;
	double z;
};

extern void cvFitPlane(const CvMat* points, float* plane);

extern void column_principle_gauss(int N, double **a);

extern void Least_squares(vector<Point3D>&v_Point, double M2[3]);