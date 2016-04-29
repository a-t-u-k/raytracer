#ifndef ACCEL_H_
#define ACCEL_H_

#include "z_pol.h"

void callCudaFnc(vector<Ray> *rays, std::list<int> *active_rays, float n0, float n1);

#endif /* ACCEL_H_ */
