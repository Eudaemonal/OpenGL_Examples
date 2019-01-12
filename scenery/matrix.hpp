#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <cmath>


std::vector<double> cross(std::vector<double> u, std::vector<double> v){
    std::vector<double> crossProduct(3);
    crossProduct[0] = u[1]*v[2] - u[2]*v[1];
    crossProduct[1] = u[2]*v[0] - u[0]*v[2];
    crossProduct[2] = u[0]*v[1] - u[1]*v[0];
    return crossProduct;
}

std::vector<double> normalise(std::vector<double> n) {
    double maginitude = sqrt(n[0]*n[0] + n[1]*n[1] + n[2]*n[2]);
    std::vector<double> norm(3);
    norm[0] = n[0]/maginitude;
    norm[1] = n[1]/maginitude;
    norm[2] = n[2]/maginitude;
    return norm;
}

std::vector<double> getNormal(std::vector<double> p0, std::vector<double> p1, std::vector<double> p2){
    std::vector<double> u = {p1[0] - p0[0], p1[1] - p0[1], p1[2] - p0[2]};
    std::vector<double> v = {p2[0] - p0[0], p2[1] - p0[1], p2[2] - p0[2]};
    return cross(u,v);
}


#endif
