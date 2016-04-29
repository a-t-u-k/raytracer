#ifndef ZPOL_H_
#define ZPOL_H_

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <ctime>
#include <list>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>


// intel embree:
#include <xmmintrin.h>
#include "objTester/objLoader.h"

#if !defined(_MM_SET_DENORMALS_ZERO_MODE)
#define _MM_DENORMALS_ZERO_ON   (0x0040)
#define _MM_DENORMALS_ZERO_OFF  (0x0000)
#define _MM_DENORMALS_ZERO_MASK (0x0040)
#define _MM_SET_DENORMALS_ZERO_MODE(x) (_mm_setcsr((_mm_getcsr() & ~_MM_DENORMALS_ZERO_MASK) | (x)))
#endif
// :intel embree

typedef cv::Vec<unsigned short, 3> Vec3ui;

using namespace cv;
using namespace std;

template<typename ValueType>
std::string stringulate(ValueType v)
{
    std::ostringstream oss;
    oss << v;
    return oss.str();
}


class Ray
{
public:
	int i;
	int j;
	Mat direction=(Mat_<float>(3,1) << 0.0, 0.0, 0.0);
	Mat origin=(Mat_<float>(3,1) << 0.0, 0.0, 0.0);
	Mat normal=(Mat_<float>(3,1) << 0.0, 0.0, 0.0);
	int is_propagating=1;
	float t_closest=0.0;
};

// returns rotation matrix:
void give_rotation_matrix(Mat *axisP1, Mat *axisP2, float angle, Mat *Rot, Mat *T);

/* vertex and triangle layout */
#if !defined(__NO_VERTEX__)
struct Vertex   { float x,y,z,r; };
#endif

struct Triangle { int v0, v1, v2; };

void intersect_ray_and_plane(Mat *II, Mat *plane_origin, Mat *plane_ox, Mat *plane_oy, float plane_size_x, float plane_size_y, Mat *ray_origin, Mat *ray_direction, int &r, int &g, int &b, Mat *intersection_point, int &is_intersecting);


#endif
