#include <iostream>
#include "accel.h"

__global__ void refraction_cuda(float *d_ray_directions_x, float *d_ray_directions_y, float *d_ray_directions_z, float *d_ray_origins_x, float *d_ray_origins_y, float *d_ray_origins_z, float *d_normals_x, float *d_normals_y, float *d_normals_z, int *d_is_propagating, float *d_t_closest, int Size, float n0, float n1)
{
	int index=blockIdx.x*blockDim.x+threadIdx.x;
	if (index<Size)
	{
		if (d_is_propagating[index]==1)
		{
			// the ray is still propagating.

			float3 ray_direction;
			float3 plane_normal;

			ray_direction.x=d_ray_directions_x[index];
			ray_direction.y=d_ray_directions_y[index];
			ray_direction.z=d_ray_directions_z[index];
			plane_normal.x=d_normals_x[index];
			plane_normal.y=d_normals_y[index];
			plane_normal.z=d_normals_z[index];

			// normalize:
			float norm=sqrt(ray_direction.x*ray_direction.x+ray_direction.y*ray_direction.y+ray_direction.z*ray_direction.z);
			ray_direction.x=ray_direction.x/norm;
			ray_direction.y=ray_direction.y/norm;
			ray_direction.z=ray_direction.z/norm;

			norm=sqrt(plane_normal.x*plane_normal.x+plane_normal.y*plane_normal.y+plane_normal.z*plane_normal.z);
			plane_normal.x=plane_normal.x/norm;
			plane_normal.y=plane_normal.y/norm;
			plane_normal.z=plane_normal.z/norm;

			// dot product:
			float cos_incoming_alpha = plane_normal.x*ray_direction.x + plane_normal.y*ray_direction.y + plane_normal.z*ray_direction.z;
		    if (cos_incoming_alpha<0){ // normal vector is directed towards ray origin
		        cos_incoming_alpha=-cos_incoming_alpha;
		        plane_normal.x=-plane_normal.x;
		        plane_normal.y=-plane_normal.y;
		        plane_normal.z=-plane_normal.z;
		        // normal vector is directed towards the ray propagation
		    }

		    float incoming_alpha=acos(cos_incoming_alpha);
		    float sin_outcoming_alpha=n0*sin(incoming_alpha)/n1;
		    if (sin_outcoming_alpha>=1.0){
		        // terminate ray propagation - total internal reflection
		    	d_is_propagating[index]=0;
		        return;
		    }

		    // update the ray origin:
		    d_ray_origins_x[index] += d_t_closest[index]*d_ray_directions_x[index];
		    d_ray_origins_y[index] += d_t_closest[index]*d_ray_directions_y[index];
		    d_ray_origins_z[index] += d_t_closest[index]*d_ray_directions_z[index];

		    float outcoming_alpha=asin(sin_outcoming_alpha);

		    if (sin_outcoming_alpha>0){
		    	// vector orthogonal to the refraction plane
		    	float3 n_ort;
		    	n_ort.x = plane_normal.y * ray_direction.z - plane_normal.z * ray_direction.y;
		    	n_ort.y = plane_normal.z * ray_direction.x - plane_normal.x * ray_direction.z;
		    	n_ort.z = plane_normal.x * ray_direction.y - plane_normal.y * ray_direction.x;
		        // vector in the refr. plane perpend. to normal
		    	float3 n_perp;
		    	n_perp.x = plane_normal.y * n_ort.z - plane_normal.z * n_ort.y;
		    	n_perp.y = plane_normal.z * n_ort.x - plane_normal.x * n_ort.z;
		    	n_perp.z = plane_normal.x * n_ort.y - plane_normal.y * n_ort.x;

		    	// normalize just in case:
				float norm=sqrt(n_perp.x*n_perp.x+n_perp.y*n_perp.y+n_perp.z*n_perp.z);
				n_perp.x=n_perp.x/norm;
				n_perp.y=n_perp.y/norm;
				n_perp.z=n_perp.z/norm;

				float3 dir1;
				float3 dir2;
				float3 dir;

				// one potential point on the refracted ray:
				dir1.x = plane_normal.x + n_perp.x*tan(outcoming_alpha);
				dir1.y = plane_normal.y + n_perp.y*tan(outcoming_alpha);
				dir1.z = plane_normal.z + n_perp.z*tan(outcoming_alpha);

				// another potential point on the refracted ray:
				dir2.x = plane_normal.x - n_perp.x*tan(outcoming_alpha);
				dir2.y = plane_normal.y - n_perp.y*tan(outcoming_alpha);
				dir2.z = plane_normal.z - n_perp.z*tan(outcoming_alpha);

				// select proper point:
		    	float result = n_perp.x*d_ray_directions_x[index]+n_perp.y*d_ray_directions_y[index]+n_perp.z*d_ray_directions_z[index];
		    	dir=dir1;
		    	if (result<0)
		    	{
		    		// we take dir2:
		    		dir=dir2;
		    	}
		    	// normalize the direction and assign it as new direction:
		    	norm = sqrt(dir.x*dir.x+dir.y*dir.y+dir.z*dir.z);
		    	dir.x=dir.x/norm; dir.y=dir.y/norm; dir.z=dir.z/norm;

		    	d_ray_directions_x[index]=dir.x;
		    	d_ray_directions_y[index]=dir.y;
		    	d_ray_directions_z[index]=dir.z;
			}
		    //else{
		    //  // sin_outcoming_alpha==0 e.g. ray is continuing straight
			//	// its possible only if incoming_angle=0
		    //}
		}
	}
}


void callCudaFnc(vector<Ray> *rays, std::list<int> *active_rays, float n0, float n1)
{
	int Size = active_rays->size();

	int i_size = Size*sizeof(int);
	int f_size = Size*sizeof(float);

    float *ray_directions_x;
    float *ray_directions_y;
    float *ray_directions_z;
    float *ray_origins_x;
    float *ray_origins_y;
    float *ray_origins_z;
    float *normals_x;
    float *normals_y;
    float *normals_z;
    int *is_propagating;
    float *t_closest;

    ray_directions_x = (float*) malloc(f_size);
    ray_directions_y = (float*) malloc(f_size);
    ray_directions_z = (float*) malloc(f_size);

    ray_origins_x = (float*) malloc(f_size);
    ray_origins_y = (float*) malloc(f_size);
    ray_origins_z = (float*) malloc(f_size);

    normals_x = (float*) malloc(f_size);
    normals_y = (float*) malloc(f_size);
    normals_z = (float*) malloc(f_size);

    is_propagating = (int*) malloc(i_size);
    t_closest = (float*) malloc(f_size);

    int local_idx=0;
    for (std::list<int>::iterator it=active_rays->begin(); it!=active_rays->end(); ++it)
    {
    	int idx = *it;
    	// Ray:
    	ray_directions_x[local_idx]=(*rays)[idx].direction.at<float>(0);
    	ray_directions_y[local_idx]=(*rays)[idx].direction.at<float>(1);
    	ray_directions_z[local_idx]=(*rays)[idx].direction.at<float>(2);

    	ray_origins_x[local_idx]=(*rays)[idx].origin.at<float>(0);
    	ray_origins_y[local_idx]=(*rays)[idx].origin.at<float>(1);
    	ray_origins_z[local_idx]=(*rays)[idx].origin.at<float>(2);

    	normals_x[local_idx]=(*rays)[idx].normal.at<float>(0);
    	normals_y[local_idx]=(*rays)[idx].normal.at<float>(1);
    	normals_z[local_idx]=(*rays)[idx].normal.at<float>(2);

    	t_closest[local_idx]=(*rays)[idx].t_closest;
    	is_propagating[local_idx]=(*rays)[idx].is_propagating;
    	++local_idx;
    }

    float *d_ray_directions_x;
    float *d_ray_directions_y;
    float *d_ray_directions_z;
    float *d_ray_origins_x;
    float *d_ray_origins_y;
    float *d_ray_origins_z;
    float *d_normals_x;
    float *d_normals_y;
    float *d_normals_z;
    int *d_is_propagating;
    float *d_t_closest;

    cudaMalloc(&d_ray_directions_x, f_size);
    cudaMalloc(&d_ray_directions_y, f_size);
    cudaMalloc(&d_ray_directions_z, f_size);

    cudaMalloc(&d_ray_origins_x, f_size);
    cudaMalloc(&d_ray_origins_y, f_size);
    cudaMalloc(&d_ray_origins_z, f_size);

    cudaMalloc(&d_normals_x, f_size);
    cudaMalloc(&d_normals_y, f_size);
    cudaMalloc(&d_normals_z, f_size);

	cudaMalloc(&d_is_propagating, i_size);
	cudaMalloc(&d_t_closest, f_size);

	cudaMemcpy(d_ray_directions_x, ray_directions_x, f_size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_ray_directions_y, ray_directions_y, f_size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_ray_directions_z, ray_directions_z, f_size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_ray_origins_x, ray_origins_x, f_size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_ray_origins_y, ray_origins_y, f_size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_ray_origins_z, ray_origins_z, f_size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_normals_x, normals_x, f_size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_normals_y, normals_y, f_size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_normals_z, normals_z, f_size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_is_propagating, is_propagating, i_size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_t_closest, t_closest, f_size, cudaMemcpyHostToDevice);

	// refraction kernel call:
	int block_size=128;
	int grid_size=Size/block_size+1;
	refraction_cuda<<<grid_size,block_size>>>(d_ray_directions_x, d_ray_directions_y, d_ray_directions_z, d_ray_origins_x, d_ray_origins_y, d_ray_origins_z, d_normals_x, d_normals_y, d_normals_z, d_is_propagating, d_t_closest, Size, n0, n1);
	cudaError_t err = cudaGetLastError();
	if (err != cudaSuccess)
	    printf("Error: %s\n", cudaGetErrorString(err));

	cudaThreadSynchronize();

	cudaMemcpy(ray_directions_x, d_ray_directions_x, f_size, cudaMemcpyDeviceToHost);
	cudaMemcpy(ray_directions_y, d_ray_directions_y, f_size, cudaMemcpyDeviceToHost);
	cudaMemcpy(ray_directions_z, d_ray_directions_z, f_size, cudaMemcpyDeviceToHost);
	cudaMemcpy(ray_origins_x, d_ray_origins_x, f_size, cudaMemcpyDeviceToHost);
	cudaMemcpy(ray_origins_y, d_ray_origins_y, f_size, cudaMemcpyDeviceToHost);
	cudaMemcpy(ray_origins_z, d_ray_origins_z, f_size, cudaMemcpyDeviceToHost);
	cudaMemcpy(normals_x, d_normals_x, f_size, cudaMemcpyDeviceToHost);
	cudaMemcpy(normals_y, d_normals_y, f_size, cudaMemcpyDeviceToHost);
	cudaMemcpy(normals_z, d_normals_z, f_size, cudaMemcpyDeviceToHost);
	cudaMemcpy(is_propagating, d_is_propagating, i_size, cudaMemcpyDeviceToHost);
	cudaMemcpy(t_closest, d_t_closest, f_size, cudaMemcpyDeviceToHost);

	// Free device memory:
	cudaFree(d_ray_directions_x);
	cudaFree(d_ray_directions_y);
	cudaFree(d_ray_directions_z);
	cudaFree(d_ray_origins_x);
	cudaFree(d_ray_origins_y);
	cudaFree(d_ray_origins_z);
	cudaFree(d_normals_x);
	cudaFree(d_normals_y);
	cudaFree(d_normals_z);
	cudaFree(d_is_propagating);
	cudaFree(d_t_closest);

	local_idx=0;
	for (std::list<int>::iterator it=active_rays->begin(); it!=active_rays->end(); ++it)
	{
    	int idx = *it;
        // Copy the data back to ray:
    	(*rays)[idx].direction.at<float>(0)=ray_directions_x[local_idx];
    	(*rays)[idx].direction.at<float>(1)=ray_directions_y[local_idx];
    	(*rays)[idx].direction.at<float>(2)=ray_directions_z[local_idx];
    	(*rays)[idx].origin.at<float>(0)=ray_origins_x[local_idx];
    	(*rays)[idx].origin.at<float>(1)=ray_origins_y[local_idx];
    	(*rays)[idx].origin.at<float>(2)=ray_origins_z[local_idx];
    	(*rays)[idx].normal.at<float>(0)=normals_x[local_idx];
    	(*rays)[idx].normal.at<float>(1)=normals_y[local_idx];
    	(*rays)[idx].normal.at<float>(2)=normals_z[local_idx];
    	(*rays)[idx].t_closest=t_closest[local_idx];
    	(*rays)[idx].is_propagating=is_propagating[local_idx];
    	++local_idx;
    }

    free(ray_directions_x);
    free(ray_directions_y);
    free(ray_directions_z);
    free(ray_origins_x);
    free(ray_origins_y);
    free(ray_origins_z);
	free(normals_x);
	free(normals_y);
	free(normals_z);
	free(is_propagating);
	free(t_closest);
}


