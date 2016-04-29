#include <embree2/rtcore.h>
#include <embree2/rtcore_ray.h>
#include "common/math/vec3.h"
#include "common/sys/alloc.h"

#include "z_pol.h"
#include "objects.h"
#include "accel.h"

embree::Vec3fa * face_colors = nullptr;
embree::Vec3fa * vertex_colors = nullptr;
unsigned int add_object (RTCScene scene_i, objLoader *objData);

int main(void){
	// Inputs:
	string screenFileName = "background.jpg"; // screen pattern
	const int max_refraction_interfaces = 20; // limits the number of interfaces
    const float refr_index_air=1.0;
    const float refr_index_glass=1.5;
    const float min_travel_time=0.001;
    // camera image size
    const int W=1200;
    const int H=1200;
    const float camera_opening=1500;
    Mat K = (Mat_<float>(3,3) << camera_opening, 0.0, 800.0, 0.0, camera_opening, 800.0, 0.0, 0.0, 1.0); // K matrix

    // screen:
    Mat II = imread(screenFileName.c_str(), CV_LOAD_IMAGE_ANYCOLOR | CV_LOAD_IMAGE_ANYDEPTH);
    Mat plane_origin = (Mat_<float>(3,1) << -10.0, -10.0, 15.0); // vertical shift, horizontal shift
    Mat plane_ox = (Mat_<float>(3,1) << 1.0, 0.0, 0.0);
    Mat plane_oy = (Mat_<float>(3,1) << 0.0, 1.0, 0.0);
    const float plane_size_x=20.0;
    const float plane_size_y=20.0;



    // camera image:
    Mat I(W, H, CV_8UC3, Scalar::all(0));
    // invert K matrix:
    Mat Kinv;
    invert(K, Kinv);

    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
    _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);
	rtcInit(NULL);
	// create scene:
	RTCScene scene = rtcNewScene(RTC_SCENE_STATIC, RTC_INTERSECT1);

    // load the object:
	objLoader *objData = new objLoader();

    objData->load("sphere_64x64.obj");
    //objData->load("hollow_sphere.obj");
    //objData->load("hollow_sphere_128.obj");
    add_glass_sphere(objData);
    add_object(scene, objData);

    //objData->load("wineglassgoblet.obj");
    //add_glass_goblet_v1(objData);
    //add_object(scene, objData);

    // add object:
    //objData->load("cylinder.obj");
    //objData->load("hollow_cylinder_360.obj");
    //objData->load("input/cylinder_360.obj");
    //add_glass_cylinder_v1(objData);
    //add_glass_cylinder_v2(objData);
    //add_object(scene, objData);

    delete(objData);
	// commit changes to scene
	rtcCommit (scene);

	// initialize data structures:
	vector<Ray> rays;
	rays.resize(H*W);
	for (int i=0; i<H; ++i){
		for (int j=0; j<W; ++j)
		{
			int idx = i*W+j;
			rays[idx].i=i;
			rays[idx].j=j;
        	Mat ij = (Mat_<float>(3,1) << float(i), float(j), 1.0);
            Mat ray_direction=Kinv*ij;
            ray_direction = ray_direction/norm(ray_direction); // normalized direction
			rays[idx].direction=ray_direction;
		}
	}

	std::list<int> active_rays; // list of indexes of active rays
	active_rays.resize(H*W);
	int element=0;
	for (std::list<int>::iterator it=active_rays.begin(); it!=active_rays.end(); ++it)
	{
		*it=element;
		++element;
	}

	// raytracing:

	// timing:
	clock_t begin = clock();

	RTCRay ray;
	int rays_segment_number=1;
	bool raytrace = true;
	while (raytrace==true && rays_segment_number < max_refraction_interfaces)
	{
		raytrace = false;
		cout << "Step " << rays_segment_number<< endl;
		std::list<int>::iterator it=active_rays.begin();
		while (it!=active_rays.end())
		{
			int idx = *it;
			ray.org[0] = rays[idx].origin.at<float>(0);
			ray.org[1] = rays[idx].origin.at<float>(1);
			ray.org[2] = rays[idx].origin.at<float>(2);
			ray.dir[0] = rays[idx].direction.at<float>(0);
			ray.dir[1] = rays[idx].direction.at<float>(1);
			ray.dir[2] = rays[idx].direction.at<float>(2);
			ray.tnear = min_travel_time;
			ray.tfar = 1000000000.0;
			ray.geomID = RTC_INVALID_GEOMETRY_ID;
			ray.primID = RTC_INVALID_GEOMETRY_ID;
			ray.mask = -1;
			ray.time = 0;

			// intersect ray with the scene
			rtcIntersect(scene, ray);

			if (ray.primID==RTC_INVALID_GEOMETRY_ID)
			{
				// no more intersection with the object for this ray:
				rays[idx].is_propagating=2;
				it = active_rays.erase (it);
			}else
			{
				rays[idx].t_closest = ray.tfar;
				rays[idx].normal.at<float>(0) = ray.Ng[0];
				rays[idx].normal.at<float>(1) = ray.Ng[1];
				rays[idx].normal.at<float>(2) = ray.Ng[2];
				++it;
			}
		}
		cout << "Active list size:" << active_rays.size() << endl;
		// refract all rays:
		float n0, n1;
		if (rays_segment_number%2==1)
		{
			n0=refr_index_air;
			n1=refr_index_glass;
		}else{
			n0=refr_index_glass;
			n1=refr_index_air;
		}

		callCudaFnc(&rays, &active_rays, n0, n1);
		++rays_segment_number;

		for (int idx=0; idx<H*W; ++idx)
		{
			if (rays[idx].is_propagating==1)
			{
				raytrace=true;
				break;
			}
		}
	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "\n Raytracing time: " << elapsed_secs;

	// drawing the camera image:
	for (int idx=0; idx<H*W; ++idx)
	{
		if (rays[idx].is_propagating==2)
		{
		  	int r, g, b;
		   	Mat intersection_point;
		   	Mat ray_origin = (Mat_<float>(3,1) << rays[idx].origin.at<float>(0), rays[idx].origin.at<float>(1), rays[idx].origin.at<float>(2));
		   	Mat ray_direction = (Mat_<float>(3,1) << rays[idx].direction.at<float>(0), rays[idx].direction.at<float>(1), rays[idx].direction.at<float>(2));
		   	int is_intersecting=0;

		   	// plane_ox - direction of the X axis of the plane
		   	// plane_oy - direction of the Y axis of the plane
		    intersect_ray_and_plane(&II, &plane_origin, &plane_ox, &plane_oy, plane_size_x, plane_size_y, &ray_origin, &ray_direction, r, g, b, &intersection_point, is_intersecting);

		    I.at<Vec3b>(rays[idx].j,rays[idx].i).val[2]=r;
		    I.at<Vec3b>(rays[idx].j,rays[idx].i).val[1]=g;
		    I.at<Vec3b>(rays[idx].j,rays[idx].i).val[0]=b;
		}
	}
	imwrite("output.png", I);

	rtcDeleteScene(scene);
	rtcExit();
	cout << endl << "done" << endl;
}


// r=1; g=0; b=0 if the plane not intersected
// is_intersecting=0 if the ray not intersects the picture
void intersect_ray_and_plane(Mat *II, Mat *plane_origin, Mat *plane_ox, Mat *plane_oy, float plane_size_x, float plane_size_y, Mat *ray_origin, Mat *ray_direction, int &r, int &g, int &b, Mat *intersection_point, int &is_intersecting){
        Mat A = (Mat_<float>(3,3) << plane_ox->at<float>(0), plane_oy->at<float>(0), -ray_direction->at<float>(0), plane_ox->at<float>(1), plane_oy->at<float>(1), -ray_direction->at<float>(1), plane_ox->at<float>(2), plane_oy->at<float>(2), -ray_direction->at<float>(2));
        Mat C = (Mat_<float>(3,1) << ray_origin->at<float>(0)-plane_origin->at<float>(0), ray_origin->at<float>(1)-plane_origin->at<float>(1), ray_origin->at<float>(2)-plane_origin->at<float>(2));
        Mat Ainv; invert(A, Ainv);
        Mat t = Ainv*C;
        is_intersecting=0;
        if (t.at<float>(2)>0 && t.at<float>(2)<100000000){
            // the ray is intersecting the plane at t(3) for the ray and at
            // coordinates [t(1) t(2)]
            if (t.at<float>(0)>=0 && t.at<float>(0)<plane_size_x && t.at<float>(1)>=0 && t.at<float>(1)<plane_size_y){
                // on the picture:
                is_intersecting=1;
                (*intersection_point)=(*ray_origin)+t.at<float>(2)*(*ray_direction);
                int px=(int)(floor(II->size().width*t.at<float>(0)/plane_size_x));
                int py=(int)(floor(II->size().height*t.at<float>(1)/plane_size_y));

                r=(int)(II->at<Vec3b>(py,px).val[2]);
                g=(int)(II->at<Vec3b>(py,px).val[1]);
                b=(int)(II->at<Vec3b>(py,px).val[0]);
            }else{
                r=0; g=0; b=0;
			}
        }else{
            r=1; g=0; b=0; // no plane intersected
        }
}

/* adds an object to the scene */
unsigned int add_object (RTCScene scene_i, objLoader *objData)
{
	int N=objData->faceCount;
	int M=objData->vertexCount;
	/* create a triangulated object with N triangles and M vertices */
	unsigned int mesh = rtcNewTriangleMesh (scene_i, RTC_GEOMETRY_STATIC, N, M);

	/* create face and vertex color arrays */
	face_colors = (embree::Vec3fa*) embree::alignedMalloc(N*sizeof(embree::Vec3fa));
	vertex_colors = (embree::Vec3fa*) embree::alignedMalloc(M*sizeof(embree::Vec3fa));

	/* set vertices and vertex colors */
	Vertex* vertices = (Vertex*) rtcMapBuffer(scene_i,mesh,RTC_VERTEX_BUFFER);
	for (int i=0; i<M; ++i){
		vertices[i].x=objData->vertexList[i]->e[0];
		vertices[i].y=objData->vertexList[i]->e[1];
		vertices[i].z=objData->vertexList[i]->e[2];
		vertex_colors[i]=embree::Vec3fa(1,1,1);
	}

	rtcUnmapBuffer(scene_i,mesh,RTC_VERTEX_BUFFER);

	/* set triangles and face colors */
	Triangle* triangles = (Triangle*) rtcMapBuffer(scene_i,mesh,RTC_INDEX_BUFFER);

	for (int i=0; i<N; ++i){
		triangles[i].v0 = objData->faceList[i]->vertex_index[0];
		triangles[i].v1 = objData->faceList[i]->vertex_index[1];
		triangles[i].v2 = objData->faceList[i]->vertex_index[2];
		face_colors[i]=embree::Vec3fa(1,1,1);
	}

	rtcUnmapBuffer(scene_i,mesh,RTC_INDEX_BUFFER);
	rtcSetBuffer(scene_i,mesh,RTC_USER_VERTEX_BUFFER0,vertex_colors,0,sizeof(embree::Vec3fa));

	return mesh;
}

