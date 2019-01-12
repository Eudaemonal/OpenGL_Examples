#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <vector>
#include <cmath>
#include "matrix.hpp"

/* generate terrain */
class Terrain{
public:
    Terrain(int w, int d)
        : Width(w)
        , Depth(d)
    {
        Altitude = std::vector<std::vector<double>>(w, std::vector<double>(d));
    }

    // get altitude at arbitrary point
    double getAltitude(double x, double z) {
        double altitude = 0;
        
        int x0 = floor(x);
        int x1 = ceil(x);
        int z0 = floor(z);
        int z1 = ceil(z);
        
        if (x0 == x1) {
            if (z0 == z1) {
                // The arbitrary point is on a grid point
                return Altitude[x0][z0];      
            }

            double y0 = Altitude[x0][z0];
            double y1 = Altitude[x1][z1];
                
            altitude = ((z-z0)/(z1-z0))*y1 + ((z1-z)/(z1-z0))*y0;
            
        } else if (z0 == z1) {

            double y2 = Altitude[x0][z0];
            double y3 = Altitude[x1][z1];
            
            altitude = ((x-x0)/(x1-x0))*y3 + ((x1-x)/(x1-x0))*y2;
        } else {
        	double x2 = ((z - z0) / (z1 - z0)) * (x0 - x1) + x1;
        	if (x - x2 < 0){
        		//on the left
        		double y0 = Altitude[x1][z0];
        		double y1 = Altitude[x0][z1];
        		double alt0 = ((z-z0)/(z1-z0)) *y1 + ((z1-z)/(z1-z0)) *y0;
        		
        		double y2 = Altitude[x0][z0];
        		double y3 = Altitude[x0][z1];
        		double alt1 = ((z-z0)/(z1-z0)) *y3 + ((z1-z)/(z1-z0)) *y2;
        		
        		altitude = ((x-x0)/(x2-x0))*alt0 + ((x2-x)/(x2-x0))*alt1;        		
        	} else if (x - x2 > 0){
        		//on the right
        		double y0 = Altitude[x1][z0];
        		double y1 = Altitude[x0][z1];
        		double alt0 = ((z-z0)/(z1-z0))*y1 + ((z1-z)/(z1-z0))*y0;
        		
        		double y2 = Altitude[x1][z0];
        		double y3 = Altitude[x1][z1];
        		double alt1 = ((z-z0)/(z1-z0))*y3 + ((z1-z)/(z1-z0))*y2;
        		
        		altitude = ((x-x2)/(x1-x2))*alt1 + ((x1-x)/(x1-x2))*alt0;

        	} else {
        		// on the line
        		double y0 = Altitude[x1][z0];
        		double y1 = Altitude[x0][z1];

        		altitude = ((z-z0)/(z1-z0))*y1 + ((z1-z)/(z1-z0))*y0;
        	}
        }
        return altitude;
    }

    // Draw terrain
    void draw(){
        // set material property
        float alpha = 1.0;
       	float ambient[4] = {0.46, 0.93, 0.27, alpha}; 
    	float diffuse[4] = {0.46, 0.93, 0.27, alpha}; 
    	float specular[4] = {0.33, 0.33, 0.33, alpha}; 
    	float shininess = 2.8;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient); 
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse); 
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular); 
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

        // Set the terrain to middle       
        glTranslatef(-Width/2, 0.0 ,-Depth/2);

        for (int x = 0; x < Width - 1; x++) {
            for (int z = 0; z < Depth - 1; z++) {
                double p0[3] = {(double)x, getAltitude(x, z), (double)z};
                double p1[3] = {(double)x+1, getAltitude(x+1, z), (double)z};
                double p2[3] = {(double)x+1, getAltitude(x+1, z+1), (double)z+1};
                double p3[3] = {(double)x, getAltitude(x, z+1), (double)z+1};
                
                double* n1 = getNormal(p0, p1, p3);
                double* n2 = getNormal(p1, p2, p3);
                
                n1 = normalise(n1);
                n2 = normalise(n2);
                
                //double[] t0 = normalise(p0);
                //double[] t1 = normalise(p1);
                //double[] t2 = normalise(p2);
                //double[] t3 = normalise(p3);
                
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                glBegin(GL_TRIANGLES);
                {
                	
                	glNormal3dv(n1);
                    //glNormal3dv(t0);
                    glVertex3dv(p0);
                    
                    //glNormal3dv(t1);
                    glVertex3dv(p1);
                    
                    //glNormal3dv(t3);
                    glVertex3dv(p3);
                }
                glEnd();
                
                glBegin(GL_TRIANGLES);
                {
                	
                	glNormal3dv(n2);
                    //glNormal3dv(t1, 0);
                    glVertex3dv(p1);
                    
                    //glNormal3dv(t2);
                    glVertex3dv(p2);
                    
                    //glNormal3dv(t3);
                    glVertex3dv(p3);
                }
                glEnd();
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
        }
    }

private:
    int Width; // number of vertices in the x-direction
    int Depth; // number of vertices in the z-direction

    std::vector<std::vector<double>> Altitude;

};


#endif
