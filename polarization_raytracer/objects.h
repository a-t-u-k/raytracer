#include "z_pol.h"

void scale_object(objLoader *objData, float object_scale_factor);
void translate_object(objLoader *objData, Mat *T);
void rotate_object(objLoader *objData, Mat *ObjR, Mat *ObjT);

void add_glass_test_plates(objLoader *objData);
void add_glass_test_plates45v1(objLoader *objData);
void add_glass_test_plates45v2(objLoader *objData);

void add_glass_goblet_v1(objLoader *objData);

void add_glass_cylinder_v1(objLoader *objData);
void add_glass_cylinder_v2(objLoader *objData);

void add_glass_plate45v1(objLoader *objData);
void add_glass_plate45v2(objLoader *objData);
void add_glass_plate45v3(objLoader *objData);
void add_glass_plate45v4(objLoader *objData);

void add_three_plates0(objLoader *objData);
void add_three_plates45v1(objLoader *objData);
void add_three_plates45v2(objLoader *objData);
void add_three_plates45v3(objLoader *objData);

void add_glass_wedge_v1(objLoader *objData);
void add_glass_wedge_v2(objLoader *objData);

void add_glass_sphere(objLoader *objData);


