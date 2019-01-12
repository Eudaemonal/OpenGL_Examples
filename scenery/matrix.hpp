#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <cmath>


double* cross(double u[3], double v[3]){
    double* crossProduct = (double*)malloc(sizeof(double)*3);
    crossProduct[0] = u[1]*v[2] - u[2]*v[1];
    crossProduct[1] = u[2]*v[0] - u[0]*v[2];
    crossProduct[2] = u[0]*v[1] - u[1]*v[0];
    return crossProduct;
}

double* normalise(double n[3]) {
    double maginitude = sqrt(n[0]*n[0] + n[1]*n[1] + n[2]*n[2]);
    double* norm = (double*)malloc(sizeof(double)*3);
    norm[0] = n[0]/maginitude;
    norm[1] = n[1]/maginitude;
    norm[2] = n[2]/maginitude;
    return norm;
}

double* getNormal(double p0[3], double p1[3], double p2[3]){
    double* u = (double*)malloc(sizeof(double)*3);
    double* v = (double*)malloc(sizeof(double)*3);

    u[0] = p1[0] - p0[0]; u[1] = p1[1] - p0[1]; u[2] = p1[2] - p0[2];
    v[0] = p2[0] - p0[0]; v[1] = p2[1] - p0[1]; v[2] = p2[2] - p0[2];
    return cross(u,v);
}


#endif
