#include "objects.h"

void give_rotation_matrix(Mat *axisP1, Mat *axisP2, float angle, Mat *Rot, Mat *T){
	Mat Pdelta=(*axisP2)-(*axisP1); Pdelta=Pdelta/norm(Pdelta);
	float a=axisP1->at<float>(0); float b=axisP1->at<float>(1); float c=axisP1->at<float>(2);
	float u=Pdelta.at<float>(0); float v=Pdelta.at<float>(1); float w=Pdelta.at<float>(2);

	Rot->at<float>(0,0)=u*u*(1-cos(angle))+cos(angle);
	Rot->at<float>(0,1)=u*v*(1-cos(angle))-w*sin(angle);
	Rot->at<float>(0,2)=u*w*(1-cos(angle))+v*sin(angle);
	Rot->at<float>(1,0)=u*v*(1-cos(angle))+w*sin(angle);
	Rot->at<float>(1,1)=v*v*(1-cos(angle))+cos(angle);
	Rot->at<float>(1,2)=u*w*(1-cos(angle))-u*sin(angle);
	Rot->at<float>(2,0)=u*w*(1-cos(angle))-v*sin(angle);
	Rot->at<float>(2,1)=v*w*(1-cos(angle))+u*sin(angle);
	Rot->at<float>(2,2)=w*w*(1-cos(angle))+cos(angle);

	(*T)=(*axisP1)-(*Rot)*(*axisP1);

	//T->at<float>(0)=(a*(v*v+w*w)-u*(b*v+c*w))*(1-cos(angle))+(b*w-c*v)*sin(angle);
	//T->at<float>(1)=(b*(u*u+w*w)-v*(a*u+c*w))*(1-cos(angle))+(c*u-a*w)*sin(angle);
	//T->at<float>(2)=(c*(u*u+v*v)-w*(a*u+b*v))*(1-cos(angle))+(a*v-b*u)*sin(angle);

}



// three plates 0 degrees:
void add_three_plates0(objLoader *objData)
{
    Mat T = (Mat_<float>(3,1) << 0.0, 0.0, 8.0); // T translation vector
    //Mat T = (Mat_<float>(3,1) << 0.0, 0.0, 8.0); // T translation vector
    float object_scale_factor=2.0;
    Mat ObjR = (Mat_<float>(3,3) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Mat ObjT = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);

    // apply scale to the object:
    scale_object(objData, object_scale_factor);

    // apply rotation to the object:
    float angle=0;
    Mat Obj_axisP1 = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);
    Mat Obj_axisP2 = (Mat_<float>(3,1) << 1.0, 0.0, 0.0);
    give_rotation_matrix(&Obj_axisP1, &Obj_axisP2, angle, &ObjR, &ObjT);
    rotate_object(objData, &ObjR, &ObjT);

    // apply translation to the object:
    translate_object(objData, &T);
}

// three plates 45 degrees v1:
void add_three_plates45v1(objLoader *objData)
{
    Mat T = (Mat_<float>(3,1) << 0.0, 0.0, 8.0); // T translation vector
    //Mat T = (Mat_<float>(3,1) << 0.0, 0.0, 8.0); // T translation vector
    float object_scale_factor=2.0;
    Mat ObjR = (Mat_<float>(3,3) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Mat ObjT = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);

    // apply scale to the object:
    scale_object(objData, object_scale_factor);

    // apply rotation to the object:
    float angle=M_PI/4.0;
    Mat Obj_axisP1 = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);
    Mat Obj_axisP2 = (Mat_<float>(3,1) << 1.0, 0.0, 0.0);
    give_rotation_matrix(&Obj_axisP1, &Obj_axisP2, angle, &ObjR, &ObjT);
    rotate_object(objData, &ObjR, &ObjT);

    // apply translation to the object:
    translate_object(objData, &T);
}

// three plates 45 degrees v2:
void add_three_plates45v2(objLoader *objData)
{
    Mat T = (Mat_<float>(3,1) << 0.0, 0.0, 8.0); // T translation vector
    //Mat T = (Mat_<float>(3,1) << 0.0, 0.0, 8.0); // T translation vector
    float object_scale_factor=2.0;
    Mat ObjR = (Mat_<float>(3,3) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Mat ObjT = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);

    // apply scale to the object:
    scale_object(objData, object_scale_factor);

    // apply rotation to the object:
    float angle=M_PI/4.0;
    Mat Obj_axisP1 = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);
    Mat Obj_axisP2 = (Mat_<float>(3,1) << 0.0, 1.0, 0.0);
    give_rotation_matrix(&Obj_axisP1, &Obj_axisP2, angle, &ObjR, &ObjT);
    rotate_object(objData, &ObjR, &ObjT);

    // apply translation to the object:
    translate_object(objData, &T);
}

// three plates 45 degrees v3:
void add_three_plates45v3(objLoader *objData)
{
    Mat T = (Mat_<float>(3,1) << 0.0, 0.0, 8.0); // T translation vector
    //Mat T = (Mat_<float>(3,1) << 0.0, 0.0, 8.0); // T translation vector
    float object_scale_factor=2.0;
    Mat ObjR = (Mat_<float>(3,3) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Mat ObjT = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);

    // apply scale to the object:
    scale_object(objData, object_scale_factor);

    // apply rotation to the object:
    float angle=M_PI/4.0;
    Mat Obj_axisP1 = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);
    Mat Obj_axisP2 = (Mat_<float>(3,1) << 1.0, 0.0, 0.0);
    give_rotation_matrix(&Obj_axisP1, &Obj_axisP2, angle, &ObjR, &ObjT);
    rotate_object(objData, &ObjR, &ObjT);

    Obj_axisP2.at<float>(1) = 1.0;
    Obj_axisP2.at<float>(0) = 0.0;
    give_rotation_matrix(&Obj_axisP1, &Obj_axisP2, angle, &ObjR, &ObjT);
    rotate_object(objData, &ObjR, &ObjT);

    // apply translation to the object:
    translate_object(objData, &T);
}


void add_glass_wedge_v1(objLoader *objData)
{
    Mat T = (Mat_<float>(3,1) << 0.0, 0.0, 8.0); // T translation vector
    //Mat T = (Mat_<float>(3,1) << 0.0, 0.0, 8.0); // T translation vector
    float object_scale_factor=2.0;
    Mat ObjR = (Mat_<float>(3,3) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Mat ObjT = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);

    // apply scale to the object:
    scale_object(objData, object_scale_factor);

    // apply rotation to the object:
    float angle=M_PI/2.0;
    Mat Obj_axisP1 = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);
    Mat Obj_axisP2 = (Mat_<float>(3,1) << 0.0, 0.0, 1.0);
    give_rotation_matrix(&Obj_axisP1, &Obj_axisP2, angle, &ObjR, &ObjT);
    rotate_object(objData, &ObjR, &ObjT);

    // apply rotation to the object:
    angle=M_PI/6.0;
    Obj_axisP2.at<float>(0) = 1.0;
    Obj_axisP2.at<float>(1) = 0.0;
    Obj_axisP2.at<float>(2) = 0.0;
    give_rotation_matrix(&Obj_axisP1, &Obj_axisP2, angle, &ObjR, &ObjT);
    rotate_object(objData, &ObjR, &ObjT);

    // apply translation to the object:
    translate_object(objData, &T);
}

void add_glass_wedge_v2(objLoader *objData)
{
    Mat T = (Mat_<float>(3,1) << 0.0, 0.0, 8.0); // T translation vector
    //Mat T = (Mat_<float>(3,1) << 0.0, 0.0, 8.0); // T translation vector
    float object_scale_factor=2.0;
    Mat ObjR = (Mat_<float>(3,3) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Mat ObjT = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);

    // apply scale to the object:
    scale_object(objData, object_scale_factor);

    // apply rotation to the object:
    float angle=M_PI-M_PI/6.0;
    Mat Obj_axisP1 = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);
    Mat Obj_axisP2 = (Mat_<float>(3,1) << 0.0, 1.0, 0.0);
    give_rotation_matrix(&Obj_axisP1, &Obj_axisP2, angle, &ObjR, &ObjT);
    rotate_object(objData, &ObjR, &ObjT);

    // apply translation to the object:
    translate_object(objData, &T);
}

// three plates 45 degrees v1:
void add_glass_plate45v1(objLoader *objData)
{
    Mat T = (Mat_<float>(3,1) << 0.0, 0.0, 8.0); // T translation vector
    //Mat T = (Mat_<float>(3,1) << 0.0, 0.0, 8.0); // T translation vector
    float object_scale_factor=1.0;
    Mat ObjR = (Mat_<float>(3,3) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Mat ObjT = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);

    // apply scale to the object:
    scale_object(objData, object_scale_factor);

    // apply rotation to the object:
    float angle=M_PI/4.0;
    Mat Obj_axisP1 = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);
    Mat Obj_axisP2 = (Mat_<float>(3,1) << 1.0, 0.0, 0.0);
    give_rotation_matrix(&Obj_axisP1, &Obj_axisP2, angle, &ObjR, &ObjT);
    rotate_object(objData, &ObjR, &ObjT);

    // apply translation to the object:
    translate_object(objData, &T);
}

void add_glass_plate45v2(objLoader *objData)
{
    Mat T = (Mat_<float>(3,1) << 0.0, 0.0, 8.0); // T translation vector
    //Mat T = (Mat_<float>(3,1) << 0.0, 0.0, 8.0); // T translation vector
    float object_scale_factor=1.0;
    Mat ObjR = (Mat_<float>(3,3) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Mat ObjT = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);

    // apply scale to the object:
    scale_object(objData, object_scale_factor);

    // apply rotation to the object:
    float angle=M_PI/4.0;
    Mat Obj_axisP1 = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);
    Mat Obj_axisP2 = (Mat_<float>(3,1) << 0.0, 1.0, 0.0);
    give_rotation_matrix(&Obj_axisP1, &Obj_axisP2, angle, &ObjR, &ObjT);
    rotate_object(objData, &ObjR, &ObjT);

    // apply translation to the object:
    translate_object(objData, &T);
}


void add_glass_plate45v3(objLoader *objData)
{
    Mat T = (Mat_<float>(3,1) << 0.0, 0.0, 8.0); // T translation vector
    //Mat T = (Mat_<float>(3,1) << 0.0, 0.0, 8.0); // T translation vector
    float object_scale_factor=1.0;
    Mat ObjR = (Mat_<float>(3,3) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Mat ObjT = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);

    // apply scale to the object:
    scale_object(objData, object_scale_factor);

    // apply rotation to the object:
    float angle=M_PI/4.0;
    Mat Obj_axisP1 = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);
    Mat Obj_axisP2 = (Mat_<float>(3,1) << 1.0, 0.0, 0.0);
    give_rotation_matrix(&Obj_axisP1, &Obj_axisP2, angle, &ObjR, &ObjT);
    rotate_object(objData, &ObjR, &ObjT);

    Obj_axisP2.at<float>(2) = 1.0;
    Obj_axisP2.at<float>(0) = 0.0;
    give_rotation_matrix(&Obj_axisP1, &Obj_axisP2, angle, &ObjR, &ObjT);
    rotate_object(objData, &ObjR, &ObjT);

    // apply translation to the object:
    translate_object(objData, &T);
}

void add_glass_plate45v4(objLoader *objData)
{
    Mat T = (Mat_<float>(3,1) << 0.0, 0.0, 8.0); // T translation vector
    //Mat T = (Mat_<float>(3,1) << 0.0, 0.0, 8.0); // T translation vector
    float object_scale_factor=1.0;
    Mat ObjR = (Mat_<float>(3,3) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Mat ObjT = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);

    // apply scale to the object:
    scale_object(objData, object_scale_factor);

    // apply rotation to the object:
    float angle=-M_PI/4.0;
    Mat Obj_axisP1 = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);
    Mat Obj_axisP2 = (Mat_<float>(3,1) << 1.0, 0.0, 0.0);
    give_rotation_matrix(&Obj_axisP1, &Obj_axisP2, angle, &ObjR, &ObjT);
    rotate_object(objData, &ObjR, &ObjT);

    angle=-M_PI/4.0;
    Obj_axisP2.at<float>(2) = 1.0;
    Obj_axisP2.at<float>(0) = 0.0;
    give_rotation_matrix(&Obj_axisP1, &Obj_axisP2, angle, &ObjR, &ObjT);
    rotate_object(objData, &ObjR, &ObjT);

    // apply translation to the object:
    translate_object(objData, &T);
}


void add_glass_cylinder_v1(objLoader *objData)
{
    //Mat T = (Mat_<float>(3,1) << 1.0, 0.0, 8.0); // T translation vector
    Mat T = (Mat_<float>(3,1) << 1.0, 0.0, 14.0); // T translation vector
    //Mat T = (Mat_<float>(3,1) << 0.0, 0.0, 8.0); // T translation vector
    float object_scale_factor=2.0;
    Mat ObjR = (Mat_<float>(3,3) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Mat ObjT = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);

    // apply scale to the object:
    scale_object(objData, object_scale_factor);

    // apply rotation to the object:
    float angle=M_PI/2.0;
    Mat Obj_axisP1 = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);
    Mat Obj_axisP2 = (Mat_<float>(3,1) << 1.0, 0.0, 0.0);
    give_rotation_matrix(&Obj_axisP1, &Obj_axisP2, angle, &ObjR, &ObjT);
    rotate_object(objData, &ObjR, &ObjT);

    Obj_axisP2.at<float>(1) = 1.0;
    Obj_axisP2.at<float>(0) = 0.0;
    give_rotation_matrix(&Obj_axisP1, &Obj_axisP2, angle, &ObjR, &ObjT);
    rotate_object(objData, &ObjR, &ObjT);

    // apply translation to the object:
    translate_object(objData, &T);
}

void add_glass_cylinder_v2(objLoader *objData)
{
    Mat T = (Mat_<float>(3,1) << 1.0, 0.0, 8.0); // T translation vector
    //Mat T = (Mat_<float>(3,1) << 0.0, 0.0, 8.0); // T translation vector
    float object_scale_factor=1.0;
    Mat ObjR = (Mat_<float>(3,3) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Mat ObjT = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);

    // apply scale to the object:
    scale_object(objData, object_scale_factor);

    // apply rotation to the object:
    float angle=M_PI/2.0;
    Mat Obj_axisP1 = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);
    Mat Obj_axisP2 = (Mat_<float>(3,1) << 0.0, 1.0, 0.0);
    give_rotation_matrix(&Obj_axisP1, &Obj_axisP2, angle, &ObjR, &ObjT);
    rotate_object(objData, &ObjR, &ObjT);

    Obj_axisP2.at<float>(1) = 1.0;
    Obj_axisP2.at<float>(0) = 0.0;

    give_rotation_matrix(&Obj_axisP1, &Obj_axisP2, angle, &ObjR, &ObjT);
    rotate_object(objData, &ObjR, &ObjT);

    // apply translation to the object:
    translate_object(objData, &T);
}

void add_glass_sphere(objLoader *objData)
{
    Mat T = (Mat_<float>(3,1) << -3.0, -4.0, 2.0); // T translation vector
    //Mat T = (Mat_<float>(3,1) << 0.0, 0.0, 12.0); // T translation vector
    float object_scale_factor=1.0;

    // apply scale to the object:
    scale_object(objData, object_scale_factor);

    // apply translation to the object:
    translate_object(objData, &T);
}

void add_glass_goblet_v1(objLoader *objData)
{
    Mat T = (Mat_<float>(3,1) << 2.0, -2.0, 8.0); // T translation vector
    //Mat T = (Mat_<float>(3,1) << 0.0, 0.0, 8.0); // T translation vector
    float object_scale_factor=1.0;
    Mat ObjR = (Mat_<float>(3,3) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Mat ObjT = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);

    // apply scale to the object:
    scale_object(objData, object_scale_factor);

    // apply rotation to the object:
    float angle=M_PI/2.0;
    Mat Obj_axisP1 = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);
    Mat Obj_axisP2 = (Mat_<float>(3,1) << 0.0, 0.0, 1.0);
    give_rotation_matrix(&Obj_axisP1, &Obj_axisP2, angle, &ObjR, &ObjT);
    rotate_object(objData, &ObjR, &ObjT);

    Obj_axisP2.at<float>(0) = 0.0; Obj_axisP2.at<float>(1) = 1.0; Obj_axisP2.at<float>(2) = 0.0;
    angle=M_PI/10.0;
    give_rotation_matrix(&Obj_axisP1, &Obj_axisP2, angle, &ObjR, &ObjT);
    rotate_object(objData, &ObjR, &ObjT);

    // apply translation to the object:
    translate_object(objData, &T);
}

void add_glass_test_plates(objLoader *objData)
{
    Mat T = (Mat_<float>(3,1) << -0.5, -0.5, 8.0); // T translation vector
    //Mat T = (Mat_<float>(3,1) << 0.0, 0.0, 8.0); // T translation vector
    float object_scale_factor=2.0;
    Mat ObjR = (Mat_<float>(3,3) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Mat ObjT = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);

    // apply scale to the object:
    scale_object(objData, object_scale_factor);

    // apply rotation to the object:
    float angle=0.0;
    Mat Obj_axisP1 = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);
    Mat Obj_axisP2 = (Mat_<float>(3,1) << 0.0, 0.0, 1.0);
    give_rotation_matrix(&Obj_axisP1, &Obj_axisP2, angle, &ObjR, &ObjT);
    rotate_object(objData, &ObjR, &ObjT);

    Obj_axisP2.at<float>(0) = 0.0; Obj_axisP2.at<float>(1) = 1.0; Obj_axisP2.at<float>(2) = 0.0;
    angle=0.0;
    give_rotation_matrix(&Obj_axisP1, &Obj_axisP2, angle, &ObjR, &ObjT);
    rotate_object(objData, &ObjR, &ObjT);

    // apply translation to the object:
    translate_object(objData, &T);
}

void add_glass_test_plates45v1(objLoader *objData)
{
    Mat T = (Mat_<float>(3,1) << -0.5, -0.5, 8.0); // T translation vector
    //Mat T = (Mat_<float>(3,1) << 0.0, 0.0, 8.0); // T translation vector
    float object_scale_factor=2.0;
    Mat ObjR = (Mat_<float>(3,3) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Mat ObjT = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);

    // apply scale to the object:
    scale_object(objData, object_scale_factor);

    // apply rotation to the object:
    float angle=M_PI/4.0;
    Mat Obj_axisP1 = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);
    Mat Obj_axisP2 = (Mat_<float>(3,1) << 0.0, 1.0, 0.0);
    give_rotation_matrix(&Obj_axisP1, &Obj_axisP2, angle, &ObjR, &ObjT);
    rotate_object(objData, &ObjR, &ObjT);

    Obj_axisP2.at<float>(0) = 0.0; Obj_axisP2.at<float>(1) = 1.0; Obj_axisP2.at<float>(2) = 0.0;
    angle=0.0;
    give_rotation_matrix(&Obj_axisP1, &Obj_axisP2, angle, &ObjR, &ObjT);
    rotate_object(objData, &ObjR, &ObjT);

    // apply translation to the object:
    translate_object(objData, &T);
}

void add_glass_test_plates45v2(objLoader *objData)
{
    Mat T = (Mat_<float>(3,1) << -0.5, -0.5, 8.0); // T translation vector
    //Mat T = (Mat_<float>(3,1) << 0.0, 0.0, 8.0); // T translation vector
    float object_scale_factor=2.0;
    Mat ObjR = (Mat_<float>(3,3) << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Mat ObjT = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);

    // apply scale to the object:
    scale_object(objData, object_scale_factor);

    // apply rotation to the object:
    float angle=M_PI/4.0;
    Mat Obj_axisP1 = (Mat_<float>(3,1) << 0.0, 0.0, 0.0);
    Mat Obj_axisP2 = (Mat_<float>(3,1) << 1.0, 0.0, 0.0);

    give_rotation_matrix(&Obj_axisP1, &Obj_axisP2, angle, &ObjR, &ObjT);
    rotate_object(objData, &ObjR, &ObjT);

    Obj_axisP2.at<float>(0) = 0.0; Obj_axisP2.at<float>(1) = 1.0; Obj_axisP2.at<float>(2) = 0.0;
    angle=0.0;

    give_rotation_matrix(&Obj_axisP1, &Obj_axisP2, angle, &ObjR, &ObjT);
    rotate_object(objData, &ObjR, &ObjT);

    // apply translation to the object:
    translate_object(objData, &T);
}

// scale object by object_scale_factor
void scale_object(objLoader *objData, float object_scale_factor)
{
    for (int i=0; i<objData->vertexCount; ++i){
    	objData->vertexList[i]->e[0]=objData->vertexList[i]->e[0]*object_scale_factor;
    	objData->vertexList[i]->e[1]=objData->vertexList[i]->e[1]*object_scale_factor;
    	objData->vertexList[i]->e[2]=objData->vertexList[i]->e[2]*object_scale_factor;
    }
}

// translate object on T
void translate_object(objLoader *objData, Mat *T)
{
    for (int i=0; i<objData->vertexCount; ++i){
    	objData->vertexList[i]->e[0]=objData->vertexList[i]->e[0]+T->at<float>(0);
    	objData->vertexList[i]->e[1]=objData->vertexList[i]->e[1]+T->at<float>(1);
    	objData->vertexList[i]->e[2]=objData->vertexList[i]->e[2]+T->at<float>(2);
    }
}

void rotate_object(objLoader *objData, Mat *ObjR, Mat *ObjT)
{
    for (int i=0; i<objData->vertexCount; ++i){
        Mat obj_vertex = (Mat_<float>(3,1) << objData->vertexList[i]->e[0], objData->vertexList[i]->e[1], objData->vertexList[i]->e[2]);
        obj_vertex=(*ObjR)*obj_vertex+(*ObjT);
    	objData->vertexList[i]->e[0]=obj_vertex.at<float>(0);
    	objData->vertexList[i]->e[1]=obj_vertex.at<float>(1);
    	objData->vertexList[i]->e[2]=obj_vertex.at<float>(2);
    }
}

